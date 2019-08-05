#include <stdlib.h>
#include <stdio.h>
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
  res = malloc(len + start);
  if (start) { res[0] = '-';}
  for (int i = len + start - 1; i >= start; i--) {
    res[i] = nn % 10;
    nn = nn/10;
  }
  return res;
}

int main() {
  int n = 12345689;
  char *s = my_itoa(n);
  for (int i=0; i < 8; i++){
    printf("%d",s[i]);
  }
  return 0;
}

