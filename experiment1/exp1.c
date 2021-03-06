#include <stdio.h>
#include "../perceptron/perceptron.h"
#include "../perceptron/digits.h"


int values[2] = {0,1};


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
		for(j=0;j<2;j++)
		{
			valueachieved = sum(&net->neurons[i],*digits[j]);
			//printf("%d\n",valueachieved);

			s = step(valueachieved);
			if(s < values[j])
			{
				modifyweights(&net->neurons[i],*digits[j],1);
				j=-1;
				epoch++;
			}
			else if(s > values[j])
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
	int j,k;
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
			printf("\t%d",testneuron(&net->neurons[0],*digits[d]));
		printf("\n");
	}
}


void distortions(neuralnet* net)
{
	int i,r;
	srand(time(NULL));

	printf("pattern\tanswer\n");
	for(i=0;i<10;i++)
	{
		r = rand()%30;
		*(*digits[0]+r) = !*(*digits[0]+r);
		printdigit(digits[0],net,0);
		//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[0]));
		printf("\n");
	}
	for(i=0;i<10;i++)
	{
		r = rand()%30;
		*(*digits[1]+r) = !*(*digits[1]+r);
		printdigit(digits[1],net,1);
		//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[1]));
		printf("\n");
	}
}


void testdigits(neuralnet* net)
{
	int i;
	printf("\npattern\tanswer\n");
	for(i=2;i<6;i++)
	{
		printdigit(digits[i],net,i);
		//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[0]));
		printf("\n");
	}
}


void exp1(int argc)
{
	int i;
	int entries = 2;
	neuralnet* net = newneuralnet(1,30,argc-1);
	training(net);

	printf("weights: ");
	for(i=0;i<31;i++)
	{
		printf("%d, ",net->neurons[0].weights[i]);
	}
	printf("\n");
	
	distortions(net);
	testdigits(net);
}


int main(int argc,char* argv[])
{
	exp1(argc);
	return 0;
}