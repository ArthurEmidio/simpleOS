#include <cstdio>

#include "process.h"

Process::Process(int initTime, int priority, int processingTime, int memoryBlocks,
        bool requestedPrinter, bool requestedDrive, bool requestedScanner, bool requestedModem) :
        _memOffset(-1), _pid(-1), _initTime(initTime), _priority(priority), _processingTime(processingTime),
        _memoryBlocks(memoryBlocks), _requestedPrinter(requestedPrinter), _requestedDrive(requestedDrive),
        _requestedScanner(requestedScanner), _requestedModem(requestedModem)
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
    printf("\tPID: %d\n", _pid);
    printf("\toffset: %d\n", _memOffset);
    printf("\tblocks: %d\n", _memoryBlocks);
    printf("\tpriority: %d\n", _priority);
    printf("\tinit time: %d\n", _initTime);
    printf("\ttime left: %d\n", _processingTime);
    printf("\tprinters: %d\n", _requestedPrinter);
    printf("\tscanners: %d\n", _requestedScanner);
    printf("\tmodems: %d\n", _requestedModem);
    printf("\tdrives: %d\n", _requestedDrive);
}
