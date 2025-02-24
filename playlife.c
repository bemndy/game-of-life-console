// playlife.c 
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lifefunc.h"



int main(int argc, char* argv[]) 
{

  char r_board[size][size];
  char t_board[size][size]; 
  char command = ' '; 
  char commands[50][100]; // amount of maximum commands per script is fifty
  int command_count = 0; // counts how many commands there are
  int mode = 0; // zero is interactive, one is batch
  int i = 0; // current command for while loop
  int placeholder; // placeholder for int functions


  initialize_board(r_board);

  

  while (1) {
    
    // start with empty board and displays it
    copy_board(r_board,t_board);  
    printf("\n");
    print_cboard(r_board);
 
    // interactive mode enabled when argc = one
    if (argc == 1) {
      printf("COMMAND: ");
      command = getchar();
      mode = 0; 
    }

    // batch mode enabled when argc = two 
    else if (argc == 2) {
      const char *filename = argv[1]; // filename becomes name of argument (first)
      command_count = load_script(commands, filename);
      if ( i <= command_count ) { 
	 
	// changes mode for add and remove function 
        mode = 1; 
        command = commands[i][0]; 
      }
      i++;
    }
    else if (argc >= 3) {
      system("clear"); 
      printf("too many arguments.\n"); 
      break;
    }
    
    
    // all command options
    if ( command == 'a') {
      placeholder = add_cell(r_board, mode, commands, i); 
    }
    else if ( command == 'n') { 
      check_rules1(r_board, t_board); 
    }
    else if ( command == 'r') { 
      placeholder = remove_cell(r_board, mode, commands, i);
    } 
    else if ( command == 'p') { 
      while (1) {
        check_rules1(r_board, t_board);
        usleep(117500); 	
	print_cboard(r_board);
      }      
    }
    else if ( command == 'q' ) {
    printf("Thank you!\n"); 
    return 1;
    } 
    else {
      system("clear"); 
      printf("Unknown command.\n"); 
    }

    // checks if batch mode is on, if it is the null character will not be red 
    // and first character from batch wile be read
    if (mode == 0) {
      while ( (command != '\n') && (command != EOF) ) { 
        command = getchar();
      }
    }
  }


  return 0; 
}


