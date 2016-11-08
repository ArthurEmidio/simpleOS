#ifndef memorymanager_h
#define memorymanager_h

#include <stdint-gcc.h>

class MemoryManager{
    public:
    protected:
    private:
        uint8_t memory[1000000];//1MB de memória contígua.
        //Não utilizei vector em primeiro momento para garantir alocação contígua real.
        //pode ser modificado.
        //64 MB deve ser reservado para processos de tempo real, o restante deve ser para processos de usuário

};
#endif // memorymanager_h
