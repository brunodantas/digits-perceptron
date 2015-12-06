#include <stdlib.h>
#include <time.h>


typedef struct
{
	int* weights;
}
neuron;


typedef struct
{
	int inputqty;
	int neuronqty;
	neuron *neurons;
}
neuralnet;


neuralnet* newneuralnet(int neuronqty,int inputqty,int randomweights);