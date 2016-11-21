#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
    _resources[ResourceType::MODEM] = ResourceInfo(_modemQuantity);
    _resources[ResourceType::SCANNER] = ResourceInfo(_scannerQuantity);
    _resources[ResourceType::DRIVE] = ResourceInfo(_driveQuantity);
    _resources[ResourceType::PRINTER] = ResourceInfo(_printerQuantity);
}

bool ResourceManager::_canAcquire(ResourceType resourceType)
{
    ResourceInfo &info = _resources[resourceType];
    return info.allocated < info.capacity;
}

void ResourceManager::_addToQueue(ResourceType resourceType, Process *process)
{
    ResourceInfo &info = _resources[resourceType];
    if (info.allocTable.count(process) == 0) {
        info.allocTable[process] = ProcessStatus::IN_QUEUE;
        info.queue.push_back(process);
    }
}

void ResourceManager::_acquire(ResourceType resourceType, Process *process)
{
    ResourceInfo &info = _resources[resourceType];
    info.allocated++;
    info.allocTable[process] = ProcessStatus::WITH_RESOURCE;
}

bool ResourceManager::acquireAll(Process *process)
{
    bool canAcquire = !((process->didRequestModem() && !_canAcquire(ResourceType::MODEM)) ||
                        (process->didRequestScanner() && !_canAcquire(ResourceType::SCANNER)) ||
                        (process->didRequestDrive() && !_canAcquire(ResourceType::DRIVE)) ||
                        (process->didRequestPrinter() && !_canAcquire(ResourceType::PRINTER)));

    if (canAcquire) {
        if (process->didRequestModem()) _acquire(ResourceType::MODEM, process);
        if (process->didRequestScanner()) _acquire(ResourceType::SCANNER, process);
        if (process->didRequestDrive()) _acquire(ResourceType::DRIVE, process);
        if (process->didRequestPrinter()) _acquire(ResourceType::PRINTER, process);
    } else {
        if (process->didRequestModem()) _addToQueue(ResourceType::MODEM, process);
        if (process->didRequestScanner()) _addToQueue(ResourceType::SCANNER, process);
        if (process->didRequestDrive()) _addToQueue(ResourceType::DRIVE, process);
        if (process->didRequestPrinter()) _addToQueue(ResourceType::PRINTER, process);
    }

    return canAcquire;
}

void ResourceManager::_release(ResourceType resourceType, Process *process, MemoryManager &memoryManager)
{
    ResourceInfo &info = _resources[resourceType];

    std::map<Process*, ProcessStatus> &allocTable = info.allocTable;
    if (allocTable.count(process) && allocTable[process] == ProcessStatus::WITH_RESOURCE) {
        info.allocated--;
        allocTable.erase(process);

        // iterate queue until a process can be allocated.
        std::deque<Process*> &queue = info.queue;
        auto it = queue.begin();
        while (it != queue.end()) {
            if (allocTable.count(*it) > 0 && allocTable[*it] == ProcessStatus::IN_QUEUE) {
                if (memoryManager.allocateMemory(process) && acquireAll(*it)) {
                    queue.erase(it); // found a process
                    break;
                } else {
                    memoryManager.deallocateMemory(process);
                }
            } else if (allocTable.count(*it) == 0 || allocTable[*it] == ProcessStatus::WITH_RESOURCE) {
                it = queue.erase(it); // remove old processes
            } else {
                it++;
            }
        }
    }
}

void ResourceManager::releaseAll(Process *process, MemoryManager &memoryManager)
{
    if (process->didRequestModem()) _release(ResourceType::MODEM, process, memoryManager);
    if (process->didRequestScanner()) _release(ResourceType::SCANNER, process, memoryManager);
    if (process->didRequestDrive()) _release(ResourceType::DRIVE, process, memoryManager);
    if (process->didRequestPrinter()) _release(ResourceType::PRINTER, process, memoryManager);
}
