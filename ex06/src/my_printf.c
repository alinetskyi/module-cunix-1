#include "../include/test.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int  my_strlen(char *str)
{
    unsigned int count;

    count = 0;
    if (str == 0)
        return (-1);
    while (*str)
    {
        str++;
        count++;
    }
    return (count);
}

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

void    my_putchar(char c)
{
    write(1, &c, 1);
}

int my_puts(const char *s)
{
    if (s == NULL)
        return (-1);
    int i = 0;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    return (0);
}

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

int     do_padding(char *str, int pad, int zero_flag)
{
    if ( pad != 0)
    {
        pad -= my_strlen(str);
        //pad = (pad < 0) ? 0 : pad;
        while (pad != 0)
        {
            if (zero_flag == 0)
                my_putchar(' ');
            else
                my_putchar('0');
            pad--;
        }
    }
    return (0);
}

int     my_printf(const char *format, ...)
{
    int     d;
    int     pad;
    int     zero_flag;
    char    *str;
    char    *tmp;
    va_list argptr;

    zero_flag = 0;
    d = 0;
    pad = 0;
    va_start(argptr, format);
    tmp = (char *)format;
    while (*tmp)
    {
        while (*tmp != '%' && *tmp != '\0')
        {
            my_putchar(*tmp);
            tmp++;
        }
        if (*tmp == '\0')
            return (0);
        tmp++;
        if (*tmp >= '0' && *tmp <= '9')
        {
            if (*tmp == '0')
                zero_flag = 1;
            while (*tmp >= '0' && *tmp <= '9')
            {   
                pad *= 10;
                pad += *tmp - '0';
                tmp++;
            }
            if (*tmp != 'd' && *tmp != 's')
                my_puts(my_itoa(pad));
        }
        if (*tmp == 's')
        { 
            str = va_arg(argptr, char *);
            pad = do_padding(str, pad, zero_flag);
            my_puts(str);
            tmp++;
        }
        else if (*tmp == 'd')
        {
            d = va_arg(argptr, int);
            str = my_itoa(d);
            pad = do_padding(str, pad, zero_flag);
            my_puts(str);
            tmp++;
        }
        else if (*tmp == '%')
            my_putchar('%');
        zero_flag = 0;
    }
    va_end(argptr);
    return (0);
}
