#include <unistd.h>

int my_puts(const char *s) 
{
  int i = 0;
  while ( s[i] != '\0') 
  {
    write(1,s + i++,1);
  }
  write(1,"\n",1);
  return i;  
}
