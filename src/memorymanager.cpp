#include "memorymanager.h"

MemoryManager::MemoryManager(int realTimeBlocks, int userBlocks) :
    _realTimeBlocks(realTimeBlocks), _userBlocks(userBlocks)
{
    _realTimeSegment.push_back(MemorySet(0, realTimeBlocks));
    _userSegment.push_back(MemorySet(realTimeBlocks, userBlocks));
}

bool MemoryManager::_canAllocate(std::list<MemorySet> &segment, Process *process)
{
    int blocks = process->getMemoryBlocks();

    for (auto it = segment.begin(); it != segment.end(); it++) {
        MemorySet &memorySet = *it;
        if (memorySet.process == nullptr && memorySet.blocks >= blocks) {
            return true;
        }
    }
    return false;
}

bool MemoryManager::canAllocate(Process *process)
{
    if (process->getMemoryOffset() != -1) return true;

    if (process->getPriority() == 0) {
        return _canAllocate(_realTimeSegment, process);
    } else {
        return _canAllocate(_userSegment, process);
    }
}

bool MemoryManager::allocateMemory(Process *process)
{
    if (process->getMemoryOffset() != -1) return true;

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
            if (blocks + 1 <= memorySet.blocks) {
                MemorySet newMemSet(memorySet.offset + blocks, memorySet.blocks - blocks, nullptr);
                segment.insert(std::next(it), newMemSet);
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
            memorySet.process = nullptr;
            process->setMemoryOffset(-1);

            if (it != segment.begin()) {
                MemorySet &prev = *std::prev(it);
                if (prev.process == nullptr) {
                    memorySet.offset = prev.offset;
                    memorySet.blocks += prev.blocks;
                    segment.erase(std::prev(it));
                }
            }

            if (std::next(it) != segment.end()) {
                MemorySet &next = *std::next(it);
                if (next.process == nullptr) {
                    memorySet.blocks += next.blocks;
                    segment.erase(std::next(it));
                }
            }

            return true;
        }
    }

    return false;
}

void MemoryManager::printMemory(){
    printf("---     Memoria:    ---\n");
    printf(" - RealTimeSegment: ");
    for (auto it = _realTimeSegment.begin(); it != _realTimeSegment.end(); it++){
        printf("%d ", it->offset);
        if(it->process) printf("PID%d ", it->process->getPid());
        else printf("livre ");
        printf("%d|", it->blocks + it->offset - 1);
    }
    printf("\n");
    printf(" - UserSegment: ");
    for (auto it = _userSegment.begin(); it != _userSegment.end(); it++){
        printf("%d ", it->offset);
        if(it->process) printf("PID%d ", it->process->getPid());
        else printf("livre ");
        printf("%d|", it->blocks + it->offset - 1);
    }
    printf("\n");
    printf("-----------------------");
}
