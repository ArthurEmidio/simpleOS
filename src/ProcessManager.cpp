#include "ProcessManager.h"

ProcessManager::ProcessManager()
{
    processLines.push_back(std::vector<Process*>);//prioridade 0//processos de tempo real
    processLines.push_back(std::vector<Process*>);//prioridade 1 > processos de usuário
    processLines.push_back(std::vector<Process*>);//prioridade 2
    processLines.push_back(std::vector<Process*>);//prioridade 3
    processCount = 0;
}

ProcessManager::~ProcessManager()
{
    //dtor
}

void ProcessManager::InsertProcess(Process* process){
    //Insere o processo na fila correta de acordo com sua prioridade
    processLines[process->getPriority()].push_back(process);

    /*
        Da especificação:
        As  filas  devem  suportar  no  máximo 1000  processos.
        Portanto,  recomenda-se  utilizar  uma  fila “global”,
        que  permita  avaliar  os  recursos  disponíveis  antes
        da  execução  e  que  facilite  classificar  o  tipo  de processo.
    */
    //Mil processos por fila (total de 4000 processos) ou 1000 processos no total?
    processCount++;
}

void Process::ExecuteNext(){
    //Executa o proximo processo
    //se houverem processos na fila de processos de tempo real (fila 0)
    //executar todos os processos dessa fila.
    //se não, executar o processo first in na fila i e envelhecê-lo para a fila i+1, i >=1.
    //manter o processo na mesma fila caso i == 3.
}
