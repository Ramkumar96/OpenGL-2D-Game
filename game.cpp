#include<GL/gl.h>
#include<GL/glut.h> //GLUT is a library of utilities for OpenGL programs
#include<ctime> //converts the given time to  character representation of the date and time.
#include "game.h" //including game.h file

//The extern keyword tells the compiler that a variable is declared
// in another source module (outside of the current scope).
//The linker then finds this actual declaration and sets up the extern variable to point to the correct location.
extern int score;//getting the variable from other file

int gridX,gridY; //declaring integer variables to make gird
int snake_length = 5; //initial length of snake

bool food = true; //creating a boolean to check availability of food
int foodX,foodY; //position of food
short sDirection = RIGHT; //initializing the direction of snake to RIGHT
extern bool gameOver; //access declared boolean variable gameOver from main.cpp

int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16}; //Initial position of snake body at center of screen

//Defining function to initialize gridX,gridY
void initGrid(int x,int y)
{
    gridX = x;
    gridY = y;
}

//declaring unit function
void unit(int,int);

//Defining function to draw the grid
void drawGrid()
{
   for(int x=0;x<gridX;x++)
   {
       for(int y=0;y<gridY;y++)
       {
           unit(x,y); //calling unit function
       }
   }
}

//Defining function to draw simple square
void unit(int x,int y)
{
    //Setting the border of the grid to Red and 3.0 thickness
   if(x==0 || y==0 || x == gridX-1 || y==gridY-1)
    {
        glLineWidth(3.0); //set the 3.0 width of the  border line
        glColor3f(1.0,0.0,0.0); //set Red color to border line
    }
    else
    {
        glLineWidth(1.0); //set the normal width of the line
        glColor3f(0.0,0.0,0.0); //set Black-+ color to grid lines
    }

    glBegin(GL_LINE_LOOP); //loop first and last vertex will be connected
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

//Defining function to draw the food
void drawFood()
{
    if(food)
        random(foodX,foodY);
    food=false;
    glColor3f(0.0,1.0,0.0);
    glRectd(foodX,foodY,foodX+1,foodY+1); //position of food will be drawn
}

//Defining Function to draw snake
void drawSnake()
{
    for(int i = snake_length-1 ; i>0; i--)
    {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }

    if(sDirection==UP)
        posY[0]++;
    else if(sDirection==DOWN)
        posY[0]--;
    else if(sDirection==RIGHT)
        posX[0]++;
    else if(sDirection==LEFT)
        posX[0]--;

    for(int i=0 ; i < snake_length ; i++)
    {
        if(i==0)
            glColor3f(1.0,0.0,0.0); //head color is green
        else
            glColor3f(0.0,0.0,1.0); // body color is blue

        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1); // draw the snake
    }

    //if snake collide with border grid lines game is over collision detection only for head element
    if(posX[0]==0 || posX[0] == gridX-1 || posY[0] == 0 || posY[0] == gridY-1)
    gameOver=true; // Assign boolean variable gameOver to true

    if(posX[0] == foodX && posY[0] == foodY)//check whether food and head of snake collided
    {
        score++; //increment the score by one
        snake_length++; //increase of snake length while eating food
        if(snake_length>MAX)
            snake_length=MAX; //Maximum length of snake
        food=true;  //After snake ate food assign food value to true
    }

}

//Defining function to get random number
void random(int &x, int &y)
{
    int _maxX = gridX-2; //maximun random number 38
    int _maxY = gridY-2;
    int _min = 1; //minimum random number

    srand(time(NULL)); //seed random number
    //min + rand % (max-min)
    x = _min + rand() % (_maxX-_min);
    y = _min + rand() % (_maxY-_min);

}
