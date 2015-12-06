#include <stdio.h>
#include "../perceptron/perceptron.h"
#include "../perceptron/digits.h"


int values[16][4] = {
					{0,0,0,0},
					{0,0,0,1},
					{0,0,1,0},
					{0,0,1,1},
					{0,1,0,0},
					{0,1,0,1},
					{0,1,1,0},
					{0,1,1,1},
					{1,0,0,0},
					{1,0,0,1},
					{1,0,1,0},
					{1,0,1,1},
					{1,1,0,0},
					{1,1,0,1},
					{1,1,1,0},
					{1,1,1,1}
					};


int sum(neuron* n,int* input)
{
	int k;
	int valueachieved = 1*n->weights[0];
	for(k=1;k<31;k++,input++)
	{
		valueachieved += n->weights[k] * (*input);
	}
	return valueachieved;
}


int step(int value)
{
	return value > 0;
}


void modifyweights(neuron* n,int* input,int addition)
{
	int k,m;
	if(addition)
		m = 1;
	else
		m = -1;

	n->weights[0] += 1*m;
	for(k=1;k<31;k++,input++)
	{
		n->weights[k] += *input * m;
	}
}


int testneuron(neuron* n,int* input)
{
	int s = sum(n,input);
	return step(s);
}


void training(neuralnet* net)
{
	int i,j,k;
	int valueachieved;
	int s;
	int epoch=0;

	for(i=0;i<net->neuronqty;i++)
	{
		for(j=0;j<16;j++)
		{
			valueachieved = sum(&net->neurons[i],*digits[j]);
			//printf("%d\n",valueachieved);

			s = step(valueachieved);
			if(s < values[j][i])
			{
				modifyweights(&net->neurons[i],*digits[j],1);
				j=-1;
				epoch++;
			}
			else if(s > values[j][i])
			{
				modifyweights(&net->neurons[i],*digits[j],0);
				j=-1;
				epoch++;
			}				
		}
		epoch++;
	}
	printf("epochs: %d\n",epoch);
}


void printdigit(int digit[][5],neuralnet* net,int d)
{
	int j,k,i;
	for(j=0;j<6;j++)
	{
		for(k=0;k<5;k++)
		{
			if(digit[j][k])
				printf("@");
			else
				printf(" ");
		}
		if(j==2)
		{
			printf("\t");
			for(i=0;i<4;i++)
			{
				printf("%d",testneuron(&net->neurons[i],*digits[d]));
			}
		}
		printf("\n");
	}
}


void testdigits(neuralnet* net)
{
	int i;
	printf("\npattern\tanswer\n");
	for(i=0;i<16;i++)
	{
		printdigit(digits[i],net,i);
		//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[0]));
		printf("\n");
	}
}


void experiment4(int argc)
{
	int i,j;
	neuralnet* net = newneuralnet(4,30,argc-1);
	training(net);

	for(j=0;j<4;j++)
	{
		printf("weights: ");

		for(i=0;i<31;i++)
		{
			printf("%d, ",net->neurons[j].weights[i]);
		}
		printf("\n");
	}
	
	//distortions(net);
	testdigits(net);
}


int main(int argc,char* argv[])
{
	experiment4(argc);
	return 0;
}