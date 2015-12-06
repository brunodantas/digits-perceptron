#include <stdio.h>
#include "../perceptron/digits.h"


void printdigits()
{
	int i,j,k;

	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{
			for(k=0;k<5;k++)
			{
				if(digits[i][j][k])
					printf("@");
				else
					printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}
}


void printdigits2()
{
	int i,j;
	int* value;

	for(i=0;i<6;i++)
	{
		value = *digits[i];
		for(j=0;j<30;j++,value++)
		{
			printf("%d",*value);
		}
		printf("\n");
	}
}


int main()
{
	printdigits();
	return 0;
}