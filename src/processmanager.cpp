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

ProcessManager::ProcessManager() : _processCount(0)
{
    DEBUG_PRINT("ProcessManager(): iniciado")
    //cria as 4 filas de prioridade;
    for(int i = 0; i < 4; i++){
        std::vector<Process*> newLine;
        _processLines.push_back(newLine);
    }
    DEBUG_PRINT("ProcessManager(): finalizado")
}

void ProcessManager::insertTimestampProcesses(std::pair<int, std::vector<Process*>> timestampProcessList)
{
    //Insere o processo na fila correta de acordo com sua prioridade
    /*
        Da especificacao:
        As  filas  devem  suportar  no  maximo 1000  processos.
        Portanto,  recomenda-se  utilizar  uma  fila “global”,
        que  permita  avaliar  os  recursos  disponiveis  antes
        da  execucao  e  que  facilite  classificar  o  tipo  de processo.
    */
    //Mil processos por fila (total de 4000 processos) ou 1000 processos no total?

    DEBUG_PRINT("ProcessManager::InsertTimeStampProcesses(): iniciado")
    unsigned int i = 0;
    DEBUG_PRINT(" - TimeStamp: \t\t" << timestampProcessList.first)
    DEBUG_PRINT(" - Novos processos: \t" << timestampProcessList.second.size())
    while(i < timestampProcessList.second.size()){
        Process *process = timestampProcessList.second[i];
        _processLines[process->getPriority()].push_back(process);
        _processCount++;
        i++;
    }
    DEBUG_PRINT("ProcessManager::InsertTimeStampProcesses(): finalizado")
}

void ProcessManager::insertBackProcess(Process *process){
    DEBUG_PRINT("ProcessManager::InsertBackProcess(): iniciado")
    if(process->getPriority() > 0 && process->getPriority() < 3){
            process->setPriority(process->getPriority() + 1);
    }
    _processLines[process->getPriority()].push_back(process);
    DEBUG_PRINT("ProcessManager::InsertBackProcess(): finalizado")
}

void ProcessManager::printLines(){
    DEBUG_PRINT("ProcessManager::PrintLines(): iniciado")
    for(unsigned int i = 0; i < _processLines.size(); i++){
        std::cout << "Line [" << i << "]:" << std::endl;
        for(unsigned int j = 0; j < _processLines[i].size(); j++){
            std::cout << " - Process [" << j << "]:" << std::endl;
            _processLines[i][j]->printProcess();
            std::cout << " ---- " << std::endl;
        }
    }
    DEBUG_PRINT("ProcessManager::PrintLines(): finalizado")
}

Process* ProcessManager::getNextProcess(){
    //Elege o proximo processo a ser executado
    //se houverem processos na fila de processos de tempo real (fila 0)
    //executar todos os processos dessa fila.
    //se nao, executar o processo first in na fila i e envelhece-lo para a fila i+1, i >=1.
    //manter o processo na mesma fila caso i == 3.
    DEBUG_PRINT("ProcessManager::getNextProcess(): iniciado")
    Process *nextProcess = new Process(0,0,0,0,0,0,0,0);
    if(_processLines[0].size()){
        nextProcess = _processLines[0][0];
        _processLines[0].erase(_processLines[0].begin());
    }else if(_processLines[1].size()){
        nextProcess = _processLines[1][0];
        _processLines[1].erase(_processLines[1].begin());
    }else if(_processLines[2].size()){
        nextProcess = _processLines[2][0];
        _processLines[2].erase(_processLines[2].begin());
    }else if(_processLines[3].size()){
        nextProcess = _processLines[3][0];
        _processLines[3].erase(_processLines[3].begin());
    }
    DEBUG_PRINT("ProcessManager::getNextProcess(): finalizado")
    return nextProcess;
}


#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
