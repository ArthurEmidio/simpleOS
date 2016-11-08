#ifndef memorymanager_h
#define memorymanager_h

#include <stdint-gcc.h>
#define MEMORY_BLOCKS 1024
class MemoryManager{
    public:
    protected:
    private:
        /*
            Da especificação:
            A  alocação  de  memória  deve  ser  implementada  como  um
            conjunto  de  blocos  contíguos,  onde  cada
            bloco equivale uma palavra da memória real.
            ///====NOTA: 1 bloco = 1byte = uma palavra da memoria real

            Cada processo deve alocar um segmento contíguo de memória,
            o qual permanecerá alocado durante toda  a  execução  do  processo.
            ///====NOTA: se um processo não está mais em execução, NÃO significa que será desalocado da memória.
                         o processo permanece com reserva de memória até o fim da execução do último quantum.

            Deve-se  notar  que  não é  necessário  a  implementação  de  memória  virtual,
            swap,  nem  sistema  de  paginação.  Portanto,  não  é  necessário
            gerenciar  a  memória,  apenas  verificar  a disponibilidade de recursos
            antes de iniciar um processo.
            ///====NOTA: se um processo for iniciar e requisitar mais memória do que está disponível,
                         esse processo NÃO executará.

            Deve ser utilizado um tamanho fixo de memória de 1024 blocos.
            Dessa quantidade, 64 blocos devem ser reservados  para processos
            de tempo-real e os  960 blocos restantes devem  ser  compartilhados
            entre os processos de usuário.
        */
        uint8_t memory[ MEMORY_BLOCKS ];//1MB de memória contígua. 1KK blocos.
};
#endif // memorymanager_h
