#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "process.h"

#include <list>

/*!
 * \brief The \c MemoryManager class is responsible for managing the requests to memory allocation.
 *
 * As default, the memory size is 1024 blocks. The OS reserves 64 blocks for real time processes, and 960 for user
 * processes.
 *
 * The memory is organized as follow: the first N blocks are reserved for real time processes, and the remaining
 * blocks are for user processes.
 */
class MemoryManager
{
    /*!
     * \brief The \c MemorySet struct is an internal representation of a contiguous sequence of memory blocks.
     */
    struct MemorySet
    {
        /*!
         * \brief The memory offset that the memory set starts at.
         */
        int offset;

        /*!
         * \brief How many blocks are contained in the memory set.
         */
        int blocks;

        /*!
         * \brief The process responsible for such memory set. If \c nullptr, it means the memory set is not allocated
         * for any process.
         */
        Process *process;

        /*!
         * \brief Default constructor.
         * \param _offset The memory offset that the memory set starts at.
         * \param _blocks How many blocks are contained in the memory set.
         * \param _process The process responsible for such memory set. If \c nullptr, it means the memory set is not
         * allocated for any process.
         */
        MemorySet(int _offset, int _blocks, Process *_process = nullptr) :
            offset(_offset), blocks(_blocks), process(_process) {}
    };

    /*!
     * \brief How many blocks are reserved for real time processes.
     */
    const int _realTimeBlocks;

    /*!
     * \brief How many blocks are reserved for user processes.
     */
    const int _userBlocks;

    /*!
     * \brief User memory segment. It contains \c MemorySet objects to determine what parts of the memory are free and
     * occupied with a process. It is guaranteed that there are never two adjacent free memory sets.
     */
    std::list<MemorySet> _userSegment;

    /*!
     * \brief Real time memory segment. It contains \c MemorySet objects to determine what parts of the memory are
     * free and occupied with a process. It is guaranteed that there are never two adjacent free memory sets.
     */
    std::list<MemorySet> _realTimeSegment;

    bool _canAllocate(std::list<MemorySet> &segment, Process *process);

    /*!
     * \brief Attempts to allocate a process in the given segment.
     * \param segment The segment (i.e. \c _userSegment or \c _realTimeSegment).
     * \param process The process to be allocated.
     * \return \c true if the process could be allocated, or \c false otherwise.
     */
    bool _allocate(std::list<MemorySet> &segment, Process *process);

    /*!
     * \brief Attempts to deallocate a process in the given segment.
     * \param segment The segment (i.e. \c _userSegment or \c _realTimeSegment).
     * \param process The process to be deallocated.
     * \return \c true if the process could be deallocated, or \c false otherwise. \c false is only returned if
     * the process doesn't have allocated memory.
     */
    bool _deallocate(std::list<MemorySet> &segment, Process *process);

public:
    /*!
     * \brief Default constructor.
     * \param realTimeBlocks How many blocks should be reserved for real time processes.
     * \param userBlocks How many blocks should be reserved for user processes.
     */
    MemoryManager(int realTimeBlocks = 64, int userBlocks = 960);

    /*!
     * \brief Attempts to allocate memory for the given process.
     * \param process The process to be allocated.
     * \return \c true if the process could be allocated, or \c false otherwise.
     */
    bool allocateMemory(Process *process);

    /*!
     * \brief Attempts to deallocate memory for the given process.
     * \param process The process to be deallocated.
     * \return \c true if the process could be deallocated, or \c false otherwise. \c false is only returned if
     * the process doesn't have allocated memory.
     */
    bool deallocateMemory(Process *process);

    bool canAllocate(Process *process);

};

#endif // MEMORYMANAGER_H
