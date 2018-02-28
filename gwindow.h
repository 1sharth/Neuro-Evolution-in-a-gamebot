#pragma once
#include <GL/freeglut.h>
#include "allheaders.h"
int CurrentWidth = 512,CurrentHeight = 512;
int CurrentWidth2 = 750,CurrentHeight2 = 700;
int windowup;
int windowdown;
int windowleft;
int windowright;
int drawinwindowone=1;

void renderFunction();
void renderFunction2();
void onMouseHandling(int ,int , int , int );
void onKeyPress(unsigned char,int,int);
void onMouseHandling2(int ,int , int , int );
void idle1();
void idle2();
void Initialize(int argc,char** argv)
{
  windowup=(int)(CurrentHeight*0.6/2);
  windowdown= (int)(-CurrentHeight*0.6/2);
  windowleft= (int)(-CurrentWidth*0.8/2);
  windowright= (int)(CurrentWidth*0.8/2);
  printf("%d %d %d %d\n",windowup,windowdown,windowleft,windowright);
  glutInit(&argc, argv);

  
  glutInitWindowSize(CurrentWidth2, CurrentHeight2);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(CurrentWidth,0);
    glutCreateWindow("window2");
    glutDisplayFunc(renderFunction2);
    //glutKeyboardFunc(onKeyPress);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-CurrentWidth2/2,CurrentWidth2/2,-CurrentHeight2/2,CurrentHeight2/2);

    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutCreateWindow("window1");
    glutDisplayFunc(renderFunction);
    glutMouseFunc(onMouseHandling);
    //glutIdleFunc(idle);
    glutKeyboardFunc(onKeyPress);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-CurrentWidth/2,CurrentWidth/2,-CurrentHeight/2,CurrentHeight/2);



}
