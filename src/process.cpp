#include "process.h"

Process::Process(int initTime, int priority, int processingTime, int memoryBlocks,
        int printerId, int driveId, bool requestedScanner, bool requestedModem) :
        _initTime(initTime), _priority(priority), _processingTime(processingTime), _memoryBlocks(memoryBlocks),
        _printerId(printerId), _driveId(driveId), _requestedScanner(requestedScanner), _requestedModem(requestedModem)
{
    _memOffset = -1;
    _pid = -1;
}

int Process::getPid() const
{
    return _pid;
}

int Process::getMemoryOffset() const
{
    return _memOffset;
}

int Process::getMemoryBlocks() const
{
    return _memoryBlocks;
}

int Process::getPriority() const
{
    return _priority;
}

int Process::getInitTime() const
{
    return _initTime;
}

int Process::getProcessingTime() const
{
    return _processingTime;
}

int Process::getPrinterId() const
{
    return _printerId;
}

int Process::getDriveId() const
{
    return _driveId;
}

bool Process::didRequestScanner() const
{
    return _requestedScanner;
}

bool Process::didRequestModem() const
{
    return _requestedModem;
}

void Process::setPid(int pid)
{
    _pid = pid;
}

void Process::setMemoryOffset(int offset)
{
    _memOffset = offset;
}

void Process::setPriority(int priority)
{
    _priority = priority;
}

void Process::setProcessingTime(int processingTime)
{
    _processingTime = processingTime;
}

void Process::printProcess(){
    std::cout << " - pid: " << _pid << std::endl;
    //std::cout << " - memOffset: " << _memOffset << std::endl;
    std::cout << " - initTime: " << _initTime << std::endl;
    std::cout << " - priority: " << _priority << std::endl;
    std::cout << " - processingTime: " << _processingTime << std::endl;
    //std::cout << " - memoryBlocks: " << _memoryBlocks << std::endl;
    //std::cout << " - printerId: " << _printerId << std::endl;
    //std::cout << " - driverId: " << _driveId << std::endl;
    //std::cout << " - requestedScanner: " << _requestedScanner << std::endl;
    //std::cout << " - requestedModen: " << _requestedModem << std::endl;
}
