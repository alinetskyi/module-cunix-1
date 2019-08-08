#include "../include/test.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

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

int my_atoi(const char *s) {
    int res = 0;
    int i = 0;
    while (s[i] != '\0') {
        res = 10*res + s[i] - '0';
	i++;
    }
    return res;
}

unsigned int my_strlen(char *str) {
    int n = 0;
    while (*str++ != '\0') { n++; }
    return n;
}

int get_pad (const char *nptr) {
    int i, n = 0;
    for (i = 0; nptr[i]>='0' && nptr[i]<='9'; i++) { n++; }
    return n;
}

int str_print(char *str) {
    while (*str != '\0') {
       write(1,str,1);
       str++;
    }
    return 0;
}

void add_pad(char c, int cnt) {
   for (; cnt > 0; cnt--) { write(1,&c,1); }
}

int determination(const char *type, va_list *argptr)

{
  int flag=0;
    char *ptrOnArg;
    int width=0;
    int pad_to_char;
    int pad_to_string;
    if (*type=='0')
    {
      type++;
      flag=1;
    }
    switch(*type)
    {
     case 's':
     str_print(va_arg(*argptr, char *));
     return 2;

     case '%':
     write(1,"%",1);
     return 2;

     case 'd':
     ptrOnArg=my_itoa(va_arg(*argptr,int ));
     str_print(ptrOnArg);
     return 2;



     default:
     width=my_atoi(type);
     pad_to_char=get_pad(type);
     if (*(type+pad_to_char)=='d')
     {
       ptrOnArg=my_itoa(va_arg(*argptr,int ));
       pad_to_string=width- my_strlen(ptrOnArg);
     }
     else
     {
     ptrOnArg=va_arg(*argptr,char *);
     pad_to_string=width- my_strlen(ptrOnArg);
     }
     if (flag==1)
     {
      add_pad('0',pad_to_string);
     }
     else
     {
       add_pad(' ',pad_to_string);
     }
      str_print(ptrOnArg);
     return (pad_to_char+flag+2);
    }
    return 0;
}


int my_printf(const char *format, ...)
{

 int a=0;
 va_list argptr;
 va_start(argptr,format);
 while (format[a]!='\0')
  {
    if (format[a]=='%')
    {
      a=a+determination(format+a+1, &argptr);
    }
    if (format[a]=='\n')
    {
      break;
    }
    else
    {
      write (1,format+a,1);
      a++;
    }
  }
    write(1,"\n",1);
   va_end(argptr);
   return a;
}




