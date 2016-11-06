
class Process
{
    int _pid;
    
    int _memOffset;
    
    int _initTime;
    
    int _priority;
    
    int _processingTime;
    
    int _memoryBlocks;
    
    int _printerId;
    
    int _driveId;
    
    bool _requestedScanner;
    
    bool _requestedModem;
    
public:  
    Process(int initTime, int priority, int processingTime, int memoryBlocks,
            int printerId, int driveId, bool requestedScanner, bool requestedModem);
     
    int getPid() const;
    
    int getMemoryOffset() const;
    
    int getMemoryBlocks() const;
    
    int getPriority() const;
    
    int getInitTime() const;
    
    int getProcessingTime() const;
    
    int getPrinterId() const;
    
    int getDriveId() const;
    
    bool didRequestScanner() const;
    
    bool didRequestModem() const;
    
    void setPid(int pid);
    
    void setMemoryOffset(int offset);
        
};