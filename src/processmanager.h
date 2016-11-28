#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <deque>
#include <vector>
#include <cstddef>

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
    const int _queuesQuant = 4;

    /*!
     * \brief A vector containing all priority queues.
     */
    std::vector<std::deque<Process*>> _processQueues;

public:
    class iterator : public std::iterator<std::input_iterator_tag, Process*, ptrdiff_t, Process**, Process*>
    {
        friend class ProcessManager;

        int currQueue;
        std::vector<std::deque<Process*>> &queues;
        std::deque<Process*>::iterator currIt;

        explicit iterator(int _currQueue, std::vector<std::deque<Process*>> &_queues) :
            currQueue(_currQueue), queues(_queues)
        {
            if (currQueue >= queues.size()) {
                currIt = queues.back().end();
            } else {
                currIt = queues[currQueue].begin();
                if (currIt == queues[currQueue].end()) ++(*this);
            }
        }

    public:
        iterator& operator++()
        {
            if (currQueue >= queues.size()) {
                currIt = queues[currQueue - 1].end();
            } else {
                if (currIt != queues[currQueue].end()) currIt++;
                while (currQueue < queues.size() - 1 && currIt == queues[currQueue].end()) {
                    currIt = queues[++currQueue].begin();
                }
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator ret = *this;
            ++(*this);
            return ret;
        }

        bool operator==(iterator other) const
        {
            return currIt == other.currIt;
        }

        bool operator!=(iterator other) const
        {
            return !(*this == other);
        }

        Process* operator*()
        {
            return *currIt;
        }
    };

    iterator begin()
    {
        return iterator(0, _processQueues);
    }

    iterator end()
    {
        return iterator(_queuesQuant, _processQueues);
    }

    void erase(iterator it)
    {
        if (it != end()) {
            it.queues[it.currQueue].erase(it.currIt);
        }
    }

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
