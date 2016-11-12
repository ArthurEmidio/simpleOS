#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "dispatcher.h"
#include "process.h"

//#define DEBUG
#ifdef DEBUG
    //se estiver definido debug, imprime os trecos
    #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
    #define DEBUG_ONLY(x) do{x;}while(0);

#else
    //caso contrario, recebe argumentos mas faz nada
    #define DEBUG_PRINT(message)
    #define DEBUG_ONLY(x) //do{;}while(0)

#endif //DEBUG

int main(int argc, char *argv[])
{
    std::string arq;
    if (argc < 2) {
        std::cout << "Usage: ./simpleSO proccesses.txt" << std::endl;
        //exit(1);
        arq = "processes.txt";
    }else{
        arq = argv[1];
    }
    DEBUG_PRINT(arq)

    std::ifstream inputFile;
    inputFile.open(arq, std::ios::in);
    if (!inputFile.is_open()) {
        std::cout << "The file \"" << arq << "\" could not be opened." << std::endl;
        exit(1);
    }

    // Parsing the input file and creating the processes.
    std::vector<Process*> processes;
    std::string line;
    int pidCounter = 0;
    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);

        char sep;
        int initTime, priority, processingTime, memoryBlocks, printerId, driveId;
        bool requestedScanner, requestedModem;
        ss >> initTime >> sep;
        ss >> priority >> sep;
        ss >> processingTime >> sep;
        ss >> memoryBlocks >> sep;
        ss >> printerId >> sep;
        ss >> requestedScanner >> sep;
        ss >> requestedModem >> sep;
        ss >> driveId;

        DEBUG_PRINT("*****")
        DEBUG_PRINT("initTime: \t\t" << initTime);
        DEBUG_PRINT("priority: \t\t" << priority);
        DEBUG_PRINT("processingTime: \t" << processingTime);
        DEBUG_PRINT("memoryBlocks: \t\t" << memoryBlocks);
        DEBUG_PRINT("printerId: \t\t" << printerId);
        DEBUG_PRINT("requestedScanner: \t" << requestedScanner);
        DEBUG_PRINT("requestedModem: \t" << requestedModem);
        DEBUG_PRINT("driveId: \t\t" << driveId);

        Process *process = new Process(initTime, priority, processingTime, memoryBlocks,
                                       printerId, driveId, requestedScanner, requestedModem);
        process->setPid(pidCounter++);
        processes.push_back(process);
    }
    inputFile.close();


    // Creating the dispatcher and running it.
    Dispatcher dispatcher(processes);
    dispatcher.run();

    return 0;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
