#include "LinesGame.h"
#include "Board.h"
#include "BFSPathFinder.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "LoggerDirector.h"

// Main App Function
int main() 
{
    system("clear || cls"); // Console Clearing
    cout << "\033[?25l" << flush; // Hinding Cursor
    srand(time(0)); // Seed the rand()

    LoggerDirector& loggerDirector = LoggerDirector::GetInstance();

    loggerDirector.AddLogger(make_unique<ConsoleLogger>());
    loggerDirector.AddLogger(make_unique<FileLogger>());
    
    Board* board = new Board(BOARD_SIZE, MAX_COLORS, START_BALLS_COUNT, new BFSPathFinder());

    LinesGame* game = new LinesGame(board);

    loggerDirector.Log("System initialized.");

    game->Play();

    return 0;
}