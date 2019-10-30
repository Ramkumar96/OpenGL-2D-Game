//checks whether the given token has been #defined earlier in the
//file or in an included file; if not, it includes the code between it and the closing
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 60 //define a constant MAX = 60 for the maximum length of snake

void initGrid(int,int); //declaring function for initializing the grid variables
void drawGrid();  //declaring function for drawing grid
void drawSnake();  //declaring function for drawing snake
void drawFood();  //declaring function for drawing food
void random(int&,int&);  //declaring function for getting random numbers

#endif // GAME_H_INCLUDED
