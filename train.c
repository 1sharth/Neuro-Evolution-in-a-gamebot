#include "allheaders.h"



int main(int argc,char** argv)
{
  Initialize(argc,argv);
  initInputStyle();
  neuralnetInit();
  spriteInit();
  //printNeuralNetwork();
  glutMainLoop();
}