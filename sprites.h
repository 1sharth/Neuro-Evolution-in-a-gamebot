#pragma once
#include "allheaders.h"

int noofgenes=0;

struct Color
{
  int r,g,b;
};typedef struct Color Color;

Color black={0,0,0},red={255,0,0},green={0,255,0},white={255,255,255},blue={0,0,255},yellow={255,255,0}
,orange={255,100,4},nicegreen={145,255,0};

struct Point
{
  int x,y;
};typedef struct Point Point;

struct Bot
{
  int x,y,w,h,dw,dh;
  short isalive;
  Color color;
  int windowId;
  double* genes;
  double fitness;
};typedef struct Bot Bot;

int Bot_count=0;
Bot **Bot_arr;

Bot* newBot(int cx,int cy,int w,int h)
{
  Bot* bot=(Bot*)malloc(sizeof(Bot));
  bot->x=cx;
  bot->y=cy;
  bot->w=w;
  bot->h=h;
  bot->dh=h/2;
  bot->dw=w/2;
  bot->isalive=0;
  bot->windowId=1;
  bot->genes=(double*)malloc(sizeof(double)*noofgenes);
  bot->fitness=0;
  return bot;
}


int addBot(int cx,int cy,int w,int h)
{
  Bot_count++;
  if(Bot_count==0)
  {
    Bot_arr=(Bot**)malloc(1*sizeof(Bot*));
  }
  else
  {
    Bot_arr=(Bot**)realloc(Bot_arr,Bot_count*sizeof(Bot*));
  }
  Bot_arr[Bot_count-1]=(Bot*)malloc(sizeof(Bot));
  Bot_arr[Bot_count-1]->x=cx;
  Bot_arr[Bot_count-1]->y=cy;
  Bot_arr[Bot_count-1]->w=w;
  Bot_arr[Bot_count-1]->h=h;
  Bot_arr[Bot_count-1]->dh=h/2;
  Bot_arr[Bot_count-1]->dw=w/2;
  Bot_arr[Bot_count-1]->isalive=0;
  Bot_arr[Bot_count-1]->windowId=1;
  Bot_arr[Bot_count-1]->genes=(double*)malloc(sizeof(double)*noofgenes);
  Bot_arr[Bot_count-1]->fitness=0;
  Bot_arr[Bot_count-1]->color=white ;
  int i;
  for(i=0; i<noofgenes; i++)
  {
    Bot_arr[Bot_count-1]->genes[i]=getRandomfd(-1,1);
  }
  return Bot_count-1;
}

void drawBot(Bot* Bot)
{
  int dw=Bot->dw;
  int dh=Bot->dh;
  int x=Bot->x;
  int y=Bot->y;
  //printf("%d %d %d\n",Bot->color.r,Bot->color.g,Bot->color.b);
  //fflush(stdout);
  glColor3f(Bot->color.r,Bot->color.g,Bot->color.b);
  glBegin(GL_POLYGON);
  glVertex2d(x-dw,y+dh);
  glVertex2d(x+dw,y+dh);
  glVertex2d(x+dw,y-dh);
  glVertex2d(x-dw,y-dh);
  glEnd();
}

void moveBot(Bot* Bot, double xx,double yy)
{
  Bot->x+=(int)xx;
  Bot->y+=(int)yy;
}

void drawAllBots(int id)
{
  int i;
  //printf("draw Bot y:%d h/2:%d\n",player->y,(player->h)/2);
  for(i=0; i<Bot_count; i++)
  {
    //printf("%d\n",Bot_arr[i].windowId);
    if(Bot_arr[i]->isalive==1 && Bot_arr[i]->windowId==id)
      drawBot(Bot_arr[i]);
  }
}

short nextBot()
{
  currentBot++;
  if(currentBot==POPULATION)
  {
    currentBot=0;
    return 0;
  }
  return 1;
}


struct Bullet
{
  int x,y,w,h,dw,dh;
  short isalive;
  Color color;
  int windowId;
  int speed;
  int distTrav;
};typedef struct Bullet Bullet;

int Bullet_count=0;
Bullet *Bullet_arr;

Bullet* addBullet(int cx,int cy,int w,int h)
{
  Bullet_count++;
  if(Bullet_count==0)
  {
    Bullet_arr=(Bullet*)malloc(1*sizeof(Bullet));
  }
  else
  {
    Bullet_arr=(Bullet*)realloc(Bullet_arr,Bullet_count*sizeof(Bullet));
  }
  Bullet_arr[Bullet_count-1].x=cx;
  Bullet_arr[Bullet_count-1].y=cy;
  Bullet_arr[Bullet_count-1].w=w;
  Bullet_arr[Bullet_count-1].h=h;
  Bullet_arr[Bullet_count-1].dh=h/2;
  Bullet_arr[Bullet_count-1].dw=w/2;
  Bullet_arr[Bullet_count-1].isalive=1;
  Bullet_arr[Bullet_count-1].windowId=1;
  Bullet_arr[Bullet_count-1].distTrav=0;
  Bullet_arr[Bullet_count-1].color=red;
  return &Bullet_arr[Bullet_count-2];
}

Bullet* newBullet(int cx,int cy,int w,int h)
{
  Bullet* bullet=(Bullet*)malloc(sizeof(Bullet));
  bullet->x=cx;
  bullet->y=cy;
  bullet->w=w;
  bullet->h=h;
  bullet->dh=h/2;
  bullet->dw=w/2;
  bullet->isalive=1;
  bullet->windowId=1;
  bullet->distTrav=0;
  bullet->color=red;
  return bullet;
}

void bulletPlayerReset()
{
  Bot* player=Bot_arr[currentBot];
  //printf("at bulletplayer reset\n");
  int i;
  for(i=0; i<Bullet_count; i++)
  {
    Bullet* bullet=&Bullet_arr[i];
    player->y=0;
    bullet->x=windowright;
    int ymin,ymax;
    if(i==0)
    {
      ymin=player->y - (player->h)/2-5;
      ymax=player->y + (player->h)/2+5;
    }
    else
    {
      ymin=windowdown;
      ymax=windowup;
    }
    double y=getRandomfd(ymin,ymax);
    bullet->y=(int)y;
  }


}

void drawBullet(Bullet* Bullet)
{
  int dw=Bullet->dw;
  int dh=Bullet->dh;
  int x=Bullet->x;
  int y=Bullet->y;
  //printf("%d %d %d\n",Bullet->color.r,Bullet->color.g,Bullet->color.b);
  //fflush(stdout);
  glColor3f(Bullet->color.r,Bullet->color.g,Bullet->color.b);
  glBegin(GL_POLYGON);
  glVertex2d(x-dw,y+dh);
  glVertex2d(x+dw,y+dh);
  glVertex2d(x+dw,y-dh);
  glVertex2d(x-dw,y-dh);
  glEnd();
}

void moveBullet(Bullet* Bullet, double xx,double yy)
{
  Bullet->x+=(int)xx;
  Bullet->y+=(int)yy;
}

void drawAllBullets(int id)
{
  int i;
  //printf("draw Bullet y:%d h/2:%d\n",player->y,(player->h)/2);
  for(i=0; i<Bullet_count; i++)
  {
    //printf("%d\n",Bullet_arr[i].windowId);
    if(Bullet_arr[i].isalive==1 && Bullet_arr[i].windowId==id)
      drawBullet(&Bullet_arr[i]);
  }
}

void drawEverything(int id)
{
  drawAllBots(id);
  drawAllBullets(id);
}


short collided(Bot* Bot1, Bullet* Bot2)
{
  if((Bot1->x+Bot1->w/2 > Bot2->x-Bot2->w/2) && (Bot1->x-Bot1->w/2 < Bot2->x+Bot2->w/2))
  {
    if((Bot1->y+Bot1->h/2 > Bot2->y-Bot2->h/2) && (Bot1->y-Bot1->h/2 < Bot2->y+Bot2->h/2))
    {
      return 1;
    }
  }
  return 0;
}
void botDynamics(int xx,int yy)
{
  if(Bot_arr[currentBot]->y+yy>windowdown && Bot_arr[currentBot]->y+yy<windowup)
  {
    //printf("lol:playery:%d yy:%d\n",Bot_arr[playerind].y,yy);
    moveBot(Bot_arr[currentBot],xx,yy);
  }
}

void bswap(Bot** x,Bot** y)
{
  Bot* temp=*x;
  *x=*y;
  *y=temp;
}

void botSort(Bot** Arr,int l,int r)
{
  int j,i=l+1;
  if(l<r)
  {
    for(j=l+1; j<=r; j++)
      if(Arr[j]->fitness > Arr[l]->fitness)
        bswap(&Arr[j],&Arr[i++]);
    bswap(&Arr[i-1],&Arr[l]);
    botSort(Arr,l,i-2);
    botSort(Arr,i,r);
  }
}

short bulletDynamicsAndCollision()             //TODO:Remove hardcoded
{
  Bot* player=Bot_arr[currentBot];
  int i;
  for(i=0; i<Bullet_count;i++)
  {
    Bullet *bullet = &Bullet_arr[i];
    if(i!=0 && !BULLETANIMATE[i])
      continue;
    if ((bullet->x < (int) (windowleft)))
    {
      bullet->x = (int) (windowright);
      //int ymin=player->y - (player->h)/2-5;
      //int ymax=player->y + (player->h)/2+5;
      int ymin, ymax;
      if (i==0)
      {
        ymin = player->y - (player->h) / 2 - 5;
        ymax = player->y + (player->h) / 2 + 5;
      }
      else
      {
        ymin = windowdown;
        ymax = windowup;
      }
      double y = getRandomfd(ymin, ymax);
      bullet->y = (int) y;
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

void spriteInit()
{
  int i;
  for(i=2; i<=LAYERS[0]; i++)
  {
    noofgenes+=(LAYERS[i]*LAYERS[i-1]+LAYERS[i]);
  }
  printf("noofgenes=%d\n",noofgenes);
  for(i=0; i<POPULATION; i++)
  {addBot(windowleft,0,BOTWIDTH,BOTHEIGHT);}
  for(i=0; i<requiredNoOfBullets; i++)
  {
    addBullet(windowright,0,4,2);
  }

}

void printAllGenes()
{
  int i,j;
  for(i=0; i<Bot_count; i++)
  {
    printf("bot %d genes= ",i);
    for(j=0; j<noofgenes; j++)
    {
      printf("%f ",Bot_arr[i]->genes[j]);
    }
    printf("\n");
  }
}

void printAllBotInfo()
{
  printf("\n");
  int i;
  for(i=0; i<Bot_count; i++)
  {
    printf("bot %d fitness:%f alive:%d\n",i,Bot_arr[i]->fitness,Bot_arr[i]->isalive);
  }
  printf("\n");
}


