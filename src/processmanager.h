#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <vector>
#include <queue>
#include <iostream>

#include "process.h"

class ProcessManager
{
    public:
        static void InsertTimeStampProcesses(std::pair<int, std::vector<Process*>>);
        static void InsertBackProcess(Process *process);
        static Process* getNextProcess();
        static void PrintLines();
        static ProcessManager* getInstance();

    protected:

    private:
        //Singleton
        ProcessManager();
        static ProcessManager *instance;
        static int processCount;
        //vetor contendo as 4 filas de prioridade
        static std::vector<std::vector<Process*>> processLines;
};

#endif // PROCESSMANAGER_H
