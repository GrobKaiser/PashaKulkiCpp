#pragma once
#include "Config.h"

// An Interface for Board Class
class BoardInterface 
{

public:

	virtual ~BoardInterface() = default;

	virtual int GetSize() const = 0;
	virtual int GetFreeSpacesCount() const = 0;
	virtual int DeleteBalls(bool** toDelete) = 0;
	virtual int GetAt(int x, int y) const = 0;

	virtual bool SetAt(int x, int y, int v) = 0;
	virtual bool SpawnRandomBall() = 0;
	virtual bool Swap(int x1, int y1, int x2, int y2) = 0;
	virtual bool IsInside(int x, int y) const = 0;

	virtual bool** CheckAndClearLines() = 0;

	virtual vector<Point> FindPath(Point s, Point e) const = 0;
};