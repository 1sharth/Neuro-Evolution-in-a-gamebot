#pragma once
#include "allheaders.h"

int LAYERS[]={4,15,100,100,2};
int currentBot=0;
int POPULATION=100;
double thisgenmaxfitness=0;
double overallmaxfitness=0;
int current_gen=0;
int BULLETSPAWNRANGEFULL=0;
int requiredNoOfBullets=4;
int timestep=0;
int BULLETANIMATE[]={1,0,0,0};
int currentbull=0;
int BULLETSPEED=4;
int BOTSPEED=7;
time_t PAUSETIME=0;
int BOTWIDTH=4;
int BOTHEIGHT=50;

char folder[]="genesData/";
int noOfFiles=0;
char str[]="notdead:";
char numch[1001];
char numchnotdead[1001];

FILE* fp;

void resetFileStr()
{
    folder[10]='\0';
}



