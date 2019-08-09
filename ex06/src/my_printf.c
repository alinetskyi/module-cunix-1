#include "../include/test.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
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

int my_atoi(const char *s, int cnt) {
    int res = 0;
    int i = 0;
    while ( i < cnt) {   
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

int read_pad (const char *nptr) {
    int i, n = 0;
    for (i = 0; nptr[i]>='0' && nptr[i]<='9'; i++) { n++; }
    return n;
}

void str_print(char *str) {
    while (*str != '\0') {
       write(1,str++,1);
    }
}

void add_pad(char c, int cnt) {
   for (; cnt > 0; cnt--) { write(1,&c,1); }
}

int print_format(const char *s, va_list *args) {
    if (*s == '%') {
        write(1,"%",1);
	return 2;
    }
    if (*s == 's') {
        str_print(va_arg(*args,char *));
        return 2;
    }
    if (*s == 'd') {
        str_print(my_itoa(va_arg(*args,int)));
        return 2;
    }
    int flag = 0;
    if (*s == '0') {
	s++;
	flag = 1;
    }
    int shift = read_pad(s);
    int pad = my_atoi(s,shift);
    char *str;
    int len;
    if (*(s + shift) == 'd') {    
        str = my_itoa(va_arg(*args,int));
        len = my_strlen(str);
        pad = pad - len;
	if (flag) {
	add_pad('0',pad);
	} else { add_pad(' ',pad); }
	str_print(str); 
	return shift + 2 + flag;
    }
    if (*(s + shift) == 's') {
        str = va_arg(*args, char *);
	len = my_strlen(str);
	add_pad(' ',pad - len);
	str_print(str);
    }
    return shift + 2;
}

int my_printf(const char *format, ...) {
    va_list args;
    va_start(args,format);
    const char *i = format; 
    while (*i != '\0') {
        if (*i == '%') {
	    i = i + print_format(i+1,&args);
	}
	else { 
	    if (*i == '\n') {
	        break;
	    } else {
	        write(1,i++,1);
	    }
	}
    }  
    write(1,"\n",1);
    va_end(args);
    return 0; 
}	

