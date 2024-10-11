/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width);

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width);

/* place your headers below */

