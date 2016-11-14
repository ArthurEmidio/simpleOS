#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
}

bool ResourceManager::acquire(ResourceType resourceType, Process *process)
{
    switch (resourceType) {
        case ResourceType::PRINTER:
            return _acquire(_printerQuantity, _printerAllocation, _printerQueue, process);
        case ResourceType::DRIVE:
            return _acquire(_driveQuantity, _driveAllocation, _driveQueue, process);
        case ResourceType::SCANNER:
            return _acquire(_scannerQuantity, _scannerAllocation, _scannerQueue, process);
        case ResourceType::MODEM:
            return _acquire(_modemQuantity, _modemAllocation, _modemQueue, process);
    }

    return false;
}

bool ResourceManager::acquireAll(Process *process)
{
    if(process->didRequestModem()){
        if(acquire(ResourceType::MODEM, process));
        else return false;
    }
    if(process->didRequestScanner()){
        if(acquire(ResourceType::SCANNER, process));
        else{
            release(ResourceType::MODEM, process);
            return false;
        }
    }
    if(process->getDriveId()){
        if(acquire(ResourceType::DRIVE, process));
        else{
            release(ResourceType::MODEM, process);
            release(ResourceType::SCANNER, process);
            return false;
        }
    }
    if(process->getPrinterId()){
        if(acquire(ResourceType::PRINTER, process));
        else{
            release(ResourceType::MODEM, process);
            release(ResourceType::SCANNER, process);
            release(ResourceType::DRIVE, process);
            return false;
        }
    }
    return true;
}


bool ResourceManager::_acquire(unsigned int quant, std::set<Process*> &alloc, std::queue<Process*> &waitQueue, Process *process)
{
    if (alloc.count(process) > 0) {
        return true; // when the process already has the resource
    }

    if (alloc.size() < quant) {
        alloc.insert(process);
        return true;
    }

    // the resource is full
    waitQueue.push(process);
    return false;
}

bool ResourceManager::release(ResourceType resourceType, Process *process)
{
    switch (resourceType) {
        case ResourceType::PRINTER:
            return _release(_printerAllocation, _printerQueue, process)? true: false;
        case ResourceType::DRIVE:
            return _release(_driveAllocation, _driveQueue, process)? true: false;
        case ResourceType::SCANNER:
            return _release(_scannerAllocation, _scannerQueue, process)? true: false;
        case ResourceType::MODEM:
            return _release(_modemAllocation, _modemQueue, process)? true: false;
    }

    return false;
}

bool ResourceManager::releaseAll(Process *process)
{
    if(process->didRequestModem()) release(ResourceType::MODEM, process);
    if(process->didRequestScanner()) release(ResourceType::SCANNER, process);
    if(process->getDriveId()) release(ResourceType::DRIVE, process);
    if(process->getPrinterId()) release(ResourceType::PRINTER, process);
    return true;
}

Process* ResourceManager::_release(std::set<Process*> &alloc, std::queue<Process*> &waitQueue, Process *process)
{
    if (alloc.count(process) == 0) {
        return nullptr;
    }

    alloc.erase(process);
    if (!waitQueue.empty()) {
        Process *nextProcess = waitQueue.front();
        waitQueue.pop();
        alloc.insert(nextProcess);
        return nextProcess;
    }

    return nullptr;
}
