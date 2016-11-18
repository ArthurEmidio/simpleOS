#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "process.h"
#include "processmanager.h"
#include "memorymanager.h"
#include "resourcemanager.h"

#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#ifdef _WIN32
    #include <windows.h>
#endif // __WINDOWS__
/*!
 * \brief \c The Dispatcher class is the context behind the execution of an operating system.
 *
 * The \c Dispatcher is responsible for creating instances of all elements in an operating system and it is the
 * agent responsible for managing the creation of processes.
 */
class Dispatcher
{
    /*!
     * \brief Holds all processes that will be created in the future, sorted by initialization time in decreasing order.
     */
    std::vector<Process*> _futureProcesses;

    /*!
     * \brief Gets the processes that should be initialized by the operating system in the next time slot that contains
     * at least a process to be started.
     *
     * For instance, suppose there are 3 processes that should start in the next time slot (e.g. 5). This method will
     * return a pair where the first element is 5, and the second element is a vector containing such 3 processes.
     * \return The processes that should be started in the next time slot. If there are no more processes to be
     * initialized, a pair with the first element as -1 will be returned.
     */
    std::pair<int, std::vector<Process*>> _getNextProcesses();

public:
    /*!
     * \brief Default constructor.
     * \param processes All processes that the OS will handle.
     */
    Dispatcher(std::vector<Process*> processes);

    /*!
     * \brief Executes the OS.
     */
    void run();

    /*!
     * \brief Simulates CPU executing process.
     */
    void toCPU(Process*);

    /*!
     * \brief Simulates quantum time.
     */
    int _quantum;
    int _currentTimeStamp;

};

#endif // DISPATCHER_H
