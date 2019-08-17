#include <stdlib.h>
#include "../include/test.h"

char *my_itoa(int n) {
  char *res;
  int sign,start,tmp,len = 1;
  sign = 1 - 2*(n < 0);
  n = sign * n;
  tmp = n;
  while (1) 
  {
    tmp = tmp/10;
    if (tmp == 0) 
    { 
      break; 
    }    
    len++;
  }
  start = (sign == -1);
  res = malloc(len + start + 1);
  res[0] = '-';
  for (int i = len + start - 1; i >= start; i--) 
  {
    res[i] = (n % 10) + '0';
    n = n/10;
  }
  res[len+start] = '\0';
  return res;
}

