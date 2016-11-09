#ifndef RESOURCEMANEGER_H
#define RESOURCEMANEGER_H

#include "process.h"
#include <vector>

/*!
 * \brief The \c ResourceManager class is responsible for managing all the resources of the operating system.
 *
 * Currently, there are four types of resources: printer, SATA drive, scanner, and modem.
 */
class ResourceManager
{
    /*!
     * \brief The \c ResourceType enum lists all distinct types of resources.
     */
    enum ResourceType
    {
        PRINTER, DRIVE, SCANNER, MODEM
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
     * \brief The allocation table for printers.
     */
    std::vector<int> _printerAllocation;

    /*!
     * \brief The allocation table for SATA drives.
     */
    std::vector<int> _driveAllocation;

    /*!
     * \brief The allocation table for scanners.
     */
    std::vector<int> _scannerAllocation;

    /*!
     * \brief The allocation table for modems.
     */
    std::vector<int> _modemAllocation;

    /*!
     * \brief Attemps to acquire a resource.
     * \param resourceId The resource identifier.
     * \param allocTable The allocation table for the specific resource (e.g. \c printerAllocation for printers).
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool _acquire(int resourceId, std::vector<int> &allocTable, Process *process);

    /*!
     * \brief Attemps to release a resource.
     * \param resourceId The resource identifier.
     * \param allocTable The allocation table for the specific resource (e.g. \c printerAllocation for printers).
     * \param process The process that wants to release the resource.
     * \return \c true if the process released the resource. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool _release(int resourceId, std::vector<int> &allocTable, Process *process);

    /*!
     * \brief Gets the allocation table based on the type of resource.
     * \param type The resource type.
     * \param allocTable[out] The allocation table.
     */
    void _getAllocTable(ResourceManager::ResourceType type, std::vector<int> &allocTable);

public:
    /*!
     * \brief Default constructor.
     */
    ResourceManager();

    /*!
     * \brief Attemps to acquire a printer device.
     * \param printerId The printer identifier.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool acquirePrinter(int printerId, Process *process);

    /*!
     * \brief Attemps to acquire a SATA drive device.
     * \param printerId The drive identifier.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool acquireDrive(int driveId, Process *process);

    /*!
     * \brief Attemps to acquire a scanner device.
     * \param printerId The scanner identifier.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool acquireScanner(int scannerId, Process *process);

    /*!
     * \brief Attemps to acquire a modem device.
     * \param printerId The modem identifier.
     * \param process The process that wants to acquire the resource.
     * \return \c true if the resource could be acquired, or \c false otherwise.
     */
    bool acquireModem(int modemId, Process *process);

    /*!
     * \brief Attemps to release a printer device.
     * \param printerId The printer identifier.
     * \param process The process that wants to release the resource.
     * \return \c true if the resource could be released. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool releasePrinter(int printerId, Process *process);

    /*!
     * \brief Attemps to release a SATA drive device.
     * \param printerId The drive identifier.
     * \param process The process that wants to release the resource.
     * \return \c true if the resource could be released. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool releaseDrive(int driveId, Process *process);

    /*!
     * \brief Attemps to release a scanner device.
     * \param printerId The scanner identifier.
     * \param process The process that wants to release the resource.
     * \return \c true if the resource could be released. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool releaseScanner(int scannerId, Process *process);

    /*!
     * \brief Attemps to release a modem device.
     * \param printerId The modem identifier.
     * \param process The process that wants to release the resource.
     * \return \c true if the resource could be released. This method can return \c false in case the process
     * doesn't didn't have the resource as acquired.
     */
    bool releaseModem(int modemId, Process *process);

};

#endif // RESOURCEMANEGER_H
