#include <stdlib.h>
#include <stdio.h>
#include "../include/test.h"
char *my_strcpy(char *dest, const char *src) {
	int i = 0; 
	while (src[i] != '\0') {
	  dest[i]= src[i];
	  i++;
	}
	return dest;
}
