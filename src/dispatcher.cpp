#include "dispatcher.h"

Dispatcher::Dispatcher(std::vector<Process*> processes)
{
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

}
