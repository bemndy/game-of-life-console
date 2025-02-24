// playlife.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lifefunc.h"
#include <stdlib.h>

const int size = 40; 


void initialize_board(char board[size][size]) 
{

  // sets all the values to blank be default
 
  for (int i = 0 ; i < size ; i++) {
    for (int j = 0; j < size; j++) {
      board[i][j] = ' '; 
    }
  }


}



void print_cboard(char board[size][size]) 
{
  
  // print current state of the board or iteration


  // top row
  printf(" ");	
  for (int i = 0; i < size; i++) {
    printf("-"); 
  }
  printf("\n");

  // side rows
  for (int i = 0; i < size; i++) {
    printf("|"); 
    for (int j = 0; j < size; j++) {
      printf("%c", board[i][j]); 
    }
    printf("|");
    printf("\n"); 
  }

  // bottom row 
  printf(" ");
  for (int i = 0; i < size; i++) {
    printf("-");
  }

  printf("\n\n");  
		   
}

int load_script(char commands[50][100], const char *filename) 
{


  FILE *file = fopen(filename, "r"); 
  if (!file) { 
    printf("Error opening script file"); 
  }


  // max amount of characters per line in script 
  char line[100];
  int command_count = 0; 



  // copys command into new character array
  while ( ( fgets(line, sizeof(line), file) ) && ( command_count < 50 ) ) { 
    strcpy(commands[command_count], line); 
    command_count++;
  }

  fclose(file); 
  return command_count; 
}


void copy_board(char board[size][size], char tboard[size][size]) 
{

  // copies board (first input) into tboard (second input)


  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tboard[i][j] = board[i][j]; 
    }
  }
}

int add_cell(char board[size][size], int mode, char commands[50][100], int i)
{


  int r, c; 

  // add cell to the board at position entered by user
  if ( mode == 0 ) { 	  
    scanf("%d %d", &r, &c);
    if ( (r < 0 || r > size-1) || (c < 0 || c > size-1) ) {
      system("clear"); 
      printf("invalid points.\n"); 
      return 1; 
    } 
    board[r][c] = 'X';
  }

  // add cell to the board at position in script
  else if ( mode == 1 ) {
    r = atoi(&commands[i][2]);
    c = atoi(&commands[i][4]);   
    board[r][c] = 'X';
  }
}

int remove_cell(char board[size][size], int mode, char commands[50][100], int i)
{


  int r, c; 

  // remove cell to the board at position entered by user
  if ( mode == 0 ) {
    scanf("%d %d", &r, &c); 
    if ( (r < 0 || r > size-1) || (c < 0 || c > size-1) ) {
      system("clear"); 
      printf("invalid points.\n"); 
      return 1; 
    } 
    board[r][c] = ' ';
  }

  // remove cell to the board at position in script 
  else if ( mode == 1 ) { 
    r = atoi(&commands[i][2]); 
    c = atoi(&commands[i][4]); 
    board[r][c] = ' '; 
  }
}

void check_rules1(char board[size][size], char tboard[size][size]) 
{

  // new variable to keep track of neighbors of each cell
  int num_neighbors = 0; 
  

  copy_board(board,tboard); 

  // checking for neighbors where possible using algorithim
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      // resets count for each cell	    
      num_neighbors = 0;

      // checks for possible corner or side boundry 
      if (i == 0 && j == 0) {
        if (board[i][j+1] == 'X') num_neighbors++;
        if (board[i+1][j] == 'X') num_neighbors++;
        if (board[i+1][j+1] == 'X') num_neighbors++;
      } 
      else if (i == 0 && j == size - 1) {
        if (board[i][j-1] == 'X') num_neighbors++;
        if (board[i+1][j] == 'X') num_neighbors++;
        if (board[i+1][j-1] == 'X') num_neighbors++;
      }
      else if (i == size - 1 && j == 0) {
        if (board[i-1][j] == 'X') num_neighbors++;
        if (board[i][j+1] == 'X') num_neighbors++;
        if (board[i-1][j+1] == 'X') num_neighbors++;
            }
      else if (i == size - 1 && j == size - 1) {
        if (board[i-1][j] == 'X') num_neighbors++;
        if (board[i][j-1] == 'X') num_neighbors++;
        if (board[i-1][j-1] == 'X') num_neighbors++;
      }
      else if (i == 0) {
        if (board[i][j-1] == 'X') num_neighbors++;
        if (board[i][j+1] == 'X') num_neighbors++;
        if (board[i+1][j-1] == 'X') num_neighbors++;
        if (board[i+1][j] == 'X') num_neighbors++;
        if (board[i+1][j+1] == 'X') num_neighbors++;
      }
      else if (i == size - 1) {
        if (board[i][j-1] == 'X') num_neighbors++;
        if (board[i][j+1] == 'X') num_neighbors++;
        if (board[i-1][j-1] == 'X') num_neighbors++;
        if (board[i-1][j] == 'X') num_neighbors++;
        if (board[i-1][j+1] == 'X') num_neighbors++;
      }
      else if (j == 0) {
        if (board[i-1][j] == 'X') num_neighbors++;
        if (board[i+1][j] == 'X') num_neighbors++;
        if (board[i-1][j+1] == 'X') num_neighbors++;
        if (board[i][j+1] == 'X') num_neighbors++;
        if (board[i+1][j+1] == 'X') num_neighbors++;
      }
      else if (j == size - 1) {
        if (board[i-1][j] == 'X') num_neighbors++;
        if (board[i+1][j] == 'X') num_neighbors++;
        if (board[i-1][j-1] == 'X') num_neighbors++;
        if (board[i][j-1] == 'X') num_neighbors++;
        if (board[i+1][j-1] == 'X') num_neighbors++;
      } 

      // if not corner or side or top boundry then rules are applied to check eight positions of neighbors
      else {	      
        if ( board[i+1][j] == 'X' ) num_neighbors++; 
        if ( board[i-1][j] == 'X' ) num_neighbors++;
        if ( board[i][j-1] == 'X' ) num_neighbors++;
        if ( board[i][j+1] == 'X' ) num_neighbors++;
        if ( board[i-1][j-1] == 'X' ) num_neighbors++;
        if ( board[i-1][j+1] == 'X' ) num_neighbors++; 
        if ( board[i+1][j-1] == 'X' ) num_neighbors++;
        if ( board[i+1][j+1] == 'X' ) num_neighbors++;
      }

      // determine outcome based if its alive or dead first
      if ( board[i][j] == 'X' ) { 
        if ( (num_neighbors != 2) && (num_neighbors != 3) ) {
	  tboard[i][j] = ' ';	
	}
      }
      else {
        if ( num_neighbors == 3 ) { 
          tboard[i][j] = 'X'; 
	}
      }
    }
  }
  
  // copies tboard to regular board, order matters 
  // calls copy_board function
  copy_board(tboard, board); 
  

}



