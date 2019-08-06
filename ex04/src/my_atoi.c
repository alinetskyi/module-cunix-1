#include "../include/test.h"

int my_atoi(const char *nptr) {
  int res = 0;
  int i,sign = 1;

  i = 0;
  if (nptr[0] == '-') {
          sign = -1;
	  i = 1;
  }
  while ( nptr[i] != '\0') {
    if ((nptr[i] < 48) || (nptr[i] > 57)) {
      i++;
      continue;
    } 	  
    res = res * 10 + (nptr[i] - '0');
    i++;
  }
  res = res * sign;
  return (res);
}

