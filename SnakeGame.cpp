/** @file SnakeGame.cpp
 * @author Korosh Moosavi
 * @date 2021-08-05
 *
 * Snake game written to run on a Windows system.
 * Move the snake head with WASD or Arrow Keys
 * Snake is blocked from reversing back onto itself
 * 1 point is awarded per frame of movement and 1000 for eating food
 * High score board retains the top scores in a single game launch
 * 
 * SnakeGame.cpp file:
 * - Contains the main game logic to draw the board and manage objects
 * - Board size is set to 50 x 25 by default
 *   - Height should be ~1/2 of width for a square board
 *   - Due to the nature of the console window characters are less separated
 *     within a line than between lines, so vertical snake movement will
 *     be faster than horizontal
 * - Snake movement is set to 1 pixel per frame by default, set in the
 *   constructor parameters
 * - Highscore board retains 5 highest scores in a session, not named
 */

#include <iostream>
#include <conio.h>

#include "Snake.h"
#include "Food.h"

using namespace std;

const int W = 50;          // Board width
const int H = 25;          // Board height

Snake SNAKE({ W, H }, 1);  // Snake object with movespeed 1
Food FOOD({ W, H });       // Food object

bool PLAY = true;          // Check for game over
int SCORE = 0;             // Current score
int SCOREBOARD[5] = { 0, 0, 0, 0, 0 }; // Scoreboard

// -------------------------------------------------------------- board()
// This method prints the "board" the game takes place on
// 
// pre:    SNAKE and FOOD objects created
// post:   Visual representation of playspace printed to console
//
void board()
{
   COORD snakePos = SNAKE.getPos();
   COORD foodPos = FOOD.getPos();

   cout << "\t\tScore: " << SCORE << endl;         // Score display

   for (int i = 0; i < H; i++)                     // Print board
   {                                               // i = H = Y
      cout << "\t\t#";                             // j = W = X
      for (int j = 0; j < W - 1; j++)
      {
         if (i == 0 || i == H - 1) cout << "#";
         else if (i == snakePos.Y && j + 1 == snakePos.X) cout << "O";  // O = snake head
         else if (i == foodPos.Y && j + 1 == foodPos.X) cout << "X";    // X = food
         else
         {
            bool isBody = false;
            Body* cur = SNAKE.getBody();
            while (cur != NULL)
            {
               if (i == cur->pos.Y && j + 1 == cur->pos.X)
               {
                  cout << "o";                                          // o = snake body
                  isBody = true;
                  break;
               }
               cur = cur->next;
            }
            if (!isBody) cout << " ";
         }
      }
      cout << "#" << endl;
   }
}

int main()
{
   srand(time(NULL));                              // Randomize seed
   FOOD.newPos();                                  // Randomize food spawn

   PlayGame:                                       // New game
   while (PLAY)
   {
      board();                                     // Draw board
      if (SCORE > 0) SCORE++;                      // Increase score if movement has begun

      if (_kbhit())
      {
         switch (_getch())
         {
         case 224:                                 // Arrow keys
            switch (_getch())
            {
            case 72: SNAKE.turn(UP); break;
            case 77: SNAKE.turn(RIGHT); break;
            case 80: SNAKE.turn(DOWN); break;
            case 75: SNAKE.turn(LEFT); break;
            } break;
         case 'w': SNAKE.turn(UP); break;          // WASD
         case 'd': SNAKE.turn(RIGHT); break;
         case 's': SNAKE.turn(DOWN); break;
         case 'a': SNAKE.turn(LEFT); break;
         }
      }
      if (SCORE == 0 && SNAKE.getDir() > 0) SCORE++;// Begin incrementing score on movement

      if (SNAKE.collision())
      {
          PLAY = false;                            // Game over if snake collides with walls or body
      }

      if (SNAKE.eaten(FOOD.getPos()))
      {
         SCORE += 1000;                            // On eat, award points, grow snake, and spawn new food
         FOOD.newPos();
         SNAKE.grow();
      }

      SNAKE.move();                                // Move snake

      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Overwrite console
   }

   system("cls");
   
   cout << "\n\n\n\t\tGame Over" << endl;          // Display Game Over screen
   cout << "\t\tScore: " << SCORE << endl;
   cout << "\t\tHigh Scores: " << endl;
   int hold = SCORE;
   for (int i = 0; i < 5; i++)                     // Update scoreboard
   {
      if (hold > SCOREBOARD[i])
      {
         int temp = SCOREBOARD[i];
         SCOREBOARD[i] = hold;
         hold = temp;
      }
   }
   for (int i = 0; i < 5; i++)                     // Print scoreboard
   {
      cout << "\t\t" << SCOREBOARD[i] << endl;
   }

   cout << "\t\tEnter S to restart or any other key to exit.";
   char input;
   cin >> input;
   if (input == 'S' || input == 's')               // Option for New Game in Game Over screen
   {
      PLAY = true;                                 // Reset fields and restart while-loop
      SCORE = 0;
      SNAKE.reset();
      FOOD.newPos();
      system("cls");
      goto PlayGame;
   }
}
