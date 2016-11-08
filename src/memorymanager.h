#ifndef memorymanager_h
#define memorymanager_h

#include <stdint-gcc.h>

class MemoryManager{
    public:
    protected:
    private:
        uint8_t memory[1000000];//1MB de memória contígua.
        //Não utilizei vector em primeiro momento para garantir alocação contígua real.

};
#endif // memorymanager_h
