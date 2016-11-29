#include "dispatcher.h"

Dispatcher::Dispatcher(std::vector<Process*> processes) : _quantum(1)
{
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

bool Dispatcher::_canRun(Process *process, MemoryManager &memoryManager, ResourceManager &resourceManager)
{
    return memoryManager.canAllocate(process) && resourceManager.canAcquire(process);
}

void Dispatcher::_sendToCPU(Process *process)
{
    process->setProcessingTime(process->getProcessingTime() - _quantum);
    std::cout << "--- Processo na CPU: ---" << std::endl;
    process->printProcess();
}

void Dispatcher::run()
{
    MemoryManager memoryManager;
    ResourceManager resourceManager;
    ProcessManager processManager;

    std::pair<int, std::vector<Process*>> nextProcesses = _getNextProcesses();
    Process *currProcess = nullptr;
    int timestamp = 0;
    while (nextProcesses.first != -1 || !processManager.isEmpty()) {
        std::cout << "**  Timestamp atual[ " << timestamp << " ]  **" << std::endl;

        if (nextProcesses.first == timestamp) {
            processManager.insertProcesses(nextProcesses.second);
            nextProcesses = _getNextProcesses();
        }

        std::cout << "--- Filas de processos: ---" << std::endl;
        processManager.printQueues();


        if (!currProcess && !processManager.isEmpty()) {
            for (auto it = processManager.begin(); it != processManager.end(); it++) {
                currProcess = *it;
                if (_canRun(currProcess, memoryManager, resourceManager)) {
                    memoryManager.allocateMemory(currProcess);
                    resourceManager.acquireAll(currProcess);
                    processManager.erase(it); // remove from queue
                    break;
                } else {
                    currProcess = nullptr;
                }
            }

            if (!currProcess) {
                std::cout << "Deadlock!" << std::endl;
                exit(1);
            }
        }

        resourceManager.printResources();
        if (currProcess) {
            char wait;
            std::cin >> wait;
            _sendToCPU(currProcess);
            std::cin >> wait;
            if (currProcess->getProcessingTime() <= 0) { // finished execution
                memoryManager.deallocateMemory(currProcess);
                resourceManager.releaseAll(currProcess, memoryManager);
                delete currProcess;
                currProcess = nullptr;
            } else if (currProcess->getPriority() > 0) { // preemption for user processes
                processManager.reinsertProcess(currProcess);
                currProcess = nullptr;
            }
        }

        timestamp++;

        std::cout << "**********************************" << std::endl;
    }
}
