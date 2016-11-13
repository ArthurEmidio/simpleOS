#include "dispatcher.h"

//#define DEBUG
#ifdef DEBUG
    //se estiver definido debug, imprime os trecos
    #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
    #define DEBUG_ONLY(x) do{x;}while(0);

#else
    //caso contrario, recebe argumentos mas faz nada
    #define DEBUG_PRINT(message)
    #define DEBUG_ONLY(x) //do{;}while(0)

#endif //DEBUG



Dispatcher::Dispatcher(std::vector<Process*> processes)
{
    _quantum = 2;
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
    DEBUG_PRINT("Dispatcher::run(): iniciado")
    std::pair<int, std::vector<Process*>> nextProcesses;
    Process *toExecution;
    int i = 0;

    MemoryManager memoryManager;
    do{
        std::cout << "**  Ciclo de execucao [ " << i++ << " ]  **" << std::endl;
        nextProcesses = _getNextProcesses();
        if(nextProcesses.first != -1){
            ProcessManager::getInstance()->InsertTimeStampProcesses(nextProcesses);
        }
        std::cout << "--- Filas de processos: ---" << std::endl;
        ProcessManager::getInstance()->PrintLines();

        toExecution = ProcessManager::getNextProcess();
        if(toExecution->getInitTime() == -1) break;

        if(toExecution->getMemoryOffset() != -1){
            std::cout << "--- Processo na CPU: ---" << std::endl;
            toCPU(toExecution);
        }else{
            if(memoryManager.allocateMemory(toExecution)){
                std::cout << "--- Processo na CPU: ---" << std::endl;
                toCPU(toExecution);
            }else{
                std::cout << " -> Nao ha blocos de memoria disponiveis para o processo atual." << std::endl;
            }
        }

        if(toExecution->getProcessingTime() > 0){
            ProcessManager::getInstance()->InsertBackProcess(toExecution);
        }else{
            memoryManager.deallocateMemory(toExecution);
        }
        std::cout << "**********************************" << std::endl;

        #ifdef _WIN32
            Sleep(4000);
            system("cls");
        #endif // _WIN32
    }while(toExecution->getInitTime() != -1);
    DEBUG_PRINT("Dispatcher::run(): finalizado")
}

void Dispatcher::toCPU(Process *process){
    //O loop de execuçao em relação a CPU não funciona como "umm loop por quantum".
    //podemos fazer funcionar dessa forma.
    DEBUG_PRINT("Dispatcher::toCPU(): iniciado")
    if(process->getPriority() > 0){
        process->setProcessingTime((process->getProcessingTime() < _quantum) ? 0 : process->getProcessingTime() - _quantum);
    }else{
        process->setProcessingTime(0);
    }
    process->printProcess();
    DEBUG_PRINT("Dispatcher::toCPU(): finalizado")
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
