#pragma once
#include "PathFinder.h"

class BFSPathFinder : public PathFinder
{
public:
    vector<Point> FindPath(const BoardInterface* board, Point s, Point e) const override;
};

