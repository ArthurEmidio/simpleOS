#ifndef resourcemanager_h
#define resourcemanager_h

class ResourceManager{
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
