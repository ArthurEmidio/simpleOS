#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "dispatcher.h"
#include "process.h"

#include "testprocessmanager.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./simpleSO proccesses.txt" << std::endl;
        exit(1);
    }

    std::ifstream inputFile;
    inputFile.open(argv[1], std::ios::in);
    if (!inputFile.is_open()) {
        std::cout << "The file \"" << argv[1] << "\" could not be opened." << std::endl;
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
