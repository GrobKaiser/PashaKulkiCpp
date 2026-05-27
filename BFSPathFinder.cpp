#include "BFSPathFinder.h"

// Uses BFS algorithm to find a path prom s to e on board
vector<Point> BFSPathFinder::FindPath(const BoardInterface* board, Point s, Point e) const 
{

    // Return empty vector if pointer is null or points are completely out of bounds
    if (!board || board->GetAt(s.x, s.y) == -1 || board->GetAt(e.x, e.y) == -1) 
    {
        return {};
    }

    // If start and destination are identical, the path is just that single point
    if (s == e) 
    {
        return { s };
    }

    int size = board->GetSize();

    // Standard BFS tracking data structures
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    queue<Point> q;

    // 2D grid mapping a coordinate to the parent node that discovered it
    vector<vector<Point>> parent(size, vector<Point>(size, { -1, -1 }));

    // Initialize BFS
    q.push(s);
    visited[s.y][s.x] = true;

    // Directions
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };
    bool pathFound = false;

    while (!q.empty()) 
    {
        Point curr = q.front();
        q.pop();

        if (curr == e) 
        {
            pathFound = true;
            break; // Destination reached
        }

        for (int i = 0; i < 4; ++i) 
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < size && ny >= 0 && ny < size) 
            {
                // Node is walkable if it is empty (0) or it is explicitly our destination
                if (!visited[ny][nx] && (board->GetAt(nx, ny) == 0 || (nx == e.x && ny == e.y))) 
                {
                    visited[ny][nx] = true;
                    parent[ny][nx] = curr; // Map the route back to curr
                    q.push({ nx, ny });
                }
            }
        }
    }

    // Reconstruct the path if one was discovered
    if (pathFound)
    {
        vector<Point> dynamicPath;
        Point currentTrackingPoint = e;

        // Trace backward from target e back until we hit the start flag point
        while (currentTrackingPoint != s) 
        {
            dynamicPath.push_back(currentTrackingPoint);
            currentTrackingPoint = parent[currentTrackingPoint.y][currentTrackingPoint.x];
        }

        dynamicPath.push_back(s); // Append the initial start node

        // The path is currently backward
        reverse(dynamicPath.begin(), dynamicPath.end());

        return dynamicPath;
    }

    return {}; // Return empty vector if no path exists
}