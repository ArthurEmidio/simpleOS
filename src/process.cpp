#include "process.h"

Process::Process(int initTime, int priority, int processingTime, int memoryBlocks,
        int printerId, int driveId, bool requestedScanner, bool requestedModem) :
        _initTime(initTime), _priority(priority), _processingTime(processingTime), _memoryBlocks(memoryBlocks),
        _printerId(printerId), _driveId(driveId), _requestedScanner(requestedScanner), _requestedModem(requestedModem)
{
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

void Process::agePriority()
{
    if(_priority > 0 && _priority < 3)
        _priority++;
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
