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
    for (i = 0; i < size; i++) {
        table[x][i].figure = 'B';
    }
    for (j = 0; j < size; j++) {
        table[j][y].figure = 'B';
    }
    table[x][y].figure = 'Q';   
    for (i = 1; (i < size - y) && (i < size - x); i++) {
        table[x + i][y + i].figure = 'B';
    }
    for (i=1; (i <= x) && (i < size - y); i++) {
        table[x - i][y + i].figure = 'B';
    }
    for (i=1; (i <= x) && (i <= y ); i++ ) {
      	table[x - i][y - i].figure = 'B';	    
    }
    for (i = 1; (i < size - x) && (i <= y); i++) {
        table[x + i][y - i].figure = 'B';
    }
}

void unplace_queen(Cell **table,int size,int x,int y) {
    table[x][y].figure = 'E';
}

int start(Cell **table,int size,int column,int x,int y) {     
    if ( column == y){
        int res = start(table,size,column + 1,x,y); 
	if (res != 1){
	    for (int i = 0; i < size; i++) {
	        if ( table[i][column - 1].figure == 'Q') {
		    table[i][column - 1].figure == 'B';
                    break;		    
	        }
	    return start(table,size,column - 1,x,y);	
	    }
	}
    }
    int j,flag;
    for (j = 0; j < size; j++) {
        if (table[j][column].figure == 'B') {
	     continue;
	}
        place_queen(table,size,j,column);
        
	print_table(table,size);

	flag = start(table,size,column+1,x,y);
       	if (flag) {return 1;}
	else {
        unplace_queen(table,size,j,column);
	}
    }    
}

void place_queens(Cell **table,int size) {
    int i,j,x,y,flag;
    flag = 0;    
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
    place_queen(table,size,x,y); 
    start(table,size,0,i,j);   
}

int main() {
    int size = 8;
    int x = 2, y = 2;    
    Cell **table = create_table(size,x,y);
    print_table(table,size);
    place_queens(table,size);
    print_table(table,size);
}

