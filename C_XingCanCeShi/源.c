#include "stdio.h"


int max(int A, int B)
{
	int i;
	if (A > B)
	{
		i = A;
	}
	else
	{
		return B;
	}
	return i;
}
void main(void)
{
	printf("Max: %d", max(10, 1));
}