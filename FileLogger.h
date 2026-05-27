#pragma once
#include "Logger.h"

class FileLogger : public Logger
{

private:
    ofstream logFile; // File to log to
    string GenerateUniqueFilename();

public:
    FileLogger(const string& filename);
    FileLogger();

    ~FileLogger();

    void Log(const string& message) override;
};

