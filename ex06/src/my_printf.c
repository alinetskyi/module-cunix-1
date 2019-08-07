#include "../include/test.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* my_itoa(int n) {
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

int my_printf(const char *format, ...) {
    va_list args;
    int arg_count;
    int i = 0;
    while (format[i] != '\0') {
      if ((format[i] == '\') && ((format[i+1] == "s") || (format[i+1] == "d"))) {
        arg_count++;
      }
      i++;
    }
    va_start(args,arg_count);
    i = 0;
    size_t k = 0;
    while (format[i] != '\\') {
      if (format[i] == '\0') { break; }
      k++;
      i++;
    }
    write(1,format, k);
    char *s;
    if (format[i + 1] == 'd') {
       int num = va_arg(args,int);	    
       s = my_itoa(num);      
    }
    else {
    s =va_arg(args,char*);
    }
    /*
    format = format + i ;
    size_t len = (size_t)strlen(s);
    write(,s,len);
    format = format + (int)len;
    */
}
