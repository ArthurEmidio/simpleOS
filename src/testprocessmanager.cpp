#include "testprocessmanager.h"

#include "processmanager.h"
#include "process.h"

TestProcessManager::TestProcessManager()
{
    ProcessManager manager;

    Process *p1 = new Process(1, 0, 0, 0, 0, 0, 0, 0);
    Process *p2 = new Process(2, 1, 0, 0, 0, 0, 0, 0);
    Process *p3 = new Process(3, 3, 0, 0, 0, 0, 0, 0);

    std::vector<Process*> ps = {p3, p2, p1};

    manager.insertProcesses(ps);
//    manager.erase(manager.begin());

    for (auto it = manager.begin(); it != manager.end(); it++) {
        (*it)->printProcess();
        std::cout << std::endl;
    }
}
