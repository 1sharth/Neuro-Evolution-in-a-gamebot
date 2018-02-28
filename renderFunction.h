#pragma once
#include "allheaders.h"

int frames=0;
long botnotdeadtime=0;
/*double* getInput()
{

}*/

int sensor_box_width;
int sensor_box_height;
int sensrows;
int senscols;
int sensorDx;
int sensorDy;
double* SensorMat=NULL;

void initInputStyle()
{
  sensor_box_width=220;
  sensor_box_height=280;
  sensrows=5;
  senscols=3;
  sensorDx=sensor_box_width/senscols;
  sensorDy=sensor_box_height/sensrows;
  SensorMat=(double*)malloc(sizeof(double)*senscols*sensrows);
  printf("dim=%d\n",senscols*sensrows);
}

void drawInputSensor(Point* p1,Point* p2,Point* p3,Point* p4)
{
  glBegin(GL_LINE_LOOP);
  glVertex2d(p1->x,p1->y);
  glVertex2d(p2->x,p2->y);
  glVertex2d(p3->x,p3->y);
  glVertex2d(p4->x,p4->y);
  glEnd();
}

void fileWriteGenes(Bot* bot)
{
    sprintf(numchnotdead,"%ld",botnotdeadtime);
    sprintf(numch,"%d",noOfFiles++);
    strcat(numch,str);
    printf("str:%s\n",str);
    strcat(numch,numchnotdead);
    fp=fopen(numch,"wb");
    //resetFileStr();
    printf("botnotdeadtime> %ld happend\n",botnotdeadtime);fflush(stdout);
    fwrite(bot->genes,sizeof(double),(size_t)noofgenes,fp);
    fclose(fp);
}

void renderFunction()
{
  Bot* bot=Bot_arr[currentBot];
  bot->isalive=1;
  Point p1; p1.x=bot->x-bot->dw; p1.y=bot->y+sensor_box_height/2;
  Point p2; p2.x=bot->x+bot->dw+sensor_box_width; p2.y=bot->y+sensor_box_height/2;
  Point p3; p3.x=bot->x+bot->dw+sensor_box_width; p3.y=bot->y-sensor_box_height/2;
  Point p4; p4.x=bot->x-bot->dw; p4.y=bot->y-sensor_box_height/2;
  //printf("dim=%d\n",senscols*sensrows);
  fillArray(SensorMat,senscols*sensrows,0.0);

  int i;
  for(i=0;i<Bullet_count; i++)
  {
    Bullet* bullet=&Bullet_arr[i];
    if(bullet->x < p2.x && bullet->x > p1.x)
    {
      if(bullet->y< p2.y && bullet->y>p3.y)
      {
        double X=bullet->x-p1.x;
        double Y=p1.y-bullet->y;
        //printf("X=%f Y=%f\n",X,Y);
        int xpos=(int)(X/sensorDx);
        int ypos=(int)(Y/sensorDy);
        int realpos=(senscols)*ypos+xpos;
        //printf("real pos=%d\n",realpos);
        SensorMat[realpos]=1.0;
        //displayArray(SensorMat,sensrows*senscols);
      }
    }
  }
  //displayArray(SensorMat,11);
  neuralnetInitWithGenes(bot);
  double* out=neuralNetCalculate(SensorMat);
  int botmoveyy=0;

  if(out[0]>(out[1]))
    botmoveyy=BOTSPEED;
  else if(out[0]<(out[1]))
    botmoveyy=-BOTSPEED;
  else
    botmoveyy=0;
  //printf("botmoveyy=%d\n",botmoveyy);
  botDynamics(0,botmoveyy);
  out=(double*)realloc(out,0);

  if(bulletDynamicsAndCollision())
  {
    currentbull=0;
    for(i=1; i<Bullet_count; i++)
    {
      BULLETANIMATE[i]=0;
      Bullet_arr[i].distTrav=0;
    }
    Bullet_arr[0].distTrav=0;
    timestep=0;
    botnotdeadtime=0;
    BULLETSPAWNRANGEFULL=0;
    bot->isalive=0;
    bulletPlayerReset();
    if(!nextBot())
    {
      printf("---------------------------------------\ngen %d over:\n",current_gen++);
      printf("LastGenMaxFitness: %f\n",thisgenmaxfitness);
      printf("OverAllMaxFitness: %f\n",overallmaxfitness);
      printAllBotInfo();
      thisgenmaxfitness=0;
      evolve();

    }
    printf("current bot:%d\n",currentBot);
  }
  else
  {
    botnotdeadtime=(botnotdeadtime+1)%10000000;
    //printf("%d\n",botnotdeadtime);
    bot->fitness+=0.1;
    for(i=0; i<Bullet_count; i++)
    {
      Bullet* bullet=&Bullet_arr[i];
      if(bullet->x < p2.x && bullet->x > p1.x)
      {
        if(bullet->y< p2.y && bullet->y>p3.y)
        {
          if(bot->y+bot->h/2 < bullet->y-bullet->h/2 || bot->y-bot->h/2>bullet->y+bullet->h/2)
          {
            bot->fitness+=1.0;
          }
        }
      }

    }

    if(thisgenmaxfitness<bot->fitness)
      thisgenmaxfitness=bot->fitness;
    if(overallmaxfitness<bot->fitness)
      overallmaxfitness=bot->fitness;

  }
  if(botnotdeadtime==3500)
  {
    //BULLETSPAWNRANGEFULL=1;
      fileWriteGenes(bot);

  }
  if(botnotdeadtime==7000)
  {
      fileWriteGenes(bot);
  }
  if(botnotdeadtime==12000)
  {
      fileWriteGenes(bot);
  }
  if(botnotdeadtime==20000)
  {
      fileWriteGenes(bot);
  }
  if(botnotdeadtime==30000)
  {
    fileWriteGenes(bot);
  }
  if(botnotdeadtime==50000)
  {
    fileWriteGenes(bot);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0,0,0);
  if(drawinwindowone)
    drawEverything(1);
  //input box
  glColor3f(1,0,0);
  drawInputSensor(&p1,&p2,&p3,&p4);
  glutSwapBuffers();

  //printf("p1.x=%d p1.y=%d p2.x=%d p2.y=%d p3.x=%d p3.y=%d p4.x=%d p4.y=%d\n",p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);

  //moveBot(&Bot_arr[0]);
  Bullet_arr[currentbull].distTrav+=BULLETSPEED;
  if(Bullet_arr[currentbull].distTrav>(windowright-windowleft)/requiredNoOfBullets)
  {
    if(currentbull!=requiredNoOfBullets-1)
    {
      currentbull++;
      BULLETANIMATE[currentbull]=1;
    }
  }
  pause(PAUSETIME);
  if(drawinwindowone)
    glutPostRedisplay();
}

void renderFunction2()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0,0,0);
  clearAllLines();
  clearAllCircles();
  int xstep;
  xstep=(int)(CurrentWidth2/(LAYERS[0]-1));
  int ynodestart1=CurrentHeight2/2-10;
  int xnodestart1=-CurrentWidth2/2+10;
  int ynodestart2=CurrentHeight2/2-10;
  int xnodestart2=-CurrentWidth2/2+xstep;
  int step1,step2;
  int i,j,k;
  for(i=0; i<LAYERS[0]-1; i++)
  {

    step1=(int)(CurrentHeight2/LAYERS[i+1]);
    step2=(int)(CurrentHeight2/LAYERS[i+2]);

    for(j=0; j<LAYERS[i+1]; j++)
    {
      addCircle(xnodestart1,ynodestart1,2,&blue)->windowId=2;
      int k;
      for(k=0;k<LAYERS[i+2]; k++)
      {
        Line* l;
        if(result[i][j]*weights[i+1][k][j]<-0.6)
        {l=addLine(xnodestart1,ynodestart1,xnodestart2,ynodestart2,&red);l->windowId=2;}
        else if(result[i][j]*weights[i+1][k][j]>0.8)
        {l=addLine(xnodestart1,ynodestart1,xnodestart2,ynodestart2,&nicegreen);l->windowId=2;}
        ynodestart2-=step2;
      }
      ynodestart2=CurrentHeight2/2-10;
      ynodestart1-=step1;
    }
    ynodestart2=CurrentHeight2/2-10;;
    ynodestart1=CurrentHeight2/2-10;;
    xnodestart1=xnodestart2;
    if(i==0)
      xnodestart2+=xstep;
    else
      xnodestart2+=xstep;
  }
  drawAllLines(2);
  drawAllCircles(2);
  glutSwapBuffers();
  glutPostRedisplay();
}

void onMouseHandling(int state,int button,int x,int y)
{

}

void idle1()
{

}


void idle2()
{

}

void onKeyPress(unsigned char key,int x,int y)
{
  switch(key)
  {
    case 'w': if(BOTSPEED<=9){BOTSPEED++;BULLETSPEED++;} break;
    case 's':if(BOTSPEED>1){BOTSPEED--;BULLETSPEED--;} break;
      case 'p': PAUSETIME+=500;break;
      case 'u': PAUSETIME-=500;break;
  }
}
