// lifefunc.h


extern const int size; 


void initialize_board(char board[size][size]);
void print_cboard(char board[size][size]);
int load_script(char commands[10][100], const char *filename); 
void check_rules1(char board[size][size], char tboard[size][size]); 
int add_cell(char board[size][size], int mode, char commands[10][100], int command_count);
int remove_cell(char board[size][size], int mode, char commands[10][100], int command_count);
void copy_board(char board[size][size], char tboard[size][size]); 
void clear_newline(); 


