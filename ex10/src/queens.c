#include "../include/queens.h"
#include <stdio.h>
#include <stdlib.h>
Cell **create_table(int size,int x,int y) {
   Cell **table = malloc(size*sizeof(Cell*));	
   for (int i = 0; i < size; i++ ) {
       Cell *row = malloc(size*sizeof(Cell));	   
       table[i] = row;
       for (int j = 0; j < size; j++) {
           table[i][j].figure = 'E';
       }
   }
   table[x][y].figure = 'Q';
   return table;
}

void print_table(Cell **table,int size) {
   int i,j;	
   for (i = 0; i < size; i++) {
       for (j = 0; j < size; j++) {
           printf("%c ",table[i][j].figure);
       }
       printf("\n");
   }
   printf("\n");
}

void place_queen(Cell **table,int size,int x,int y) { 
    table[x][y].figure = 'Q';
    int i,j;

    for (i = y + 1; i < size; i++) {
        table[x][i].figure = 'B';
    }
    for (j = 0; ((j != x) && (j < size)); j++) {
        table[j][y].figure = 'B';

}   
    for (i = 1; (i < size - y) && (i < size - x); i++) {
        table[x + i][y + i].figure = 'B';
    }

    for (i=1; (i <= x) && (i < size - y); i++) {
        table[x - i][y + i].figure = 'B';
    }

}

void unplace_queen(Cell **table,int size,int x,int y) {
    table[x][y].figure = 'E';
}

int start(Cell **table,int size,int column) {     
    int j,flag;
    for (j = 0; j < size; j++) {
        if (table[j][column].figure == 'B') {
	     continue;
	}
        place_queen(table,size,j,column);
	flag = start(table,size,column+1);
       	if (flag) {return 1;}
	unplace_queen(table,size,j,column);
    }   
}

void place_queens(Cell **table,int size) {
    int i,j,x,y,flag = 0;	
    for (i = 0; i < size; i++ ) {
        for (j = 0; j < size; j++) {
	    if (table[i][j].figure == 'Q') {
		x = i; y = j;
		flag = 1;
		break;        
	    }
	}
	if (flag) { break; }
    }
    place_queen(table,size,i,j); 
    int res = start(table,size,1);   
}

int main() {
    int size = 8;
    int x = 0, y = 0;    
    Cell **table = create_table(size,x,y);
    print_table(table,size);
    place_queens(table,size);
    print_table(table,size);
}

