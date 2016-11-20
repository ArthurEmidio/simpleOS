#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <vector>
#include <queue>
#include <iostream>

#include "process.h"

class ProcessManager
{
    int _processCount;

    //vetor contendo as 4 filas de prioridade
    std::vector<std::vector<Process*>> _processLines;

public:
    ProcessManager();

    void insertTimestampProcesses(std::pair<int, std::vector<Process*>> timestampProcessList);

    void insertBackProcess(Process *process);

    Process* getNextProcess();

    void printLines();

};

#endif // PROCESSMANAGER_H
