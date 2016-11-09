#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "process.h"
#include <list>

class MemoryManager
{
    struct MemorySet
    {
        int offset;
        int blocks;
        Process *process;
        MemorySet(int _offset, int _blocks, Process *_process = nullptr) :
            offset(_offset), blocks(_blocks), process(_process) {}
    };

    int _userBlocks;

    int _realTimeBlocks;

    std::list<MemorySet> _userSegment;

    std::list<MemorySet> _realTimeSegment;

    bool _allocate(std::list<MemorySet> &segment, Process *process);

    bool _deallocate(std::list<MemorySet> &segment, Process *process);

public:
    MemoryManager(int userBlocks = 960, int realTimeBlocks = 64);

    bool allocateMemory(Process *process);

    bool deallocateMemory(Process *process);

};

#endif // MEMORYMANAGER_H
