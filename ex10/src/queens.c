#include "../include/queens.h"

int is_free(Cell **table,int size,int x,int y) 
{ 
  int i;
  for (i = 0; i < size; i++) 
  {
    if (table[i][y].figure == 'Q') 
    {
      return 0;
    }
  } 
  for (i = 1; (i < size - y) && (i < size - x); i++) 
  {
    if (table[x + i][y + i].figure == 'Q') 
    {
      return 0;
    }
  }
  for (i = 1; (i <= x) && (i < size - y); i++) 
  {
    if (table[x - i][y + i].figure == 'Q') 
    {
 	  return 0;
    }
  }
  for (i = 1; (i <= x) && (i <= y ); i++ ) 
  {
    if (table[x - i][y - i].figure == 'Q') 
    {
      return 0;
    }	    
  }
  for (i = 1; (i < size - x) && (i <= y); i++) 
  {
    if (table[x + i][y - i].figure == 'Q')
    {
      return 0;
    }
  }
  return 1;
}

int search(Cell **table,int size, int row, int oc_row) 
{
  if (row == size) 
  {
  	return 1;
  }
  int i,res;  
  if (row == oc_row) 
  {
  	return search(table,size,row + 1,oc_row);	
  }  
  for (i = 0; i < size; i++) 
  {
    if (is_free(table,size,row,i) == 0) 
    {
      continue;
    }
    table[row][i].figure = 'Q';
    res = search(table,size,row + 1,oc_row);
    if (res) 
    {
      return 1;
    }
    table[row][i].figure = 'E';
  }
  return 0;
}

void place_queens(Cell **table,int size) 
{
  int i,j,flag = 0;
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    {
      if (table[i][j].figure == 'Q') 
      {
      	flag = 1;
      	break;
      }
    }
    if (flag) 
    {
      break;
    } 
  }	
  search(table,size,(i == 0),i);
}