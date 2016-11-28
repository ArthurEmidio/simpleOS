#include <iostream>

#include "processmanager.h"

ProcessManager::ProcessManager()
{
    _processQueues.resize(_queuesQuant);
}

void ProcessManager::insertProcesses(const std::vector<Process*> &processes)
{
    for (Process *process : processes) {
        _processQueues[process->getPriority()].push_back(process);
    }
}

void ProcessManager::reinsertProcess(Process *process)
{
    if (process->getPriority() > 0 && process->getPriority() < _queuesQuant - 1) {
        process->setPriority(process->getPriority() + 1);
    }
    _processQueues[process->getPriority()].push_back(process);
}

int ProcessManager::getTotal() const
{
    int total = 0;
    for (const std::deque<Process*> &queue : _processQueues) {
        total += queue.size();
    }
    return total;
}

bool ProcessManager::isEmpty() const
{
    return getTotal() == 0;
}

void ProcessManager::printQueues()
{
    for (int i = 0; i < _processQueues.size(); i++) {
        std::cout << "Fila [" << i << "]:" << std::endl;
        for (int j = 0; j < _processQueues[i].size(); j++) {
            std::cout << " - Processo [" << j << "]:" << std::endl;
            _processQueues[i][j]->printProcess();
            std::cout << " ---- " << std::endl;
        }
    }
}
