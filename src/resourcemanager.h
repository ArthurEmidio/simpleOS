#ifndef resourcemanager_h
#define resourcemanager_h

class ResourceManager{
    /*
    Da especificação:
    O pseudo-SO deve garantir que cada recurso seja
    alocado para um proceso por vez. Portanto, não
    há preempção na alocação dos dispositivos de E/S.
    ///====NOTA: o processo que estiver de posse do recurso CONTINUA
                 com o recurso até que termine o ultimo quantum de execução.

    Processos de tempo-real não precisam de recursos de
    I/O e podem ter tamanho fixo, ficando a cargo do programador.
    */
    public:
        enum{
            SCANNER = 0;
            PRINTER = 1;
            MODEN = 2;
            SATA = 3;
        };
    protected:
    private:
        bool resources[6];//true: livre; false: em uso.
        /*
            SCANNER = 0;
            PRINTER = 1,2;
            MODEN = 3;
            SATA = 4,5;
        */

};
#endif // resourcemanager_h
