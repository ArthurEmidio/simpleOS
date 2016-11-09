#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
    _printerAllocation.assign(_printerQuantity, -1);
    _driveAllocation.assign(_driveQuantity, -1);
    _scannerAllocation.assign(_scannerQuantity, -1);
    _modemAllocation.assign(_modemQuantity, -1);
}

bool ResourceManager::_acquire(int resourceId, std::vector<int> &allocTable, Process *process)
{
    if (resourceId > 0 && resourceId <= allocTable.size()) {
        if (allocTable[resourceId] == -1 || allocTable[resourceId] == process->getPid()) {
            allocTable[resourceId] = process->getPid();
            return true;
        }
    }

    return false;
}

bool ResourceManager::_release(int resourceId, std::vector<int> &allocTable, Process *process)
{
    if (resourceId > 0 && resourceId <= allocTable.size()) {
        if (allocTable[resourceId] == process->getPid()) {
            allocTable[resourceId] = -1;
            return true;
        }
    }

    return false;
}

bool ResourceManager::acquirePrinter(int printerId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::PRINTER, allocTable);
    return _acquire(printerId, allocTable, process);
}

bool ResourceManager::acquireDrive(int driveId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::DRIVE, allocTable);
    return _acquire(driveId, allocTable, process);
}

bool ResourceManager::acquireScanner(int scannerId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::SCANNER, allocTable);
    return _acquire(scannerId, allocTable, process);
}

bool ResourceManager::acquireModem(int modemId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::MODEM, allocTable);
    return _acquire(modemId, allocTable, process);
}

bool ResourceManager::releasePrinter(int printerId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::PRINTER, allocTable);
    return _release(printerId, allocTable, process);
}

bool ResourceManager::releaseDrive(int driveId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::DRIVE, allocTable);
    return _release(driveId, allocTable, process);
}

bool ResourceManager::releaseScanner(int scannerId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::SCANNER, allocTable);
    return _release(scannerId, allocTable, process);
}

bool ResourceManager::releaseModem(int modemId, Process *process)
{
    std::vector<int> allocTable;
    _getAllocTable(ResourceManager::ResourceType::MODEM, allocTable);
    return _release(modemId, allocTable, process);
}

void ResourceManager::_getAllocTable(ResourceManager::ResourceType type, std::vector<int> &allocTable)
{
    switch (type) {
        case PRINTER:
            allocTable = _printerAllocation;
            break;
        case DRIVE:
            allocTable = _driveAllocation;
            break;
        case SCANNER:
            allocTable = _scannerAllocation;
            break;
        case MODEM:
            allocTable = _modemAllocation;
            break;
    }
}
