/** @file Food.h
 * @author Korosh Moosavi
 * @date 2021-08-05
 *
 * Snake game written to run on a Windows system
 * Move the snake head with WASD or Arrow Keys
 * Snake is blocked from reversing back onto itself
 * 1 point is awarded per frame of movement and 1000 for eating food
 * High score board retains the top scores in a single game launch
 *
 * Food.h:
 * - Contains the private fields used by Food objects
 */
#ifndef FOOD_H
#define FOOD_H

#pragma once

#include <Windows.h>
#include <cstdlib>

class Food
{
private:
   COORD board;         // Dimensions the board the game is being played on
   COORD pos;           // Current position of the food object

public:
   Food();              // Default constructor
   Food(COORD board);   // Parameter constructor
   void newPos();       // Position generator
   COORD getPos();      // Accessor for pos
};

#endif