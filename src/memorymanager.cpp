#include "memorymanager.h"

MemoryManager::MemoryManager(int userBlocks, int realTimeBlocks) :
    _userBlocks(userBlocks), _realTimeBlocks(realTimeBlocks)
{
    _userSegment.push_back(MemorySet(0, userBlocks));
    _realTimeSegment.push_back(MemorySet(0, realTimeBlocks));
}

bool MemoryManager::allocateMemory(Process *process)
{
    if (process->getPriority() == 0) {
        return _allocate(_realTimeSegment, process);
    } else {
        return _allocate(_userSegment, process);
    }
}

bool MemoryManager::_allocate(std::list<MemorySet> &segment, Process *process)
{
    int blocks = process->getMemoryBlocks();

    for (auto it = segment.begin(); it != segment.end(); it++) {
        MemorySet &memorySet = *it;
        if (memorySet.process == nullptr && memorySet.blocks >= blocks) {
            if (blocks + 1 < memorySet.blocks) {
                MemorySet newMemSet(memorySet.offset + memorySet.blocks + 1, memorySet.blocks - blocks, nullptr);
                segment.insert(next(it), newMemSet);
            }

            memorySet.blocks = blocks;
            memorySet.process = process;
            process->setMemoryOffset(memorySet.offset);
            return true;
        }
    }

    return false;
}

bool MemoryManager::deallocateMemory(Process *process)
{
    if (process->getPriority() == 0) {
        return _deallocate(_realTimeSegment, process);
    } else {
        return _deallocate(_userSegment, process);
    }
}

bool MemoryManager::_deallocate(std::list<MemorySet> &segment, Process *process)
{
    for (auto it = segment.begin(); it != segment.end(); it++) {
        MemorySet &memorySet = *it;
        if (memorySet.process == process) {
            // TODO: implement
            // set memory set as empty and merge if possible (i.e. can merge with 1 or 2).
            return true;
        }
    }

    return false;
}
