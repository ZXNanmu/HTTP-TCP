#include "stdio.h"
#include "string.h"


static int Str[10];

int *Function(int a,int *p)
{
	static int i;
	if(*p++ > a)
	{
		Str[i++] = *p;
		if (i == 10)
		{
			for (int j; j < i; j++)
			{
				printf("%d",Str[i]);
				return Str;
			}
		}
	}
}
void main()
{
	int* Point(int a, int* p);
	int A, InputArray[10], Reslut[10], ReslutData,i;
	const* ConstPoint;
	printf("输入一个数字：");
	scanf("%d", &A);
	printf("输入一个数组：");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", InputArray[i]);
	}
	Point = Function;
	printf("大于A的字符：");
	Reslut[i] = Point(A, InputArray);
	for (i=0;i<10;i++)
	{
		
		printf("%d",Reslut[i]);
	}
}