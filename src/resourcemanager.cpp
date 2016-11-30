#include "resourcemanager.h"
#include <cassert>

ResourceManager::ResourceManager()
{
    _resources[ResourceType::MODEM] = ResourceInfo(_modemQuantity);
    _resources[ResourceType::SCANNER] = ResourceInfo(_scannerQuantity);
    _resources[ResourceType::DRIVE] = ResourceInfo(_driveQuantity);
    _resources[ResourceType::PRINTER] = ResourceInfo(_printerQuantity);
}

bool ResourceManager::_canAcquire(ResourceType resourceType, Process *process)
{
    ResourceInfo &info = _resources[resourceType];
    if (info.allocTable.count(process) == 1 && info.allocTable[process] == ProcessStatus::WITH_RESOURCE) {
        return true;
    }

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
    if (info.allocTable.count(process) == 0 || info.allocTable[process] == ProcessStatus::IN_QUEUE) {
        info.allocated++;
        info.allocTable[process] = ProcessStatus::WITH_RESOURCE;
    }
}

bool ResourceManager::canAcquire(Process *process)
{
    bool result =  !((process->didRequestModem()   && !_canAcquire(ResourceType::MODEM, process))    ||
                    (process->didRequestScanner()  && !_canAcquire(ResourceType::SCANNER, process))  ||
                    (process->didRequestDrive()    && !_canAcquire(ResourceType::DRIVE, process))    ||
                    (process->didRequestPrinter()  && !_canAcquire(ResourceType::PRINTER, process)));

    if (!result) {
        if (process->didRequestModem()) _addToQueue(ResourceType::MODEM, process);
        if (process->didRequestScanner()) _addToQueue(ResourceType::SCANNER, process);
        if (process->didRequestDrive()) _addToQueue(ResourceType::DRIVE, process);
        if (process->didRequestPrinter()) _addToQueue(ResourceType::PRINTER, process);
    }

    return result;
}

bool ResourceManager::acquireAll(Process *process)
{
    bool success = canAcquire(process);

    if (success) {
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

    return success;
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
            Process *queuedProcess = *it;
            if (memoryManager.canAllocate(queuedProcess) && canAcquire(queuedProcess)) {
                memoryManager.allocateMemory(queuedProcess);
                acquireAll(queuedProcess);
            }
            it++;
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

void ResourceManager::printResources(){
    ResourceInfo *info = &_resources[ResourceType::PRINTER];
    printf("--- Filas de recursos: ---\n");
    for(int i = 0; i < 4; i++){
            switch(i){
                case 0: printf(" - PRINTER\n"); break;
                case 1: printf(" - DRIVE\n");
                        info = &_resources[ResourceType::DRIVE];
                        break;
                case 2: printf(" - SCANNER\n");
                        info = &_resources[ResourceType::SCANNER];
                        break;
                case 3: printf(" - MODEM\n");
                        info = &_resources[ResourceType::MODEM];
                        break;
            }
            printf("   - capacity: %d\n", info->capacity);
            printf("   - process using: ");
            for (auto it = info->allocTable.begin(); it != info->allocTable.end(); it++) {
                if (WITH_RESOURCE == it->second){
                    printf("PID %d", it->first->getPid());
                    printf(" | ");
                }
            }
            printf("\n");
            printf("   - processes waiting: ");
            for (auto it = info->allocTable.begin(); it != info->allocTable.end(); it++) {
                if (IN_QUEUE == it->second){
                    printf("PID %d", it->first->getPid());
                    printf(" | ");
                }
            }
            printf("\n");
    }
    printf("--------------------------\n");
}
