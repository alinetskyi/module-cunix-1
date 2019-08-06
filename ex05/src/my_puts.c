#include <stdio.h>
int my_puts(const char *s) {
  int i = 0;
  while ( s[i] != '\0') {
    printf("%c",s[i]);
    i++;
  }
  if (i > 0) { i--; }
  printf("\n");
  return i;  
}
