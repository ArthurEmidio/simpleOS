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
    _currentTimeStamp = 0;
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
    nextProcesses = _getNextProcesses();//coloca o primeiro timeStamp na espra
    Process *toExecution = nullptr;

    MemoryManager memoryManager;
    ResourceManager resourceManager;
    do{
        std::cout << "**  TimeStamp atual[ " << _currentTimeStamp << " ]  **" << std::endl;
        if(nextProcesses.first > 0){
            std::cout << "**  Proximos processos em TimeStamp: " << nextProcesses.first << "  **"  << std::endl;
        }else{
            std::cout << "**  Sem processos novos  **" << std::endl;
        }
        if(nextProcesses.first == _currentTimeStamp++){
            ProcessManager::getInstance()->InsertTimeStampProcesses(nextProcesses);
            nextProcesses = _getNextProcesses();
        }

        std::cout << "--- Filas de processos: ---" << std::endl;
        ProcessManager::getInstance()->PrintLines();
        if(toExecution == nullptr || !(toExecution->getPriority() == 0 && toExecution->getProcessingTime() > 0) ){
            toExecution = ProcessManager::getNextProcess();
        }
        if(toExecution->getProcessingTime() > 0){
            if(toExecution->getMemoryOffset() != -1){
                std::cout << "--- Processo na CPU: ---" << std::endl;
                toCPU(toExecution);
            }else{
                if(memoryManager.allocateMemory(toExecution) && resourceManager.acquireAll(toExecution)){
                    std::cout << "--- Processo na CPU: ---" << std::endl;
                    toCPU(toExecution);
                }else{
                    std::cout << " -> Nao ha blocos de memoria disponiveis para o processo atual." << std::endl;
                }
            }
        }

        if(!toExecution->getPriority() && toExecution->getProcessingTime() > 0){//checar para processo tempo real
            ProcessManager::getInstance()->InsertBackProcess(toExecution);
        }else{
            resourceManager.releaseAll(toExecution);
            memoryManager.deallocateMemory(toExecution);
        }
        std::cout << "**********************************" << std::endl;

        #ifdef _WIN32
            Sleep(4000);
            system("cls");
        #endif // _WIN32
    }while(toExecution->getInitTime() > 0 || nextProcesses.first != -1);
    DEBUG_PRINT("Dispatcher::run(): finalizado")
}

void Dispatcher::toCPU(Process *process){
    //O loop de execuçao em relação a CPU não funciona como "umm loop por quantum".
    //podemos fazer funcionar dessa forma.
    DEBUG_PRINT("Dispatcher::toCPU(): iniciado")
    process->setProcessingTime((process->getProcessingTime() < _quantum) ? 0 : process->getProcessingTime() - _quantum);
    process->printProcess();
    DEBUG_PRINT("Dispatcher::toCPU(): finalizado")
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
