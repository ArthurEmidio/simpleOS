#ifndef PROCESS_H
#define PROCESS_H

/*!
 * \brief The \c Process class represents what is a process in an operating system.
 */
class Process
{
    /*!
     * \brief The PID given to the process by the OS.
     */
    int _pid;
    
    /*!
     * \brief The memory offset given to the process by the OS.
     */
    int _memOffset;
    
    /*!
     * \brief The time that the process is created.
     */
    int _initTime;
    
    /*!
     * \brief The priority of the process. The hightest priority is 0, the second-highest is 1, and so on.
     */
    int _priority;
    
    /*!
     * \brief The time it takes for the process to fully execute.
     */
    int _processingTime;
    
    /*!
     * \brief How many blocks of memory that the process needs to execute.
     */
    int _memoryBlocks;
    
    /*!
     * \brief The printer identifier that the process requests, or 0 if none.
     */
    int _printerId;
    
    /*!
     * \brief The drive identifier that the process requests, or 0 if none.
     */
    int _driveId;
    
    /*!
     * \brief Whether the process has requested a scanner.
     */
    bool _requestedScanner;
    
    /*!
     * \brief Whether the process has requested a modem.
     */
    bool _requestedModem;
    
public:
    /*!
     * \brief Default constructor.
     * \param initTime The time that the process is created.
     * \param priority The priority of the process. The hightest priority is 0, the second-highest is 1, and so on.
     * \param processingTime The time it takes for the process to fully execute.
     * \param memoryBlocks How many blocks of memory that the process needs to execute.
     * \param printerId The printer identifier that the process requests, or 0 if none.
     * \param driveId The drive identifier that the process requests, or 0 if none.
     * \param requestedScanner Whether the process has requested a scanner.
     * \param requestedModem Whether the process has requested a modem.
     */
    Process(int initTime, int priority, int processingTime, int memoryBlocks,
            int printerId, int driveId, bool requestedScanner, bool requestedModem);

    /*!
     * \brief Gets the PID given to the process by the OS.
     * \return The PID.
     */
    int getPid() const;
    
    /*!
     * \brief Gets the memory offset given to the process by the OS.
     * \return The memory offset.
     */
    int getMemoryOffset() const;
    
    /*!
     * \brief Gets how many blocks of memory that the process needs to execute.
     * \return The number of blocks the process needs to execute.
     */
    int getMemoryBlocks() const;
    
    /*!
     * \brief Gets the priority of the process. The hightest priority is 0, the second-highest is 1, and so on.
     * \return The priority of the process.
     */
    int getPriority() const;
    
    /*!
     * \brief Gets the time that the process is created.
     * \return The time the process is created.
     */
    int getInitTime() const;
    
    /*!
     * \brief Gets the time it takes for the process to fully execute.
     * \return The execution time.
     */
    int getProcessingTime() const;
    
    /*!
     * \brief Gets the printer identifier that the process requests, or 0 if none.
     * \return The printer identifier, of 0 if none.
     */
    int getPrinterId() const;
    
    /*!
     * \brief Gets the drive identifier that the process requests, or 0 if none.
     * \return The drive identifier, or 0 if none.
     */
    int getDriveId() const;
    
    /*!
     * \brief Gets whether the process has requested a scanner.
     * \return Whether the scanner is requested by the process.
     */
    bool didRequestScanner() const;
    
    /*!
     * \brief Gets whether the process has requested a modem.
     * \return Whether the scanner is requested by the process.
     */
    bool didRequestModem() const;
    
    /*!
     * \brief Sets the PID given to the process.
     * \param pid The PID.
     */
    void setPid(int pid);
    
    /*!
     * \brief Sets the memory offset given to the process.
     * \param offset The memory offset.
     */
    void setMemoryOffset(int offset);
        
};

#endif // PROCESS_H
