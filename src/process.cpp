#include "process.h"

Process::Process(int initTime, int priority, int processingTime, int memoryBlocks,
        bool requestedPrinter, bool requestedDrive, bool requestedScanner, bool requestedModem) :
        _initTime(initTime), _priority(priority), _processingTime(processingTime), _memoryBlocks(memoryBlocks),
        _requestedPrinter(requestedPrinter), _requestedDrive(requestedDrive), _requestedScanner(requestedScanner),
        _requestedModem(requestedModem)
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

bool Process::didRequestPrinter() const
{
    return _requestedPrinter;
}

bool Process::didRequestDrive() const
{
    return _requestedDrive;
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

void Process::printProcess()
{
    printf("PID: %d\n", _pid);
    printf("offset: %d\n", _memOffset);
    printf("blocks: %d\n", _memoryBlocks);
    printf("priority: %d\n", _priority);
    printf("time: %d\n", _initTime);
    printf("printers: %d\n", _requestedPrinter);
    printf("scanners: %d\n", _requestedScanner);
    printf("modems: %d\n", _requestedModem);
    printf("drives: %d\n", _requestedDrive);
}
