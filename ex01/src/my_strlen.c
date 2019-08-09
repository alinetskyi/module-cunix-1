#include "libft.h"

unsigned int  ft_strlen(char *str)
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
