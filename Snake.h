/** @file Snake.h
 * @author Korosh Moosavi
 * @date 2021-08-05
 *
 * Snake game written to run on a Windows system
 * Move the snake head with WASD or Arrow Keys
 * Snake is blocked from reversing back onto itself
 * 1 point is awarded per frame of movement and 1000 for eating food
 * High score board retains the top scores in a single game launch
 *
 * Snake.h:
 * - Contains fields and method headers used by Snake.cpp and SnakeGame.cpp to manage the snake
 * - Snake movement directions are enumerated in this file
 * - Struct for snake body segments is defined here
 * - Detailed documentation of methods can be found in Snake.cpp
 */
#ifndef SNAKE_H
#define SNAKE_H

#pragma once

#include <Windows.h>

enum { NO_DIR, UP, RIGHT, DOWN, LEFT };

struct Body       // Body segments of snake
{
   COORD pos;     // Position of segment
   Body* next;    // Segment attached to this one

   // Parameter constructor
   Body(COORD thisPos, Body* nextPart) : pos{ thisPos }, next{ nextPart } {};
   // Recursive destructor
   ~Body() { delete next; };
};

class Snake
{
private:
   COORD pos;     // Snake head's current position
   COORD board;   // Dimensions the board the game is being played on
   
   Body* nextBody;// Pointer to the body segment attached to the snake head

   int len;       // Snake's length in body segments (including head)
   int spd;       // Number of cells the snake moves per frame
   int dir;       // 0 = no direction, 1 = up, 2 = right, 3 = down, 4 = left
   int block;     // direction opposite of snake, so it can't move back on itself

public:
   Snake();                         // Default constructor
   Snake(COORD board, int spd);     // Parameter constructor
   Snake(Snake* other);             // Copy constructor

   void operator=(Snake* other);    // Assignment operator
   void turn(int dir);              // Modify dir
   void move();                     // Update pos
   void grow();                     // Increase len and add Body
   void reset();                    // Restore initial state of the snake

   bool collision();                // Check for collision with walls or self
   bool eaten(COORD foodPos);       // Check for collision with object

   int getDir();                    // Accessor for dir
   COORD getPos();                  // Accessor for pos
   Body* getBody();                 // Accessor for nextBody

};

#endif