#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Process.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;
    inputFile.open(argv[1], ios::in);
    if (!inputFile.is_open()) {
        cout << "Usage: ./simpleSO proccesses.txt" << endl;
        exit(1);
    }
    
    vector<Process*> processes;
    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        
        char tmp;
        int initTime, priority, processingTime, memoryBlocks, printerId, driveId;
        bool requestedScanner, requestedModem;
        
        ss >> initTime >> tmp;
        ss >> priority >> tmp;
        ss >> processingTime >> tmp;
        ss >> memoryBlocks >> tmp;
        ss >> printerId >> tmp;
        ss >> requestedScanner >> tmp;
        ss >> requestedModem >> tmp;
        ss >> driveId;
        
        Process *process = new Process(initTime, priority, processingTime, memoryBlocks,
                                       printerId, driveId, requestedScanner, requestedModem);
        processes.push_back(process);
        
    }
    inputFile.close();
            
    return 0;
}
