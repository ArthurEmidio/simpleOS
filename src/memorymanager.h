#ifndef memorymanager_h
#define memorymanager_h

#include <stdint-gcc.h>

class MemoryManager{
    public:
    protected:
    private:
        uint8_t memory[1000000];//1MB de mem�ria cont�gua.
        //N�o utilizei vector em primeiro momento para garantir aloca��o cont�gua real.

};
#endif // memorymanager_h
