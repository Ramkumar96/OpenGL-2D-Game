#include<GL/gl.h> //HEADER FOR openGL
#include<GL/glut.h> //GLUT is a library of utilities for OpenGL programs
#include "game.h" //including header file game.h
#include<stdlib.h>//including  standard library of utility functions such as string conversion routines

#define COLUMNS 40 //X CORDINATE
#define ROWS 40 // Y CORDINATE
#define FPS 10 //10 frames in one second

extern short sDirection; //Access the sDirection keyword from another file using extern.

bool gameOver=false; //Declaring a boolean variable and assign it to false

int score=0;

void timer_callback(int);
void display_callback(); //define the function
void reshape_callback(int,int); //Two parameters width and height of window after reshaped
void keyboard_callback(int,int,int); //ASCII OF key pressed,position of mouse at the time of key pressed

void init()
{
    glClearColor(0.0,0.0,0.0,1.0); //RGB Alpha
    initGrid(COLUMNS,ROWS); //calling the function

}

int main(int argc, char **argv) //main function in C++
{
    glutInit(&argc,argv); //initialize glut,should be start before all glut methods
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500); //width and height
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display_callback);//Register callback function
    glutReshapeFunc(reshape_callback); //whenever window max,min or moved
    glutTimerFunc(0,timer_callback,0); //only once
    glutSpecialFunc(keyboard_callback);
    init(); //calling the init function
    glutMainLoop(); //At this point processing of all will start and window will display

    return 0;
}


void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); //clearing the color buffer
    drawGrid(); //Draw the grid after color buffer cleared
    drawSnake(); //calling draw snake function
    drawFood(); //
    glutSwapBuffers(); //swap the frames in double buffers

    //if boolean varible gameOver is True code will be executed
    if(gameOver)
    {
        char _score[10]; //declaring string array
        itoa(score,_score,10);//function to convert integer value to characters,base is 10
        char text[50]= "Your Score:";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);  //window.header file already included in glut.h
        exit(0);
    }
}

//defining reshape callback function
void reshape_callback(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h); //x,y,width,height ,viewport will cover whole area of window
    glMatrixMode(GL_PROJECTION); // changed matrix mode to projection
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0); //setting up orthographic projection for 2D game, (left.right.bottom.top.znear.zfar)
    glMatrixMode(GL_MODELVIEW); //model view matrix

}

void timer_callback(int)
{
    glutPostRedisplay(); //display function will be called as soon as possible
    glutTimerFunc(1000/FPS,timer_callback,0); //   glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds.
}

//key board inputs
void keyboard_callback(int key,int,int)
{
    //changing the direction of snake according to keyboard input
    switch(key)
    {
        case GLUT_KEY_UP:
            if(sDirection != DOWN)
                sDirection=UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection != UP)
                sDirection=DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection != LEFT)
                sDirection=RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection != RIGHT)
                sDirection=LEFT;
            break;
    }
}
