#pragma once
#include "allheaders.h"


double*** weights=NULL;
double**  bias=NULL;
double**  result=NULL;

void neuralnetInit()
{
  weights=(double***)malloc(sizeof(double**)*LAYERS[0]);
  int noofweights=1;
  int i,j;
  for(i=0; i<LAYERS[0];i++)
  {
    weights[i]=(double**)malloc(sizeof(double*)*LAYERS[i+1]);
    for(j=0; j<LAYERS[i+1]; j++)
    {
      //printf("i=%d j=%d has %d weights\n",i,j,noofweights);
      weights[i][j]=(double*)malloc(sizeof(double)*noofweights);
      /*for(int k=0; k<noofweights; k++)
      {
        weights[i][j][k]=getRandomfd(-1,1);
      }*/
    }
    noofweights=LAYERS[i+1];
  }

  bias=(double**)malloc(sizeof(double*)*LAYERS[0]);
  result=(double**)malloc(sizeof(double*)*LAYERS[0]);
  for(i=0; i<LAYERS[0]; i++)
  {
    bias[i]=(double*)malloc(sizeof(double)*LAYERS[i+1]);
    result[i]=(double*)malloc(sizeof(double)*LAYERS[i+1]);
  }
}

void neuralnetInitWithGenes(Bot* bot)
{
  int genesindex=0;
  int i,j,k;
  for(i=1; i<LAYERS[0];i++)
  {
    for(j=0; j<LAYERS[i+1]; j++)
    {

      for(k=0; k<LAYERS[i]; k++)
      {
        weights[i][j][k]=bot->genes[genesindex++];
      }
    }
  }
  //printf("after weights init, genesindex=%d\n",genesindex);
  for(i=1; i<LAYERS[0]; i++)
  {
    for(j=0; j<LAYERS[i+1]; j++)
    {
      bias[i][j]=bot->genes[genesindex++];
    }

  }
  //printf("after bias init, genesindex=%d\n",genesindex);
}

void printNeuralNetwork()
{
    int i,j,k;
  for(i=1; i<LAYERS[0];i++)
  {
    printf("\nLayer:%d\n",i);
    for(j=0; j<LAYERS[i+1]; j++)
    {
      printf("  node no:%d\n",j);
      printf("   w: ");
      for( k=0; k<LAYERS[i]; k++)
      {
        printf("%f ",weights[i][j][k]);
      }
      printf("\n");
    }
  }
  printf("\nBias\n");
  for(i=1; i<LAYERS[0]; i++)
  {
    printf("\nLayer:%d\n",i);
    printf("  bias: ");
    for(j=0; j<LAYERS[i+1]; j++)
    {
      printf("%f ",bias[i][j]);
    }
    printf("\n");
  }
}

double* neuralNetCalculate(double* inp)
{
  double* inpt=inp;
  double* out=NULL;
  double* oldout=NULL;
  int geneidex=0;
  int i,j;
  for(j=0; j<LAYERS[1]; j++)
  {
    result[0][j]=inp[j];
  }

  for(i=1; i<LAYERS[0]; i++)
  {
    out=matMulLimited(inpt,LAYERS[i],weights[i],LAYERS[i+1],LAYERS[i]);
    for(j=0; j<LAYERS[i+1]; j++)
    {
      out[j]+=bias[i][j];
      if(i==LAYERS[0]-1)
        out[j]=relu(out[j]);
      else
        out[j]=sigmoidFunc(out[j]);
      result[i][j]=out[j];
    }
    oldout=(double*)realloc(oldout,0);   //TODO:Garbage collection action
    inpt=out;
    oldout=out;
    //displayArray(out,LAYERS[i+1]);
  }
  //double* out=matMulLimited(inp,LAYERS[1],weights[1],LAYERS[2],LAYERS[1]);
  return out;                             //TODO:Garbage collection needs to delete
                                          // this out variable from where this func was called
}

