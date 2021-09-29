#include<stdio.h>

int Callback_1() // Callback Function 1
{
    printf("Hello, this is Callback_1 ");
    return 0;
}

int Callback_2() // Callback Function 2
{
    printf("Hello, this is Callback_2 ");
    return 0;
}

int Callback_3() // Callback Function 3
{
    printf("Hello, this is Callback_3 ");
    return 0;
}

int Handle(int (*Callback)())
{
    printf("Entering Handle Function. ");
    Callback();
    printf("Leaving Handle Function. ");
}

int main()
{
    printf("Entering Main Function. ");
    Handle(Callback_1);
    Handle(Callback_2);
    Handle(Callback_3);
    printf("Leaving Main Function. ");
    return 0;
}