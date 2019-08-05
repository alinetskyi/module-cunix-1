#include "../include/test.h"
#include <stdio.h>
#include <stdlib.h>

int     my_atoi(const char *nptr)
{
    int i;
    int number;
    int sign;

    sign = 1;
    number = 0;
    i = 0;
    while (*(nptr + i) == ' ' || *(nptr + i) == '\t')
        i++;
    if (*(nptr + i) == '+' || *(nptr + i) == '-')
    {
        sign = (*(nptr + i) == '-') ? -1 : 1;
        i++;
    }
    while (*(nptr + i) && (*(nptr + i) >= '0' && *(nptr + i) <= '9'))
    {
        number *= 10;
        number += *(nptr + i) - 48;
        i++;
    }

    return (number * sign);
}
/*
int main()
{
    char *str="1k";
    
    printf("%d\n", my_atoi(str));
    printf("orig:%d\n", atoi(str));
}
*/
