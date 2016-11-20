#include "dispatcher.h"

Dispatcher::Dispatcher(std::vector<Process*> processes) : _quantum(2)
{
    _currentTimestamp = 0;
    _futureProcesses = processes;
    sort(_futureProcesses.begin(), _futureProcesses.end(), [](Process *p1, Process *p2) {
        return p1->getInitTime() > p2->getInitTime();
    });
}

std::pair<int, std::vector<Process*>> Dispatcher::_getNextProcesses()
{
    if (_futureProcesses.empty()) {
        return make_pair(-1, std::vector<Process*>());
    }

    std::pair<int, std::vector<Process*>> nextProcesses;
    nextProcesses.first = _futureProcesses.back()->getInitTime();
    while (!_futureProcesses.empty() && _futureProcesses.back()->getInitTime() == nextProcesses.first) {
        nextProcesses.second.push_back(_futureProcesses.back());
        _futureProcesses.pop_back();
    }

    return nextProcesses;
}

void Dispatcher::run()
{
    std::pair<int, std::vector<Process*>> nextProcesses;
    nextProcesses = _getNextProcesses(); //coloca o primeiro timestamp na espera
    Process *currProcess = nullptr;

    MemoryManager memoryManager;
    ResourceManager resourceManager;
    ProcessManager processManager;
    do {
        std::cout << "**  Timestamp atual[ " << _currentTimestamp << " ]  **" << std::endl;
        if (nextProcesses.first > 0){
            std::cout << "**  Proximos processos em timestamp: " << nextProcesses.first << "  **"  << std::endl;
        } else {
            std::cout << "**  Sem processos novos  **" << std::endl;
        }

        if (nextProcesses.first == _currentTimestamp++){
            processManager.insertTimestampProcesses(nextProcesses);
            nextProcesses = _getNextProcesses();
        }

        std::cout << "--- Filas de processos: ---" << std::endl;
        processManager.printLines();

        if (currProcess == nullptr || !(currProcess->getPriority() == 0 && currProcess->getProcessingTime() > 0) ){
            currProcess = processManager.getNextProcess();
        }

        if (currProcess->getProcessingTime() > 0) {
            if (currProcess->getMemoryOffset() != -1) {
                std::cout << "--- Processo na CPU: ---" << std::endl;
                toCPU(currProcess);
            } else {
                if (memoryManager.allocateMemory(currProcess) && resourceManager.acquireAll(currProcess)) {
                    std::cout << "--- Processo na CPU: ---" << std::endl;
                    toCPU(currProcess);
                } else {
                    std::cout << " -> Nao ha blocos de memoria disponiveis para o processo atual." << std::endl;
                }
            }
        }

        if (!currProcess->getPriority() && currProcess->getProcessingTime() > 0) { // checar para processo tempo real
            processManager.insertBackProcess(currProcess);
        } else {
            resourceManager.releaseAll(currProcess);
            memoryManager.deallocateMemory(currProcess);
        }
        std::cout << "**********************************" << std::endl;
    } while(currProcess->getInitTime() > 0 || nextProcesses.first != -1);
}

void Dispatcher::toCPU(Process *process){
    process->setProcessingTime((process->getProcessingTime() < _quantum) ? 0 : process->getProcessingTime() - _quantum);
    process->printProcess();
}
