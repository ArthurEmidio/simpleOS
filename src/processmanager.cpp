#include "processmanager.h"

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



ProcessManager* ProcessManager::instance = nullptr;
std::vector<std::vector<Process*>> ProcessManager::processLines;
int ProcessManager::processCount = 0;

ProcessManager::ProcessManager()
{
    DEBUG_PRINT("ProcessManager(): iniciado")
    //cria as 4 filas de prioridade;
    for(int i = 0; i < 4; i++){
        std::vector<Process*> newLine;
        processLines.push_back(newLine);
    }
    DEBUG_PRINT("ProcessManager(): finalizado")
}

ProcessManager* ProcessManager::getInstance(){
    DEBUG_PRINT("ProcessManager::getInstance: iniciado")
    if(instance == nullptr){
        instance = new ProcessManager();
    }
    DEBUG_PRINT("ProcessManager::getInstance: finalizado")
    return instance;
}


//ProcessManager::~ProcessManager()
//{
//    //dtor
//}

void ProcessManager::InsertTimeStampProcesses(std::pair<int, std::vector<Process*>> timeStamp_ProcessList){
    //Insere o processo na fila correta de acordo com sua prioridade
    /*
        Da especificação:
        As  filas  devem  suportar  no  máximo 1000  processos.
        Portanto,  recomenda-se  utilizar  uma  fila “global”,
        que  permita  avaliar  os  recursos  disponíveis  antes
        da  execução  e  que  facilite  classificar  o  tipo  de processo.
    */
    //Mil processos por fila (total de 4000 processos) ou 1000 processos no total?

    DEBUG_PRINT("ProcessManager::InsertTimeStampProcesses(): iniciado")
    unsigned int i = 0;
    DEBUG_PRINT(" - TimeStamp: \t\t" << timeStamp_ProcessList.first)
    DEBUG_PRINT(" - Novos processos: \t" << timeStamp_ProcessList.second.size())
    while(i < timeStamp_ProcessList.second.size()){
        Process *process = timeStamp_ProcessList.second[i];
        processLines[process->getPriority()].push_back(process);
        processCount++;
        i++;
    }
    DEBUG_PRINT("ProcessManager::InsertTimeStampProcesses(): finalizado")
}

void ProcessManager::InsertBackProcess(Process *process){
    DEBUG_PRINT("ProcessManager::InsertBackProcess(): iniciado")
    if(process->getPriority() > 0 && process->getPriority() < 3){
            process->setPriority(process->getPriority() + 1);
    }
    processLines[process->getPriority()].push_back(process);
    DEBUG_PRINT("ProcessManager::InsertBackProcess(): finalizado")
}

void ProcessManager::PrintLines(){
    DEBUG_PRINT("ProcessManager::PrintLines(): iniciado")
    for(unsigned int i = 0; i < processLines.size(); i++){
        std::cout << "Line [" << i << "]:" << std::endl;
        for(unsigned int j = 0; j < processLines[i].size(); j++){
            std::cout << " - Process [" << j << "]:" << std::endl;
            processLines[i][j]->printProcess();
            std::cout << " ---- " << std::endl;
        }
    }
    DEBUG_PRINT("ProcessManager::PrintLines(): finalizado")
}

Process* ProcessManager::getNextProcess(){
    //Elege o proximo processo a ser executado
    //se houverem processos na fila de processos de tempo real (fila 0)
    //executar todos os processos dessa fila.
    //se não, executar o processo first in na fila i e envelhecê-lo para a fila i+1, i >=1.
    //manter o processo na mesma fila caso i == 3.
    DEBUG_PRINT("ProcessManager::getNextProcess(): iniciado")
    Process *nextProcess = new Process(0,0,0,0,0,0,0,0);
    if(processLines[0].size()){
        nextProcess = processLines[0][0];
        processLines[0].erase(processLines[0].begin());
    }else if(processLines[1].size()){
        nextProcess = processLines[1][0];
        processLines[1].erase(processLines[1].begin());
    }else if(processLines[2].size()){
        nextProcess = processLines[2][0];
        processLines[2].erase(processLines[2].begin());
    }else if(processLines[3].size()){
        nextProcess = processLines[3][0];
        processLines[3].erase(processLines[3].begin());
    }
    DEBUG_PRINT("ProcessManager::getNextProcess(): finalizado")
    return nextProcess;
}


#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
