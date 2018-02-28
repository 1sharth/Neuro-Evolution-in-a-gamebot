#pragma once
#include "allheaders.h"

struct Circle
{
  int x,y,r;
  char isalive;
  Color color;
  int windowId;
};typedef struct Circle Circle;

int circle_count=0;
Circle *circle_arr;

Circle* addCircle(int cx,int cy,int r,Color* color)
{
  circle_count++;
  if(circle_count==0)
  {
    circle_arr=(Circle*)malloc(1*sizeof(Circle));
  }
  else
  {
    circle_arr=(Circle*)realloc(circle_arr,circle_count*sizeof(Circle));
  }
  circle_arr[circle_count-1].x=cx;
  circle_arr[circle_count-1].y=cy;
  circle_arr[circle_count-1].r=r;
  circle_arr[circle_count-1].isalive='1';
  circle_arr[circle_count-1].color=*color;
  Circle* c=&circle_arr[circle_count-1];
  return c;
}

void drawCircle(Circle* circle)
{

  int xc=circle->x;
  int yc=circle->y;
  float r=(float)circle->r;
  glColor3ub(circle->color.r,circle->color.g,circle->color.b);
  glBegin(GL_POLYGON);
  float theta;
  for(theta=0; theta<=2*3.14; theta+=1/r)
    glVertex2i(r*cos(theta)+xc,r*sin(theta)+yc);
  glEnd();
}

void clearAllCircles()
{
  //free(circle_arr);
  circle_arr=(Circle*)realloc(circle_arr,0);
  circle_count=0;
}

void drawAllCircles(int id)
{
  int i;
  for(i=0; i<circle_count; i++)
  {
    if(circle_arr[i].isalive=='1' && circle_arr[i].windowId==id)
      drawCircle(&circle_arr[i]);
  }
}

