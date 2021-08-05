/** @file Food.cpp
 * @author Korosh Moosavi
 * @date 2021-08-05
 *
 * Snake game written to run on a Windows system
 * Move the snake head with WASD or Arrow Keys
 * Snake is blocked from reversing back onto itself
 * 1 point is awarded per frame of movement and 1000 for eating food
 * High score board retains the top scores in a single game launch
 *
 * Food.cpp:
 * - Contains method definitions for Food objects for use in the Snake game
 * - Food position is stored in the object as a COORD with values within the board's dimensions
 * - Position can be randomized and accessed via public methods
 */
#include "Food.h"

 // -------------------------------------------------------------- Food()
 // Default constructor for Food object. 
 // Will assume a board of size 50 x 25
 // 
 // pre:    None
 // post:   Food object created for a board of size 50 x 25
 //
Food::Food()
{
   board = { 50, 25 };
   newPos();
}

// -------------------------------------------------------------- Food(COORD)
// Parameter constructor for Food object.
// 
// param: board  Dimensions the board the game is being played on
// 
// pre:    Board dimensions must be positive values
// post:   Food object created for a board of specified size
//
Food::Food(COORD board)
{
   this->board = board;
   newPos();
}

// -------------------------------------------------------------- newPos()
// Randomly set a position within the walls of the board
// 
// pre:    None
// post:   pos values are set to a random number within the board dimensions
//
void Food::newPos()
{
   pos.X = (rand() % (board.X - 3)) + 1;
   pos.Y = (rand() % (board.Y - 3)) + 1;
}

// -------------------------------------------------------------- getPos()
// Accessor for food object's current position.
// 
// pre:    None
// return: COORD containing X and Y values corresponding to a position on the board
//
COORD Food::getPos()
{
   return pos;
}