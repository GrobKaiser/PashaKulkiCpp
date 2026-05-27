#pragma once
#include "GameManager.h"
#include "BoardInterface.h"

class LinesGame : public GameManager 
{
private:
    BoardInterface* board;  // Board
    int score;              // Current score

    void Display();
    void MoveCursor(int x, int y);
    void HideCursor();
    void ShowCursor();

    int ClearLines();

public:
    LinesGame(BoardInterface* board);

    void Play();
};