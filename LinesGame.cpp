#include "LinesGame.h"
#include "LoggerDirector.h"

// Moves cursor to specified position
void LinesGame::MoveCursor(int x, int y) 
{
    cout << "\033[" << y << ";" << x << "H" << flush;
}

// Hides Cursor
void LinesGame::HideCursor() 
{
    cout << "\033[?25l" << flush;
}

// Restores the blinking console cursor
void LinesGame::ShowCursor() 
{
    cout << "\033[?25h" << flush;
}

// Drawing current game layout
void LinesGame::Display() 
{
    MoveCursor(1, 1); // Start from the beginning

    cout << "=============================\n";
    cout << "          B A L L S          \n";
    cout << "=============================\n";
    cout << " Score: " << score << "\n\n";

    // Columns header (from 1 to board size)
    cout << "    ";
    for (int i = 1; i <= board->GetSize(); ++i)
    {
        cout << i << " ";
    }
    cout << "\n  |" << string(board->GetSize() * 2 + 1, '-') << "|\n"; // Upper Edges

    // Rows Header (from A to board size)
    for (int i = 0; i < board->GetSize(); ++i) 
    {
        char rowLabel = 'A' + i;
        cout << rowLabel << " | "; // Left Edge

        for (int j = 0; j < board->GetSize(); ++j) 
        {
            if (board->GetAt(j, i) == 0) 
            {
                cout << ". "; // Dot as an empty cell
            }
            else 
            {
                cout << COLORS[board->GetAt(j, i)] << " " << RESET; // Ball
            }
        }

        cout << "|\n"; // Right Edge
    }

    // Bottom edge
    cout << "  |" << string(board->GetSize() * 2 + 1, '-') << "|\n";

    cout << "\033[J" << flush;
}

// Main game loop
void LinesGame::Play() 
{

    LoggerDirector::GetInstance().Log("Game started.");
    
    while (true) 
    {
        Display(); // Draw new state

        // If no more free spaces - game over
        if (board->GetFreeSpacesCount() == 0) 
        {
            LoggerDirector::GetInstance().Log("Game ended with score " + to_string(score));
            cout << "\nGame over! No more empty cells.\n";
            cout << "Your final score: " << score << ".\n";

            cin.ignore(); 
            cin.get();

            break;
        }

        cout << "\nInput your move (e.g. A1 B3 -> from A1 to B3) or 'Q' to exit: ";

        ShowCursor();

        cout << "\033[J" << flush; // Clear the screen from current pos to the end

        string fromStr, toStr; // Start and End Cells
        cin >> fromStr;

        // Player want to exit
        if (fromStr == "Q" || fromStr == "q") 
        {
            LoggerDirector::GetInstance().Log("Player quit the game.");
            cout << "Thank you for playing!\n";

            cin.ignore(); 
            cin.get();

            break; // Shut the loop
        }

        cin >> toStr;

        HideCursor();

        // Validation of input
        if (fromStr.length() < 2 || toStr.length() < 2) 
        {
            LoggerDirector::GetInstance().Log("Inputed ivalid option.");
            cout << "Invalid format! Press Enter and try again...";

            cin.ignore();
            cin.get();

            continue;
        }

        // Getting real coordinates

        int fromY = toupper(fromStr[0]) - 'A';
        int fromX = fromStr[1] - '1';

        int toY = toupper(toStr[0]) - 'A';
        int toX = toStr[1] - '1';

        // Check if both points are inside the board
        if (!board->IsInside(fromX, fromY) || !board->IsInside(toX, toY)) 
        {
            LoggerDirector::GetInstance().Log("Inputed coordinates were beyond the board.");
            cout << "Coordinates are beyond the board! Press Enter and try again...";

            cin.ignore(); 
            cin.get();

            continue;
        }

        // Check if selected a ball
        if (board->GetAt(fromX, fromY) == 0) 
        {
            LoggerDirector::GetInstance().Log("No ball was at selected cell.");
            cout << "No ball at selected cell! Press Enter and try again...";

            cin.ignore();
            cin.get();

            continue;
        }

        // Check if the destination is free
        if (board->GetAt(toX, toY) != 0) 
        {
            LoggerDirector::GetInstance().Log("Selected non-empty destination cell.");
            cout << "The selected destination cell is not empty. Press Enter and try again...";

            cin.ignore();
            cin.get();

            continue;
        }

        // Check if the path exists
        auto path = board->FindPath({ fromX, fromY }, { toX, toY });

        // If there is a path than move the ball
        if (!path.empty()) 
        {
            // Gradually moving the ball
            for (int i = 0; i < path.size() - 1; ++i) 
            {
                Point currentStep = path[i];
                Point nextStep = path[i + 1];

                // Swap the contents of the current cell and the next cell
                board->Swap(currentStep.x, currentStep.y, nextStep.x, nextStep.y);

                // Refresh the board layout on the console screen
                Display();

                // Pause briefly so the animation doesn't happen instantly
                this_thread::sleep_for(chrono::milliseconds(5));
            }

            int newScore = ClearLines();
            
            // Check if cleared any lines
            if (newScore == 0) 
            {
                // If not, spawn 3 new balls
                for (int i = 0; i < 3; ++i) 
                {
                    board->SpawnRandomBall();
                }

                // Check if added balls created a line
                score += ClearLines();
            }

            score += newScore;

            LoggerDirector::GetInstance().Log("Successfully moved the ball.");
        }
        else 
        {
            LoggerDirector::GetInstance().Log("No path between the selected cells.");
            cout << "Move is not possible! The path is obstructed. Press Enter and try again...";

            cin.ignore(); 
            cin.get();
        }
    }
}

// Clears the lines with prompt animation
int LinesGame::ClearLines() 
{
    bool** toDelete = board->CheckAndClearLines();

    Display();

    this_thread::sleep_for(chrono::milliseconds(30));

    return board->DeleteBalls(toDelete);
}

// Constructor
LinesGame::LinesGame(BoardInterface* board) : board(board) 
{
    score = 0;
}
