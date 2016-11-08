#ifndef memorymanager_h
#define memorymanager_h

#include <stdint-gcc.h>
#define MEMORY_BLOCKS 1024
class MemoryManager{
    public:
    protected:
    private:
        /*
            Da especifica��o:
            A  aloca��o  de  mem�ria  deve  ser  implementada  como  um
            conjunto  de  blocos  cont�guos,  onde  cada
            bloco equivale uma palavra da mem�ria real.
            ///====NOTA: 1 bloco = 1byte = uma palavra da memoria real

            Cada processo deve alocar um segmento cont�guo de mem�ria,
            o qual permanecer� alocado durante toda  a  execu��o  do  processo.
            ///====NOTA: se um processo n�o est� mais em execu��o, N�O significa que ser� desalocado da mem�ria.
                         o processo permanece com reserva de mem�ria at� o fim da execu��o do �ltimo quantum.

            Deve-se  notar  que  n�o �  necess�rio  a  implementa��o  de  mem�ria  virtual,
            swap,  nem  sistema  de  pagina��o.  Portanto,  n�o  �  necess�rio
            gerenciar  a  mem�ria,  apenas  verificar  a disponibilidade de recursos
            antes de iniciar um processo.
            ///====NOTA: se um processo for iniciar e requisitar mais mem�ria do que est� dispon�vel,
                         esse processo N�O executar�.

            Deve ser utilizado um tamanho fixo de mem�ria de 1024 blocos.
            Dessa quantidade, 64 blocos devem ser reservados  para processos
            de tempo-real e os  960 blocos restantes devem  ser  compartilhados
            entre os processos de usu�rio.
        */
        uint8_t memory[ MEMORY_BLOCKS ];//1MB de mem�ria cont�gua. 1KK blocos.
};
#endif // memorymanager_h
