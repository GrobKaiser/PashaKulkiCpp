#pragma once
#include "BoardInterface.h"

class PathFinder
{

public:
    virtual ~PathFinder() = default;

    virtual vector<Point> FindPath(const BoardInterface* board, Point s, Point e) const = 0;
};

