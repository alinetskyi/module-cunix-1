#include "../include/test.h"
int my_strcmp(char *s1, char *s2) {
    int i = 0;
    while (1) {
    	if (s1[i] == '\0') {
          return ((s2[i] == '\0') - 1); 
	}
    	if (s2[i] == '\0') { 
	  return ((s1[i] == '\0') - 1);
	}
    	if (s1[i] > s2[i]) { return  1; }
    	if (s1[i] < s2[i]) { return -1;}
    	i++;	
    }
    return 0;
}   
