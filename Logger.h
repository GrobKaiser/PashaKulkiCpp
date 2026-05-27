#pragma once
#include "Config.h"

class Logger
{

public:
    virtual ~Logger() = default;
    
    virtual void Log(const string& message) = 0;
};

