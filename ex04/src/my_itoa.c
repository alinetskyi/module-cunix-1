#include <stdlib.h>
#include "../include/test.h"
char *my_itoa(int n) {
  char *res;
  int len = 1;
  int sign = 1;
  int start;
  if ( n < 0 ) { 
      sign = -1;
      n = -n;
  }
  int nn = n;
  while (1) {
    n = n/10;
    if (n == 0) { break; }    
    len++;
  }
  start = (sign == -1);
  res = malloc(len + start + 1);
  if (start) { res[0] = '-';}
  for (int i = len + start - 1; i >= start; i--) {
    res[i] = (nn % 10) +'0';
    nn = nn/10;
  }
  res[len+start] = '\0';
  return res;
}

