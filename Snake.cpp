/** @file Snake.cpp
 * @author Korosh Moosavi
 * @date 2021-08-05
 *
 * Snake game written to run on a Windows system
 * Move the snake head with WASD or Arrow Keys
 * Snake is blocked from reversing back onto itself
 * 1 point is awarded per frame of movement and 1000 for eating food
 * High score board retains the top scores in a single game launch
 * 
 * Snake.cpp:
 * - Contains method definitions used by SnakeGame.cpp to manage the snake
 * - Includes copy constructor and assignment operator functions
 * - Defaults to a board size of 50 x 25 if none is given
 * - Board and food data must be provided for proper functioning
 */

#include "Snake.h"

 // -------------------------------------------------------------- Snake()
 // Default constructor for Snake object. 
 // Will assume a board of size 50 x 25
 // 
 // pre:    None
 // post:   Snake object created for a board of size 50 x 25
 //
Snake::Snake()
{
   board = { 50, 25 };
   this->board = board;
   pos.X = board.X / 2;
   pos.Y = board.Y / 2;
   spd = 1;
   len = 1;
   dir = NO_DIR;
   block = NO_DIR;
   nextBody = NULL;
}

// -------------------------------------------------------------- Snake(COORD, int)
// Parameter constructor for Snake object. 
// Takes board size and speed of snake as parameters.
// Speed is calculated as pixels moved per frame drawn.
// 
// param:  board  Dimensions of the game board
// param:  spd    Pixels to move per frame drawn
// 
// pre:    Board parameter uses only positive values.
// post:   Snake object created for a specified board size and speed.
//
Snake::Snake(COORD board, int spd)
{
   this->board = board;
   pos.X = board.X / 2;
   pos.Y = board.Y / 2;
   this->spd = spd;
   len = 1;
   dir = NO_DIR;
   block = NO_DIR;
   nextBody = NULL;
}

// -------------------------------------------------------------- Snake(Snake*)
// Copy constructor for Snake object. 
// Creates a snake object as a copy of another.
// 
// param:  other  Pointer to snake object to be copied
// 
// pre:    Copied snake has valid data.
// post:   Copy created as this object.
//
Snake::Snake(Snake* other)
{
   *this = other;
}

// -------------------------------------------------------------- operator=(Snake*)
// Assignment operator for Snake object. 
// Resets this object then copies a snake object's data fields into this object.
// 
// param:  other  Pointer to snake object to be copied
// 
// pre:    Copied snake has valid data.
// post:   This object has all the same data as the other snake.
//
void Snake::operator=(Snake* other)
{
   reset();
   board = other->board;
   pos.X = other->pos.X;
   pos.Y = other->pos.Y;
   spd = other->spd;
   len = other->len;
   dir = other->dir;
   block = other->block;
   if (other->nextBody != NULL)     // Create copies of any body segments
   {
      Body* cur = other->nextBody;
      Body* thisCur = new Body(cur->pos, NULL);
      nextBody = thisCur;
      cur = cur->next;
      while (cur != NULL)
      {
         thisCur->next = new Body(cur->pos, NULL);
         cur = cur->next;
         thisCur = thisCur->next;
      }
   }
   else nextBody = NULL;
}

// -------------------------------------------------------------- turn(int)
// Sets direction of movement for the snake.
// 0 = No movement  1 = up  2 = right  3 = down  4 = left
// Enumerated as NO_DIR, UP, RIGHT, DOWN, LEFT in the header file
// 
// param:  dir  Direction code for the snake
// 
// pre:    None
// post:   Snake movement is set to the specified direction
//
void Snake::turn(int dir)
{
   if (dir == block) return;
   this->dir = dir;
   switch (dir)          // Block opposite direction from movement
   {
   case UP: block = DOWN; break;
   case RIGHT: block = LEFT; break;
   case DOWN: block = UP; break;
   case LEFT: block = RIGHT; break;
   }
}

// -------------------------------------------------------------- move()
// Sets direction of movement for the snake.
// 0 = No movement  1 = up  2 = right  3 = down  4 = left
// Enumerated as NO_DIR, UP, RIGHT, DOWN, LEFT in the header file
// 
// param:  dir  Direction code for the snake
// 
// pre:    None
// post:   Snake movement is set to the specified direction
//
void Snake::move()
{
   COORD hold = pos;
   switch (dir)            // Move position depending on the snake's direction
   {
   case UP: pos.Y -= spd; break;
   case RIGHT: pos.X += spd; break;
   case DOWN: pos.Y += spd; break;
   case LEFT: pos.X -= spd; break;
   }
   Body* cur = nextBody;
   while (cur != NULL)     // Move any body segments
   {
      COORD temp = cur->pos;
      cur->pos = hold;
      hold = temp;
      cur = cur->next;
   }
}

// -------------------------------------------------------------- grow()
// Increases length count by 1 and adds a body segment at the position
// of the snake head before it eats the food.
// 
// pre:    Snake should be moving, so body segments don't stack onto a single cell
// post:   Snake length is increased and a body segment is added
//
void Snake::grow()
{
   len++;
   nextBody = new Body(pos, nextBody);
}

// -------------------------------------------------------------- reset()
// Prepares the snake object for a new game by resetting data fields to
// initial values.
// 
// pre:    None
// post:   Snake is set to its starting state
//
void Snake::reset()
{
   delete nextBody;
   pos.X = board.X / 2;
   pos.Y = board.Y / 2;
   len = 1;
   dir = NO_DIR;
   block = NO_DIR;
   nextBody = NULL;
}

// -------------------------------------------------------------- collision()
// Checks for collision with board walls and body segments.
// 
// pre:     Board variable is correctly set to the same dimensions as the game board
// returns: True if collision is found, false otherwise
//
bool Snake::collision()
{
   if (pos.X < 1 || pos.X > board.X - 2 || pos.Y < 1 || pos.Y > board.Y - 1) return true;
   else
   {
      Body* cur = nextBody;   // Check for collision with every body segment
      while (cur != NULL)
      {
         if (cur->pos.X == pos.X && cur->pos.Y == pos.Y) return true;
         cur = cur->next;
      }
   }
   return false;
}

// -------------------------------------------------------------- eaten(COORD)
// Checks if food position equals the position of the snake (head)
// 
// param: foodPos  Position of the food object currently on the board
// 
// pre:     Food object is initialized with the same board dimensions as the snake
// returns: True if collision is found, false otherwise
//
bool Snake::eaten(COORD foodPos)
{
   if (foodPos.X == pos.X && foodPos.Y == pos.Y) return true;
   return false;
}

// -------------------------------------------------------------- getDir()
// Accessor method for the snake's current direction.
// 0 = No movement  1 = up  2 = right  3 = down  4 = left
// Enumerated as NO_DIR, UP, RIGHT, DOWN, LEFT in the header file
// 
// pre:     None
// returns: int representing the current direction the snake is moving
//
int Snake::getDir()
{
   return dir;
}

// -------------------------------------------------------------- getPos()
// Accessor method for the snake's current position on the board.
// 
// pre:     None
// returns: COORD representing the current position the snake is in
//
COORD Snake::getPos()
{
   return pos;
}

// -------------------------------------------------------------- getBody()
// Accessor method for the first body segment attached to the snake head.
// 
// pre:     None
// returns: Body* pointer to the first Body struct attached to the head
//
Body* Snake::getBody()
{
   return nextBody;
}