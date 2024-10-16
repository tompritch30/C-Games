#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Not allowed because '3' already in sub-board
  cout << endl << "Putting '3' into F8 is ";
  if (!make_move("F8", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Not allowed because B5 already contains '5'
  cout << endl << "Putting '3' into B5 is ";
  if (!make_move("B5", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
    save_board("medium-solution.dat", board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  /*
  cout << "=================== Bonus Question =====================" << endl << endl;

  for (int n=1; n<=3; n++) {
    cout << "Working on mystery board number " << n << "..." << endl;
    char filename[64], solutionfilename[64];
    sprintf(filename, "mystery%d.dat", n);
    sprintf(solutionfilename, "mystery%d-solution.dat", n);
    load_board(filename, board);
    if (solve_board(board)) {
      cout << "The '" << filename << "' board has a solution:" << endl;
      display_board(board);
      save_board(solutionfilename, board);
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;
  }
  */
  return 0;
}
