#ifndef RESOURCEMANEGER_H
#define RESOURCEMANEGER_H

#include "process.h"

#include <set>
#include <queue>

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
 */
class ResourceManager
{
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
     * \brief Contains the processes that have a printer as acquired.
     */
    std::set<Process*> _printerAllocation;

    /*!
     * \brief Contains the SATA drives that have a printer as acquired.
     */
    std::set<Process*> _driveAllocation;

    /*!
     * \brief Contains the processes that have a scanner as acquired.
     */
    std::set<Process*> _scannerAllocation;

    /*!
     * \brief Contains the processes that have a modem as acquired.
     */
    std::set<Process*> _modemAllocation;

    /*!
     * \brief The queue of processes to acquire a printer.
     */
    std::queue<Process*> _printerQueue;

    /*!
     * \brief The queue of processes to acquire a SATA drive.
     */
    std::queue<Process*> _driveQueue;

    /*!
     * \brief The queue of processes to acquire a scanner.
     */
    std::queue<Process*> _scannerQueue;

    /*!
     * \brief The queue of processes to acquire a modem.
     */
    std::queue<Process*> _modemQueue;

    /*!
     * \brief Attemps to acquire a resource.
     * \param quant How many resources of such type exist.
     * \param alloc The allocation set for the specific resource (e.g. \c printerAllocation for printers).
     * \param waitQueue The queue of processes to acquire the specific resource.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool _acquire(unsigned int quant, std::set<Process*> &alloc, std::queue<Process*> &waitQueue, Process *process);

    /*!
     * \brief Releases a resource.
     * \param alloc The allocation set for the specific resource (e.g. \c printerAllocation for printers).
     * \param waitQueue The queue of processes to acquire the specific resource.
     * \param process The process that wants to release the resource.
     * \return The enqueued process that was allocated for this resource after \c process released the resource. If
     * there is none, \c nullptr is returned.
     *
     * If this method is called when \c process doesn't have the resource acquired, then this method doesn't have any
     * effects, and \c nullptr is returned.
     */
    Process* _release(std::set<Process*> &alloc, std::queue<Process*> &waitQueue, Process *process);

public:
    /*!
     * \brief Default constructor.
     */
    ResourceManager();

    /*!
     * \brief Attemps to acquire a resource.
     * \param resourceType The resource type.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool acquire(ResourceType resourceType, Process *process);

    /*!
     * \brief Attemps to acquire all resources at once.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resources could be acquired, or \c false otherwise.
     */
    bool acquireAll(Process *process);

    /*!
     * \brief Attemps to release a resource.
     * \param resourceType The resource type.
     * \param process The process that wants to release the resource.
     * \return \c true if the process released the resource. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool release(ResourceType resourceType, Process *process);

    /*!
     * \brief Attemps to release all resource.
     * \param process The process that wants to release the resource.
     */
    void releaseAll(Process *process);

};

#endif // RESOURCEMANEGER_H
