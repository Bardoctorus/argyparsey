#include<stdio.h>
#include<util.h>
#include<string.h>

int charCounter(char input[])
{
    int count = 0;
    for (size_t i = 0; i < strlen(input); i++)
    {
        count++;
    }
    return count;   
}

int adder(int a, int b){
    return a+b;
}