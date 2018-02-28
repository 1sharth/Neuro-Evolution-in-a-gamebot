#pragma once

#include "allheaders.h"

double SELECTIONPORTION=0.2;
double PARENTSELECTIONRATE=0.2;
double CHILDSELECTPORTION=0.3;
double MUTATIONRATE=0.08;
double MUTATIONCHANCE=0.25;
double PERTURBANCE=0.3;
int* parent_indices=NULL;
int parent_indices_size=0;
Bot** children=NULL;

void mutation(Bot* x)
{
  int i;
  for(i=0; i<noofgenes; i++)
  {
    if(getRandomfd(0,1)<MUTATIONRATE)
    {
      x->genes[i]+=(getRandomfd(-1,1)*PERTURBANCE);
    }
  }
}

Bot* breed(Bot* x,Bot* y)
{
  //printf("here for breeding\n");
  int i;
  Bot* newchild=newBot(windowleft,0,BOTWIDTH,BOTHEIGHT);
  for(i=0; i<noofgenes; i++)
  {
      newchild->genes[i]=((x->genes[i]*x->fitness)+(y->genes[i]*y->fitness))/(x->fitness+y->fitness);
      //printf("new child gene %d:%f\n",i,newchild->genes[i]);
  }
  if(getRandomfd(0,1)<MUTATIONCHANCE)
  {
    mutation(newchild);
  }
  return newchild;
}

void generateNewPopulation()
{
  int i,j;
  int size=(int)(CHILDSELECTPORTION*POPULATION);
  for(i=1; i<=size; i++)
  {
    Bot_arr[Bot_count-i]=(Bot*)realloc(Bot_arr[Bot_count-i],0);
    Bot_arr[Bot_count-i]=children[i-1];
    children[i-1]=NULL;
  }
  children=(Bot**)realloc(children,0);
}

void makeChildren()
{
  int size=(int)(CHILDSELECTPORTION*POPULATION);
  children=(Bot**)realloc(children,sizeof(Bot*)*size);
  int i;
  for(i=0; i<size; i++)
  {
    int n1=rand2()%parent_indices_size;
    int n2=rand2()%parent_indices_size;
    while(n2==n1) n2=rand2()%parent_indices_size;
    children[i]=breed(Bot_arr[parent_indices[n1]],Bot_arr[parent_indices[n2]]);
  }
  parent_indices=(int*)realloc(parent_indices,0);
}

void parentSelect()
{
  parent_indices=(int*)malloc((int)(SELECTIONPORTION*POPULATION)*sizeof(int));
  parent_indices_size=(int)(SELECTIONPORTION*POPULATION);
  int i;
  for(i=0; i<parent_indices_size; i++)
  {
    parent_indices[i]=i;
  }
  for(i=parent_indices_size; i<POPULATION; i++)
  {
    if(getRandomfd(0,1)<PARENTSELECTIONRATE)
    {
      parent_indices=(int*)realloc(parent_indices,sizeof(int)*(++parent_indices_size));
      parent_indices[parent_indices_size-1]=i;
    }
  }
  /*for(int i=0; i<parent_indices_size; i++)
  {printf("%d ",parent_indices[i]);fflush(stdout);}
  printf("\n\n");*/
}

void completelyRandomize(Bot* bot)
{
  int i;
  for(i=0; i<noofgenes; i++)
    bot->genes[i]=getRandomfd(-1,1);
}

void tweak()
{
  int t1=(int)(SELECTIONPORTION*POPULATION);
  int t2=(int)(CHILDSELECTPORTION*POPULATION);
  int i;
  for(i=t2; i<POPULATION-t1; i++)
  {
    if(getRandomfd(0,1)<0.5)
    {
      completelyRandomize(Bot_arr[i]);
    }
  }
}

void evolve()
{
  printf("evolving\n");fflush(stdout);
  botSort(Bot_arr,0,POPULATION-1);
  /*printf("before:\n");
  printAllGenes();*/
  parentSelect();
  makeChildren();
  generateNewPopulation();
  tweak();
  /*printf("after:\n");
  printAllGenes();*/
}
