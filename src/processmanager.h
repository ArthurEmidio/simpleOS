#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <deque>
#include <vector>

#include "process.h"

/*!
 * \brief The \c ProcessManager class manages the priority queues of the processes.
 *
 * The first queue is reserved for real time processes, i.e. the ones with maximum priority.
 */
class ProcessManager
{
    /*!
     * \brief The number of priority queues.
     */
    const int _queuesQuant;

    /*!
     * \brief A vector containing all priority queues.
     */
    std::vector<std::deque<Process*>> _processQueues;

public:
    /*!
     * \brief Default constructor.
     */
    ProcessManager();

    /*!
     * \brief Inserts a set of processes in their respective queues.
     * \param processes The processes to be inserted.
     */
    void insertProcesses(const std::vector<Process*> &processes);

    /*!
     * \brief Reinserts a process, decreasing its priority in case
     * \param process The process to be reinserted.
     */
    void reinsertProcess(Process *process);

    /*!
     * \brief Gets the next process and removes it from its queue.
     * \return The process. If there are no enqueued processes, \c nullptr is returned.
     */
    Process *getNextProcess();

    /*!
     * \brief Gets the total number of enqueued processes.
     * \return The number of enqueued processes.
     */
    int getTotal() const;

    /*!
     * \brief Gets whether there are no enqueued processes.
     * \return \c true if there are no enqueued processes, or \c false otherwise.
     */
    bool isEmpty() const;

    /*!
     * \brief Prints the current status of all priority queues.
     */
    void printQueues();
};

#endif // PROCESSMANAGER_H
