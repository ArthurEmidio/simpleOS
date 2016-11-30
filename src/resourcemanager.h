#ifndef RESOURCEMANEGER_H
#define RESOURCEMANEGER_H

#include "process.h"
#include "memorymanager.h"

#include <cstdio>
#include <deque>
#include <map>


/*!
 * \brief The \c ResourceType enum lists all distinct types of resources.
 */
enum class ResourceType
{
    PRINTER, /*!< Printer device. */
    DRIVE,   /*!< SATA drive device. */
    SCANNER, /*!< Scanner device. */
    MODEM    /*!< Modem device. */
};

/*!
 * \brief The \c ResourceManager class is responsible for managing all the resources of the operating system.
 *
 * Currently, there are four types of resources: printer, SATA drive, scanner, and modem.
 *
 * Each resource has an internal waiting queue of processes that cannot obtain the resource. When a resource is
 * released, the manager attempts to release an item from the queue, following the queue order.
 */
class ResourceManager
{
    /*!
     * \brief The \c ProcessStatus enum contains the possible status that a process is considered in terms of a
     * resource.
     */
    enum ProcessStatus
    {
        IN_QUEUE,
        WITH_RESOURCE
    };

    /*!
     * \brief The \c ResourceInfo struct is an internal representation containing information about a resource type.
     */
    struct ResourceInfo
    {
        int capacity;
        int allocated;
        std::map<Process*, ProcessStatus> allocTable;
        std::deque<Process*> queue;
        ResourceInfo(int _capacity = 0) : capacity(_capacity), allocated(0) {}
    };

    /*!
     * \brief Holds the number of printers.
     */
    const int _printerQuantity = 2;

    /*!
     * \brief Holds the number of SATA drives.
     */
    const int _driveQuantity = 2;

    /*!
     * \brief Holds the number of scanners.
     */
    const int _scannerQuantity = 1;

    /*!
     * \brief Holds the number of modems.
     */
    const int _modemQuantity = 1;

    /*!
     * \brief Maps the resource type with its information.
     */
    std::map<ResourceType, ResourceInfo> _resources;

    /*!
     * \brief Acquires a resource.
     * \param resourceType The resource type.
     * \param process The process that wil acquire the resource.
     */
    void _acquire(ResourceType resourceType, Process *process);

    /*!
     * \brief Releases a resource.
     * \param resourceType The resource type.
     * \param process The process which will release the resource.
     * \param memoryManager The memory manager.
     */
    void _release(ResourceType resourceType, Process *process, MemoryManager &memoryManager);

    /*!
     * \brief Gets whether the resource is free.
     * \param resourceType The resource type.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource can be acquired, or \c false otherwise.
     */
    bool _canAcquire(ResourceType resourceType, Process *process);

    /*!
     * \brief Adds a process to the waiting queue of the given resource.
     * \param resourceType The resource type.
     * \param process The process to be enqueued.
     */
    void _addToQueue(ResourceType resourceType, Process *process);

public:
    /*!
     * \brief Default constructor.
     */
    ResourceManager();

    /*!
     * \brief Attemps to acquire all resources at once.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resources could be acquired, or \c false otherwise.
     *
     * In case \c false is returned, this method does not acquire any resources.
     */
    bool acquireAll(Process *process);

    /*!
     * \brief Releases all resources from a given process.
     *
     * If there are processes in the queue of any freed resource, this method attempts to allocate all resources
     * for each process, following the queue order.
     * \param process The process will have its resources released.
     * \param memoryManager The memory manager. The manager is necessary because this methods tries to allocate
     * procceses in the queue of the freed resource. However, this is only attempted if the process is allocated
     * in memory.
     */
    void releaseAll(Process *process, MemoryManager &memoryManager);

    /*!
     * \brief Returns whether the resources can be acquired.
     *
     * Note that this method does not acquire the resources, it only checks.
     * \param process The process that wants to have the resources acquired.
     * \return \c true if all the resources can be acquired, or \c false otherwise.
     */
    bool canAcquire(Process *process);

    /*!
     * \brief Prints which resource is allocated to which process.
     */
    void printResources();
};

#endif // RESOURCEMANEGER_H
