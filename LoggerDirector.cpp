#include "LoggerDirector.h"

// Global Access Point
LoggerDirector& LoggerDirector::GetInstance() 
{
    static LoggerDirector instance;
    return instance;
}

// Adds new loger to the list
void LoggerDirector::AddLogger(unique_ptr<Logger> logger) 
{
    loggers.push_back(move(logger));
}

// Writes a message with timestamp via all loggers
void LoggerDirector::Log(const string& message) 
{
    // Get current time from the system clock
    auto now = chrono::system_clock::now();

    // Convert it to time_t
    time_t time_now = chrono::system_clock::to_time_t(now);

    // Convert to local time structure safely
    tm tm_now;
#if defined(_WIN32)
    localtime_s(&tm_now, &time_now); // Windows safe version
#else
    localtime_r(&time_now, &tm_now); // Linux/macOS safe version
#endif

    // Format the time into a stream
    stringstream ss;
    ss << "[" << put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << "]: ";

    // Append the original message and return
    auto messageWithTimeStamp = ss.str() + message;
    for (const auto& logger : loggers) 
    {
        logger->Log(messageWithTimeStamp);
    }
}
