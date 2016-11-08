#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <vector>

class ProcessManager
{
    public:
        ProcessManager();
        virtual ~ProcessManager();

        void InsertProcess(Process*);
        void ExecuteNext();

    protected:

    private:
        int processCount;
        //vetor contendo as 4 filas de prioridade
        std::vector<std::vector<Process*>> processLines;
};

#endif // PROCESSMANAGER_H
