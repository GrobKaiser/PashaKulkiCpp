#pragma once

// Struct representing a single point on board
struct Point 
{

    int x, y; // Coordinates

    // Equality operators

    bool operator==(const Point& other) const 
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const 
    {
        return !(*this == other);
    }
};