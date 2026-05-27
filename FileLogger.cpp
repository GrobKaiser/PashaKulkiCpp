#include "FileLogger.h"

// Writes a message to a dedicated file
void FileLogger::Log(const string& message) 
{
    if (logFile.is_open()) 
    {
        logFile << message << endl;
    }
}

// Generates Unique name for new log file
string FileLogger::GenerateUniqueFilename() 
{
    // Get current system time
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);

    tm tm_now;
#if defined(_WIN32) // OS addapted
    localtime_s(&tm_now, &time_now); // Windows
#else
    localtime_r(&time_now, &tm_now); // Linux/MacOS
#endif

    // Format date and time
    stringstream ss;
    ss << "logs/Balls_"
        << put_time(&tm_now, "%Y-%m-%d_%H-%M-%S")
        << ".log";

    return ss.str();
}

// Constructors

FileLogger::FileLogger() 
{
    // Ensure the dedicated folder ("logs") exists
    string folderName = "logs";
    if (!filesystem::exists(folderName)) 
    {
        filesystem::create_directory(folderName);
    }

    // Generate filename and open the stream
    string fullPath = GenerateUniqueFilename();
    logFile.open(fullPath, ios::out | ios::app);
}

FileLogger::FileLogger(const string& filename) 
{
    logFile.open(filename, ios::app);
}

// Destructor
FileLogger::~FileLogger() 
{
    if (logFile.is_open()) 
    {
        logFile.close(); // Close the log file if open
    }
}