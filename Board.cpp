#include "Board.h"
#include "LoggerDirector.h"


// Counts free spaces left on board
int Board::GetFreeSpacesCount() const 
{
    int count = 0;

    for (int i = 0; i < size; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            if (data[i][j] == 0)
            {
                count++;
            }
        }
    }

    return count;
}

// Spawns a random ball in one of free spaces
bool Board::SpawnRandomBall() 
{
    int freeSpaces = GetFreeSpacesCount();

    // If no free spaces return false
    if (freeSpaces == 0)
    {
        return false;
    }

    int randomIndex = rand() % freeSpaces;
    int ballColor = (rand() % maxColors) + 1;

    int currentFree = 0;

    for (int i = 0; i < size; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            if (data[i][j] == 0) 
            {
                if (currentFree == randomIndex) 
                {
                    data[i][j] = ballColor;
                    return true;
                }

                currentFree++;
            }
        }
    }

    return false;
}

// Checks if the point is inside the board
bool Board::IsInside(int x, int y) const 
{
    return (x >= 0 && x < size && y >= 0 && y < size);
}

// Uses pathFinder to find a path between given points
vector<Point> Board::FindPath(Point start, Point end) const 
{
    return pathFinder->FindPath(this, start, end);
}

// Searching Lines of 5 or more same balls 
bool** Board::CheckAndClearLines() 
{
    bool** toDelete = new bool* [size];

    for (int i = 0; i < size; i++) 
    {
        toDelete[i] = new bool[size]{false};
    }

    bool foundAny = false;

    // Directions: (dx, dy) -> horizontal, vertical, two skews
    int dirs[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (int y = 0; y < size; ++y) 
    {
        for (int x = 0; x < size; ++x) 
        {
            if (data[y][x] == 0)
            {
                continue;
            }

            int color = data[y][x];

            for (int d = 0; d < 4; ++d) 
            {
                int dx = dirs[d][0];
                int dy = dirs[d][1];

                int count = 1;

                // Checking forward
                int nx = x + dx;
                int ny = y + dy;

                while (IsInside(nx, ny) && data[ny][nx] == color) 
                {
                    count++;
                    nx += dx;
                    ny += dy;
                }

                // If line has more than 5 balls
                if (count >= 5) 
                {
                    foundAny = true;

                    // Mark for deletion
                    int mx = x, my = y;

                    for (int i = 0; i < count; ++i) 
                    {
                        toDelete[my][mx] = true;
                        data[my][mx] = 8;
                        mx += dx;
                        my += dy;
                    }
                }
            }
        }
    }

    return toDelete;
}

// Remove balls based on bool[size][size] array
int Board::DeleteBalls(bool** toDelete) 
{
    int score = 0;

    // Delete marked balls, and count score
    for (int y = 0; y < size; ++y) 
    {
        for (int x = 0; x < size; ++x) 
        {
            if (toDelete[y][x]) 
            {
                data[y][x] = 0;
                score++;
            }
        }
    }

    if (score > 0) 
    {
        LoggerDirector::GetInstance().Log("Successfully made a line of " + to_string(score));
    }

    for (int i = 0; i < size; i++) 
    {
        delete[] toDelete[i];
    }

    delete[] toDelete;

    return score;
}

// Retrieves the value on the (x, y) cell
int Board::GetAt(int x, int y) const 
{
    if (IsInside(x, y)) 
    {
        return data[x][y];
    }

    return -1;
}

// Sets a new value (v) on the (x, y) cell
bool Board::SetAt(int x, int y, int v) 
{
    if (IsInside(x, y)) 
    {
        data[x][y] = v;
        return true;
    }

    return false;
}

// Swaps the values from two cells
bool Board::Swap(int x1, int y1, int x2, int y2) 
{
    if (IsInside(x1, y1) && IsInside(x2, y2)) 
    {
        int tmp = data[x1][y1];
        data[x1][y1] = data[x2][y2];
        data[x2][y2] = tmp;
        return true;
    }

    return false;
}

// Gets the size of the board
int Board::GetSize() const 
{
    return size;
}

// Initializes the underlying array
void Board::Initialize() 
{
    data = new int* [size];

    for (int i = 0; i < size; i++) 
    {
        data[i] = new int[size] {0};
    }
}

// Constructor
Board::Board(int boardSize, int maxColors, int startCount, const PathFinder* pathFinder)
    : size(boardSize), maxColors(maxColors), startCount(startCount), pathFinder(pathFinder)
{
    Initialize();

    // Spawn startCount Random balls at the game start
    for (int i = 0; i < startCount; ++i)
    {
        SpawnRandomBall();
    }

    // Check if starting layout generated a line. Delete without score
    DeleteBalls(CheckAndClearLines());
}

// Destructor
Board::~Board() 
{
    for (int i = 0; i < size; i++) 
    {
        delete[] data[i];
    }

    delete[] data;
}