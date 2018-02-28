#include "allheaders.h"
#include<stdio.h>
#include<stdlib.h>
#ifdef _WIN32
#define TIMELIM 30
#else
#define TIMELIM 30000
#endif
int CurrentWidtht=600;
int CurrentHeightt=500;

struct Queue
{
  int r,f;
  Bullet* data[5000];
};typedef struct Queue Queue;
Queue qbullets;
void queueInit(Queue* q)
{
  q->f=0;
  q->r=0;
}

short qpush(Queue* q,Bullet* n)
{
  q->data[q->r]=n;
  q->r++;
  return 1;
}

void qpop(Queue* q)  //doesnt return
{
  if(q->r==q->f)
  {
    printf("underflow in queue\n");
    fflush(stdout);
  }
  Bullet* n=q->data[q->f];
  q->f++;
  n=(Bullet*)realloc(n,0);
  //printf("popped\n");
}

void queueDisplay(Queue* q)
{
  int i;
  for(i=q->f;i<q->r;i++)
  {
    printf("%d ",q->data[i]->x);
  }
}

short qEmpty(Queue* q)
{
  return (q->f)==(q->r);
}

int queueSize(Queue* q)
{
  return q->r-q->f;
}

void drawAllBulletsFromQueue()
{
    int i;
  for(i=qbullets.f; i<qbullets.r;i++)
  {
    Bullet *bullet = qbullets.data[i];
    drawBullet(bullet);
  }
}

double* genes;
void onMouseHandlingt(int b,int s,int x,int y)
{

    if(s==GLUT_DOWN)
    {
      float mx = (float) x;
      float my = (float) y;
      mx = mx - (CurrentWidtht / 2);
      my = (CurrentHeightt - my) - (CurrentHeightt / 2);
      if(timerbulletsp->TIMERSETFLAG==0)
      {
        qpush(&qbullets, newBullet(mx, my, 6, 4));
        setTimer(timerbulletsp);
      }
      else
      {
        if(elapsedTime(timerbulletsp)>TIMELIM)
        {
          qpush(&qbullets, newBullet(mx, my, 6,4));
          setTimer(timerbulletsp);
        }
      }
      glutPostRedisplay();
    }
}

void onKeyPresst(unsigned char key,int x,int y)
{
  switch(key)
  {
    case 'w': if(BOTSPEED<=9){BOTSPEED++;BULLETSPEED++;} break;
    case 's':if(BOTSPEED>1){BOTSPEED--;BULLETSPEED--;} break;
    case 'p': PAUSETIME+=500;break;
    case 'u': PAUSETIME-=500;break;
  }
}

short bulletDynamicsAndCollision2()             //TODO:Remove hardcoded
{
    Bot* player=Bot_arr[currentBot];
    int i;
    for(i=qbullets.f; i<qbullets.r;i++)
    {
        Bullet *bullet = qbullets.data[i];
        if ((bullet->x < (int) (windowleft)))
        {
            qpop(&qbullets);
        }
        else
        {
            moveBullet(bullet, -BULLETSPEED, 0);
            if (collided(player, bullet))
            {
                return 1;
            }
        }

    }
    return 0;
}

void spriteInit2()
{
    addBot(windowleft,0,BOTWIDTH,BOTHEIGHT);
    Bot_arr[currentBot]->genes=genes;
}

void initInputStylet()
{
  sensor_box_width=220;
  sensor_box_height=300;
  sensrows=5;
  senscols=3;
  sensorDx=sensor_box_width/senscols;
  sensorDy=sensor_box_height/sensrows;
  SensorMat=(double*)malloc(sizeof(double)*senscols*sensrows);
  printf("dim=%d\n",senscols*sensrows);
}

void renderFunctiont()
{
    Bot* bot=Bot_arr[currentBot];
    bot->isalive=1;
    //displayArray(bot->genes,noofgenes);
    Point p1; p1.x=bot->x-bot->dw; p1.y=bot->y+sensor_box_height/2;
    Point p2; p2.x=bot->x+bot->dw+sensor_box_width; p2.y=bot->y+sensor_box_height/2;
    Point p3; p3.x=bot->x+bot->dw+sensor_box_width; p3.y=bot->y-sensor_box_height/2;
    Point p4; p4.x=bot->x-bot->dw; p4.y=bot->y-sensor_box_height/2;
    //printf("dim=%d\n",senscols*sensrows);
    fillArray(SensorMat,senscols*sensrows,0.0);
    int i,j;
    for(i=qbullets.f;i<qbullets.r; i++)
    {
        Bullet* bullet=qbullets.data[i];
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

    if(bulletDynamicsAndCollision2())
    {
        printf("collided\n");fflush(stdout);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0,0,0);
    if(drawinwindowone)
        drawEverything(1);
    drawAllBulletsFromQueue();
    //input box
    glColor3f(1,0,0);
    //drawInputSensor(&p1,&p2,&p3,&p4);
    glutSwapBuffers();

    pause(PAUSETIME);
    if(drawinwindowone)
        glutPostRedisplay();
}

void renderFunctiont2()
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
  int i,j;
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


void idlet()
{

}

void Initialize2(int argc,char** argv)
{
    windowup=(int)(CurrentHeightt*0.8/2);
    windowdown= (int)(-CurrentHeightt*0.8/2);
    windowleft= (int)(-CurrentWidtht*0.8/2);
    windowright= (int)(CurrentWidtht*0.8/2);
    printf("%d %d %d %d\n",windowup,windowdown,windowleft,windowright);
    glutInit(&argc, argv);


    glutInitWindowSize(CurrentWidth2, CurrentHeight2);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(CurrentWidtht,0);
    glutCreateWindow("window2");
    glutDisplayFunc(renderFunctiont2);
    //glutKeyboardFunc(onKeyPress);
    glClearColor(0.0f,0.0f, 0.0f, 0.0f);
    gluOrtho2D(-CurrentWidth2/2,CurrentWidth2/2,-CurrentHeight2/2,CurrentHeight2/2);

    glutInitWindowSize(CurrentWidtht, CurrentHeightt);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutCreateWindow("window1");
    glutDisplayFunc(renderFunctiont);
    glutMouseFunc(onMouseHandlingt);
    glutIdleFunc(idlet);
    glutKeyboardFunc(onKeyPresst);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-CurrentWidtht/2,CurrentWidtht/2,-CurrentHeightt/2,CurrentHeightt/2);

}

int main(int argc,char** argv)
{
    Initialize2(argc,argv);
    initInputStylet();
    neuralnetInit();
    queueInit(&qbullets);
    initTimer(&timerbulletsp);
    FILE* fp=fopen("C:/NNinp15b4nonsim3.0/fixednn(copy)/genedata3_0/ok/1299notdead_50000","rb");
    if(fp)
    {printf("hmm");fflush(stdout);}
    int i;
    for(i=2; i<=LAYERS[0]; i++)
    {
      noofgenes+=(LAYERS[i]*LAYERS[i-1]+LAYERS[i]);
    }
    genes=(double*)malloc(sizeof(double)*noofgenes);
    printf("no of genes:%d",noofgenes);
    fread(genes,sizeof(double),noofgenes,fp);
    //displayArray(genes,noofgenes);
    spriteInit2();

    glutMainLoop();
}
