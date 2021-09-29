#include "stdio.h"
#include "string.h"

#define _CRT_SECURE_NO_WARNINGS

static int Str_Data, Str[10];

int* Function(int a, int* p)
{
	static int i;
	for (unsigned char i = 0; i < 10; i++)
	{
		if (*p++ > a)
		{
			Str[i++] = *p;
			Str_Data = Str[i];
			printf("%d", Str[i]);
		}
		return Str;
	}
		
}
 
void main()
{
	int(* Point)(int a, int* p);
	int* Array_Point;
	int A,B,i,number;
	char Array[10];

	printf("输入一个数字：\n");
	scanf_s("%d", &A);
	printf("输入一个数组：\n");
	
	for (i = 0; i < 10; i++)
	{
		number =scanf_s("%c", &Array[i]);
		printf("输入的数组：%c\n", Array[i]);
		printf("字符个数：%d\n", number);
	}
	Point = Function;
	printf("大于A的字符：\n");
	
	for (i = 0; i < number; i++)
	{
		Array_Point = Point(A, Array);
		printf("%d\n", *Array_Point++);
	}
}//kl