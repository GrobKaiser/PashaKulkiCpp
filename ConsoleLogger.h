#pragma once
#include "Logger.h"

class ConsoleLogger : public Logger
{
private:
    const int START_X = 40;     // Column where logs start
    const int START_Y = 2;      // Row where logs start
    const int MAX_LOGS = 5;     // Number of log lines to show at once
    const int CLEAR_WIDTH = 70; // Maximum log length to clear

    vector<string> logHistory;  // Last MAX_LOGS logs

    //void ClearArea(); to clear
    void MoveCursor(int x, int y);

public:
    ConsoleLogger();

    void Log(const string& message) override;
};

