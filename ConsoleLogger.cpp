#include "ConsoleLogger.h"

// Moves Cursor to position with coordinates (x, y)
void ConsoleLogger::MoveCursor(int x, int y) 
{
    cout << "\033[" << y << ";" << x << "H" << flush;
}

//void ConsoleLogger::ClearArea() {
//    for (int i = 0; i < MAX_LOGS + 1; ++i) { // +1 to include header
//        MoveCursor(START_X, START_Y - 1 + i);
//        cout << string(CLEAR_WIDTH, ' ');
//    }
//} to clear

// Writes a message to the dedicated place in console
void ConsoleLogger::Log(const string& message) 
{
    // Add new message to history
    logHistory.push_back(message);

    // If history exceeds max limits, remove the oldest message
    if (logHistory.size() > MAX_LOGS) 
    {
        logHistory.erase(logHistory.begin());
    }

    // Save the user's current cursor position right now
    cout << "\033[s";

    // Render the updated log list side-panel
    for (int i = 0; i < MAX_LOGS; ++i) 
    {
        // Move to the specific log line row
        MoveCursor(START_X, START_Y + i);

        // Wipe whatever text was there previously on this line
        cout << string(CLEAR_WIDTH, ' ');

        // Go back to the column start and print the historical log if it exists
        MoveCursor(START_X, START_Y + i);
        if (i < logHistory.size()) 
        {
            // Dim the older logs, make the newest one bright white
            if (i == logHistory.size() - 1) 
            {
                cout << "\033[1;37m" << logHistory[i] << "\033[0m"; // Bold White
            }
            else 
            {
                cout << "\033[2m" << logHistory[i] << "\033[0m";    // Faded
            }
        }
    }

    // Restore the cursor automatically back to where the user was typing
    cout << "\033[u" << flush;
}

// Constructor
ConsoleLogger::ConsoleLogger()
{
    // Draw a nice persistent header for the log section on startup
    cout << "\033[s";
    MoveCursor(START_X, START_Y - 1);
    cout << "\033[1;36m--- LIVE SYSTEM LOGS ---\033[0m"; // Cyan header
    cout << "\033[u" << flush;
}