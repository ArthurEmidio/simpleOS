#ifndef resourcemanager_h
#define resourcemanager_h

class ResourceManager{
    /*
    Da especifica��o:
    O pseudo-SO deve garantir que cada recurso seja
    alocado para um proceso por vez. Portanto, n�o
    h� preemp��o na aloca��o dos dispositivos de E/S.
    ///====NOTA: o processo que estiver de posse do recurso CONTINUA
                 com o recurso at� que termine o ultimo quantum de execu��o.

    Processos de tempo-real n�o precisam de recursos de
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
