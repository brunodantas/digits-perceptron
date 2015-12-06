#include "perceptron.h"


neuralnet* newneuralnet(int neuronqty,int inputqty,int randomweights)
{
	int i,j,r;
	srand(time(NULL));
	neuralnet* net = (neuralnet*)  malloc(sizeof(neuralnet));

	net->neuronqty = neuronqty;
	net->inputqty = inputqty;
	net->neurons = (neuron*) malloc((inputqty+1)*sizeof(neuron));

	for(i=0;i<neuronqty;i++)
	{
		net->neurons[i].weights = (int*) malloc((inputqty+1)*sizeof(int));
		net->neurons[i].weights[0] = 0;

		if(randomweights)
		{
			for(j=0;j<inputqty+1;j++)
			{
				net->neurons[i].weights[j] = (rand()%200)-99;
			}
		}
		else
		{
			for(j=0;j<inputqty+1;j++)
			{
				net->neurons[i].weights[j] = 0;
			}
		}
	}

	return net;
}


