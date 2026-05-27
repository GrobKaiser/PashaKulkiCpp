#pragma once
#include <iostream>     // Console writing
#include <vector>       // Lists
#include <queue>        // BFS queue
#include <cstdlib>      // C functions
#include <ctime>        // Seeding rand()
#include <iomanip>      // Writing
#include <fstream>      // Writing to file
#include <string>       // Writing logs
#include <memory>       // Managing objects
#include <chrono>       // Sleeping
#include <sstream>      // Formatting logging messages
#include <filesystem>   // Creating log files
#include <algorithm>    // Reversing in BFS
#include <thread>       // Sleeping

#include "Point.h"

using namespace std;

const int BOARD_SIZE = 9;         // Default board size
const int MAX_COLORS = 7;         // Default maximum number of colors
const int START_BALLS_COUNT = 5;  // Default number of starting balls

const string RESET = "\033[0m"; // Resets the brush 

// Characters for the balls
const string COLORS[] = 
{   
    " ",              // 0: Puste pole
    "\033[1;31mO",    // 1 Red
    "\033[1;30mO",    // 2 Gray
    "\033[1;33mO",    // 3 Yellow
    "\033[1;34mO",    // 4 Blue
    "\033[1;35mO",    // 5 Magenta
    "\033[1;36mO",    // 6 Cyan
    "\033[1;37mO",    // 7 White
    "\033[1;32mO"     // 8 Green
};

