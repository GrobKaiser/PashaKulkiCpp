#pragma once
#include "BoardInterface.h"
#include "PathFinder.h"

class Board : public BoardInterface 
{
private:
	int** data;		// Array containing indexes of colors. 0 means no ball, >0 means the index of ball color
	int size;		// Size of the square board
	int startCount; // Number of balls at the start
	int maxColors;  // Maximum number of colors at the same time on board
	const PathFinder* pathFinder;	// Engine for finding paths between cells on board
	void Initialize();
public:
	Board(int boardSize, int maxColors, int startCount, const PathFinder* pathFinder);
	~Board();

	int GetSize() const;
	int GetFreeSpacesCount() const;
	int DeleteBalls(bool** toDelete);
	int GetAt(int x, int y) const;

	bool SetAt(int x, int y, int v);
	bool SpawnRandomBall();
	bool Swap(int x1, int y1, int x2, int y2);
	bool IsInside(int x, int y) const;

	bool** CheckAndClearLines();

	vector<Point> FindPath(Point s, Point e) const;
};