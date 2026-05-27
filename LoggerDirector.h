#pragma once
#include "LoggerDirectorInterface.h"
class LoggerDirector : public LoggerDirectorInterface
{
private:
    vector<unique_ptr<Logger>> loggers; // List of loggers to use

    // Private constructor/destructor for Singleton
    LoggerDirector() = default;
    ~LoggerDirector() override = default;

public:
    // Delete copy constructor and assignment operator to prevent cloning
    LoggerDirector(const LoggerDirector&) = delete;
    LoggerDirector& operator=(const LoggerDirector&) = delete;

    // Global Access Point
    static LoggerDirector& GetInstance();

    void AddLogger(unique_ptr<Logger> logger) override;
    void Log(const string& message) override;
};

