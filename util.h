#pragma once
#include "allheaders.h"

int rand2()
{
  time_t t=clock();
  srand((unsigned)t);
  return rand();
}

//returns random double data type between low and high inclusive
double getRandomfd(int low,int high)
{
  time_t t=clock();
  srand(t);
  double ri=rand()%(high-low)+low;
  ri+=((double)(rand()%10000000))/10000000;
  return ri;
}

//returns array of random double data type between low and high inclusive
double* getRandomfdv(int low,int high,int size)
{
  int i;
  double* v=(double*)malloc(size*sizeof(double));
  for(i=0; i<size; i++)
    v[i]=getRandomfd(low,high);
  return v;
}

/*every ith element of target array gets multiplied by that of source
array and hence target array gets modified
*/
void arrayMul(double* source,double *target, int size)
{
  int i;
  for(i=0; i<size; i++)
  {
    target[i]*=source[i];
  }
}

/*every ith element of source array is added to that of target
array and hence target array gets modified
*/
void arrayAdd(double* source,double *target, int size)
{
  int i;
  for(i=0; i<size; i++)
  {
    target[i]+=source[i];
  }
}

/*returns addition of all elements inside an array */
double arrayElementsAdd(double* source,int size)
{
  int i,sum=0;
  for(i=0; i<size; i++)
    sum+=source[i];
  return sum;
}

/*returns multiplication of all elements inside an array */
double arrayElementsMul(double* source,int size)
{
  int i,prod=1;
  for(i=0; i<size; i++)
    prod*=source[i];
  return prod;
}

double max(double x,double y)
{
  return x>y?x:y;
}

/*returns the value of 1/(1+e^-x)*/
double relu(double x)
{
  return max(0.0,x);
}

double sigmoidFunc(double x)
{
  return 1/(1+pow(2.71828,-x));
}


/*returns array containing values between indexes l(inclusive)
and r(exclusive) with given dir.
dir='l' means from left and dir='r' means from right
*/
double* extract(double* source,char dir,int l,int r)
{
  int k=0,i;
  double* x=(double*)malloc(sizeof(double)*(r-l));
  if(dir=='l')
  {
    for(i=l; i<r; i++)
      x[k++]=source[i];
  }
  else if(dir=='r')
  {
    for(i=r; i>l; i--)
      x[k++]=source[i];
  }
  return x;
}

void swap(int* x, int* y)
{
  int temp=*x;
  *x=*y;
  *y=temp;
}



void quicksort(int* A,int l,int r)
{
  int j,i=l+1;
  if(l<r)
  {
    for(j=l+1; j<=r; j++)
      if(A[j]<A[l])
        swap(&A[j],&A[i++]);
    swap(&A[i-1],&A[l]);
    quicksort(A,l,i-2);
    quicksort(A,i,r);
  }
}

void fillArray(double* A,int n,double x)
{
  int i;
  for(i=0; i<n; i++)
  {
    A[i]=x;
  }

}


void displayMatrix(double** X,int rows,int cols)
{
    int i,j;
  for(i=0; i<rows; i++)
  {
    for( j=0; j<cols; j++)
    {
      printf("%f ",X[i][j]);
    }
    printf("\n");
  }

}
void displayArray(double* X,int n)
{
  int i;
  for(i=0; i<n; i++)
    printf("%f ",X[i]);
  printf("\n");
}

double* matMulLimited(double* A,int n1,double** B,int m2,int n2)
{
  int i,j;
  double* ans=(double*)malloc(sizeof(double)*m2);
  for(i=0; i<m2; i++)
    ans[i]=0.0;
  //displayMatrix(B,m2,n2);

  for(i=0; i<m2; i++)
    for(j=0; j<n2; j++)
      ans[i]+=A[j]*B[i][j];
  return ans;
}
//Testing of above function
/*
double A[3]={1,1};
double B[][2]={
        {8,0},
        {1,0},
        {3,1},
        {4,1},
        {0,0},
};

double** C=(double**)malloc(sizeof(double*)*5);
for(int i=0;i<5;i++)
C[i]=B[i];
double* Z=matMulLimited(A,2,C,5,2);
displayArray(Z,5);
*/

void pause(time_t x)
{
    time_t a= clock();
    while(clock()-a<=x)
        ;
}

struct Timer
{
  int TIMERSETFLAG;
  time_t a;
};typedef struct Timer Timer;

Timer* timerbulletsp;

void initTimer(Timer** t)
{
  *t=(Timer*)malloc(sizeof(Timer));
  (*t)->TIMERSETFLAG=0;
}

void setTimer(Timer* t)
{
  t->TIMERSETFLAG=1;
  t->a=clock();
}

time_t elapsedTime(Timer* t)
{
  return clock()-t->a;
}

