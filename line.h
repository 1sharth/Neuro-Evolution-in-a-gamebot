#pragma once
#include "allheaders.h"

struct Line
{
  int x1,y1,x2,y2;
  char isalive;
  Color color;
  int windowId;
};typedef struct Line Line;

int line_count=0;
Line *line_arr;

Line* addLine(int x1,int y1,int x2,int y2,Color* color)
{
  line_count++;
  if(line_count==0)
  {
    line_arr=(Line*)malloc(1*sizeof(Line));
  }
  else
  {
    line_arr=(Line*)realloc(line_arr,line_count*sizeof(Line));
  }
  line_arr[line_count-1].x1=x1;
  line_arr[line_count-1].y1=y1;
  line_arr[line_count-1].x2=x2;
  line_arr[line_count-1].y2=y2;
  line_arr[line_count-1].isalive='1';
  line_arr[line_count-1].color=*color;
  Line* l=&line_arr[line_count-1];
  return l;
}

void drawLine(Line* Line)
{
  //printf("%d %d      %d %d\n",Line->x1,Line->y1,Line->x2,Line->y2);
  fflush(stdout);
  glColor3ub(Line->color.r,Line->color.g,Line->color.b);
  glBegin(GL_LINES);
  glVertex2i(Line->x1,Line->y1);
  glVertex2i(Line->x2,Line->y2);
  glEnd();
}

void drawAllLines(int id)
{
  int i;
  for(i=0; i<line_count; i++)
  {
    if(line_arr[i].isalive=='1' && line_arr[i].windowId==id)
      drawLine(&line_arr[i]);
  }
}

void clearAllLines()
{
  int i;
  /*for(i=0; i<line_count; i++)
  {
    free(line_arr[i])
  }*/
  line_arr=(Line*)realloc(line_arr,0);
  line_count=0;
}