#include <stdio.h>
#include "../perceptron/perceptron.h"
#include "../perceptron/digits.h"


int values[6][6] = {{1,0,0,0,0,0},
					{0,1,0,0,0,0},
					{0,0,1,0,0,0},
					{0,0,0,1,0,0},
					{0,0,0,0,1,0},
					{0,0,0,0,0,1}};


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
		for(j=0;j<6;j++)
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
		{
			printf("\t%d",testneuron(&net->neurons[0],*digits[d]));
			printf("%d",testneuron(&net->neurons[1],*digits[d]));
			printf("%d",testneuron(&net->neurons[2],*digits[d]));
			printf("%d",testneuron(&net->neurons[3],*digits[d]));
			printf("%d",testneuron(&net->neurons[4],*digits[d]));
			printf("%d",testneuron(&net->neurons[5],*digits[d]));

		}
		printf("\n");
	}
}


void distortions(neuralnet* net)
{
	int i,r,p;
	srand(time(NULL));

	printf("pattern\tanswer\n");

	for(p=0;p<6;p++)
	{
		for(i=0;i<10;i++)
		{
			r = rand()%30;
			*(*digits[p]+r) = !*(*digits[p]+r);
			printdigit(digits[p],net,p);
			//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[0]));
			printf("\n");
		}
	}
}


void testdigits(neuralnet* net)
{
	int i;
	printf("\npattern\tanswer\n");
	for(i=0;i<6;i++)
	{
		printdigit(letters[i],net,i);
		//printf("\t%d\n\n",testneuron(&net->neurons[0],*digits[0]));
		printf("\n");
	}
}


void experiment3(int argc)
{
	int i,j;
	neuralnet* net = newneuralnet(6,30,argc-1);
	training(net);

	for(j=0;j<6;j++)
	{
		printf("weights: ");

		for(i=0;i<31;i++)
		{
			printf("%d, ",net->neurons[j].weights[i]);
		}
		printf("\n");
	}
	
	distortions(net);
	testdigits(net);
}


int main(int argc,char* argv[])
{
	experiment3(argc);
	return 0;
}