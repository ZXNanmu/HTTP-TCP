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

	printf("����һ�����֣�\n");
	scanf_s("%d", &A);
	printf("����һ�����飺\n");
	
	for (i = 0; i < 10; i++)
	{
		number =scanf_s("%c", &Array[i]);
		printf("��������飺%c\n", Array[i]);
		printf("�ַ�������%d\n", number);
	}
	Point = Function;
	printf("����A���ַ���\n");
	
	for (i = 0; i < number; i++)
	{
		Array_Point = Point(A, Array);
		printf("%d\n", *Array_Point++);
	}
}//kl