#pragma once
#include "Logger.h"

class LoggerDirectorInterface
{

public:
    virtual ~LoggerDirectorInterface() = default;

    virtual void AddLogger(unique_ptr<Logger> logger) = 0;
    virtual void Log(const string& message) = 0;
};

