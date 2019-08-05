#include "../include/test.h"
#include <stdio.h>
#include <stdlib.h>

int     check_length(int i)
{
    int length;

    length = 0;
    while (i > 9)
    {
        i /= 10;
        length++;
    }
    length++;
    return (length);
}

char*   my_itoa(int nmb)
{
    int length;
    char *str;
    int sign;
 
    sign = (nmb >= 0) ? 1 : -1; 
    nmb = (nmb < 0) ? (nmb * -1) : nmb;
    length = check_length(nmb);
    length = (sign == 1) ? length : (length + 1);
    str = (char *)malloc(sizeof(char) * (length + 1));
    str[length] = '\0';
    if (nmb == 0)
    {
        str[0] = '0';
        return(str);
    }
    while (nmb > 0)
    {
        str[--length] = nmb % 10 + 48;
        nmb /= 10;
    }
    str[0] = (sign == -1) ? '-' : (str[0]);
    return (str);
}
/*
int main()
{
    int i = -34;

    printf("%s\n", my_itoa(i));

}
*/
