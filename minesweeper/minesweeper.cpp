#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

/* add your functions here */

bool is_complete(char mines[9][9], char revealed[9][9]){
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      // if there is a ? without there being a bomb underneath
      if (revealed[row][col] == '?' && mines [row][col] != '*') {
	return false;
      }
    }
  }
  return true;

}

void convertToRowCol(const char * position, int &row, int &col) {
  // 'A1' = 00
  // 'A9' = 08
  row = position[0] - 'A';
  col = position[1] - '1';  
}

void convertToPos(char * position, int row, int col) {
  // 'A1' = 00
  // 'A9' = 08
  position[0] = row + 'A';
  position[1] = col + '1';
}



bool isMine(int row, int col, char mines[9][9]) {
  return (mines[row][col] == '*');
}


int count_mines_row_col(int row, int col, char mines[9][9]){
  int mineCount = 0;
  // want every combination of: n, n+1, n-1 w/ m, m+1, m-1
  // how to do elegantly?

  for (int n = -1; n < 2; n++) {
    // if there is a mine in the horizontal row above
    if (isMine(row-1, col+n, mines)){
	mineCount++;
      }
    // checks current square redunant as would end game before
    if (isMine(row, col+n, mines)){
      mineCount++;
      }
    if (isMine(row+1, col+n, mines)){
      mineCount++;
    }
  }
  return mineCount;
}


int count_mines(const char * position, char mines[9][9]){
  int row = -1;
  int col = -1;

  convertToRowCol(position, row, col);
  // // cout << row << col << endl;
  // int mineCount = 0;
  // // want every combination of: n, n+1, n-1 w/ m, m+1, m-1
  // // how to do elegantly?

  // for (int n = -1; n < 2; n++) {
  //   // if there is a mine in the horizontal row above
  //   if (isMine(row-1, col+n, mines)){
  // 	mineCount++;
  //     }
  //   // checks current square redunant as would end game before
  //   if (isMine(row, col+n, mines)){
  //     mineCount++;
  //     }
  //   if (isMine(row+1, col+n, mines)){
  //     mineCount++;
  //   }
  // }
  // return mineCount;
  return count_mines_row_col(row, col, mines);
}

bool validPosition(int row, int col){
  return (row >=0 && row <9 && col >=0 && col <9);
}


void setSurroundingBlank(int row, int col, char revealed[9][9]){
  for (int n = -1; n < 2; n++) {
    // if there is a mine in the horizontal row above
    revealed[row-1][col+n] = ' ';
    revealed[row][col+n] = ' ';
    revealed[row+1][col+n] = ' ';  
  }
}

void recurBlank(int row, int col, char revealed[9][9], char mines[9][9]){
  // base case if there is a mine in a surrounding square
  // check if the square is already empty
  if (!validPosition(row, col)|| revealed[row][col] == ' ') {
      return;
  }  
  if (count_mines_row_col(row, col, mines) != 0) {
    return;
  }
  // onlt make square blank if all surrounding squares are blank?
  revealed[row][col] = ' ';

      // Recursive calls for all surrounding squares
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the current square
            recurBlank(row + i, col + j, revealed, mines);
        }
    }
}
  // setSurroundingBlank(row, col, revealed);
  // int rowAbove = -1;
//   int rowMid = -1;
//   int rowBelow = -1;
//   int newCol = -1;

//   // the problem is having overlapping squares --> infinite recursion for between squares
//    for (int n = -1; n < 2; n++) {
//      rowAbove = row-1;
//      rowMid = row;
//      rowBelow = row+1;
//      newCol = col+n;
//      // if the current col is same
//      if (newCol == col) {
//      if (!(rowAbove == row)) {
//        recurBlank(rowAbove, newCol, revealed, mines);
//      }
//      if (!(rowMid == row)) {
//      recurBlank(rowMid, newCol, revealed, mines);
//      }
//      if (!(rowBelow == row)) {
//        recurBlank(rowBelow, newCol, revealed, mines);
//      }
//      // check that the row is different to current
//      }
//    }
// }



MoveResult make_move(const char * position, char mines[9][9], char revealed[9][9]){
  // revaled is input/output parameter == current board
  // mines is input parameter

  // position is e.g. 'A1'
  int row = -1;
  int col = -1;
  convertToRowCol(position, row, col);
  // cout << row << col << endl;

  // If the index if out of bounds
  if (!validPosition(row, col)) {
    return INVALID_MOVE;
  }
  //Check if a third character and if it is a '*'
  int length = strlen(position);
  if (length > 3){
    return INVALID_MOVE;
  }

  if (length == 3) {
     // the flag logic i.e. make revealed as a *
    if (position[2] == '*') {
      // if sqare already flagged
      if (revealed[row][col] == '*') {
	return REDUNDANT_MOVE;
      }
      else{
	// if the square is not already marked then valid move to set flag
	revealed[row][col] = '*';
	return VALID_MOVE;
      }
    }
    else{
      // third char was not a *
      return INVALID_MOVE;
    }
  }

  // Check if the game is over - i assume another function will use this return value to know
  if (is_complete(mines, revealed)) {
    return SOLVED_BOARD;
  }

  //Check if blown up after checking third character!
  if (mines[row][col] == '*') {
    return BLOWN_UP;
  }

  // Check if redundant actual move
  if (revealed[row][col] != '?') {
    return REDUNDANT_MOVE;
  }

  int mineCount = count_mines(position, mines);
  if (mineCount == 0) {
    //setSurroundingBlank(row, col, revealed);
       recurBlank(row, col, revealed, mines);
    // revealed[row][col] = ' ';
    //setSurroundingBlank(row, col, revealed);
    // for each of the surrounding squares
    // if count = 0
    // call setSurroundingBlank + check all the surrounding squares to 0
    // if count != 0 return
    // add recursive stuff here
  }
  else{
    // not al squares are empty
    // make the current square the mine count
    revealed[row][col] = static_cast<char>(mineCount + '0');
  }
  
 
  // IMPORTANT will have to recursively do it until no more positions surrounded by all blank squares??
  //if no other characters are present in position == uncover square in revealed
  // if there are no adjacent mines, the square becomes blank and all adjacent squares are recursively uncovered.
  // i.e. input is 'A1'

  // if there are other characters
  // e.g. 'A1*'
  // it is set as a FLAG in revealed

  return VALID_MOVE;

}


/* enum MoveResult { INVALID_MOVE=-3,
  REDUNDANT_MOVE=-2,
  BLOWN_UP=-1,
  SOLVED_BOARD=1,
  VALID_MOVE=0 };

A player can use the digits displayed on squares to deduce that one
or more squares definitely contains a mine (and should be flagged).
For example, in the middle panel of Figure 1, it can be deduced that
squares A5 and A6 contain mines since otherwise B5 would not have
the value 2. Equally, a player may deduce that it is safe to uncover
one or more squares. For example, because H3 is flagged and G2 has
the value 1, it must be safe to uncover F1, G1, H1 and H2.
*/


bool find_safe_move(char revealed [9][9], char move [512]){
  // will return true/false is the move is safe?
  int idx = 0;
  for (int row = 0; row < 9 ;row++) {
    for (int col = 0; col < 9; col++) {
      // find a place where we havent moved yet
      if (revealed[row][col] == '?'){
	char position[3];
	convertToPos(position, row, col);
	// cout << position << endl;
	move[idx++] = (char)(position[0]);
	move[idx++] = (char)(position[1]);
	move[idx++]= '*';
	//	move[idx++]= ' ';
	move[idx++]= '\0';
	return true;
	// then find squares that are definitely bombs and resulting are safe?
	// if next to a 1 that is surrounded by blanks or other numbers --> bomb
	
	// int rowAbove = row-1;
	// int rowMid = row;
	// int rowBelow = row+1;
	// int newCol = -1;
         
	// for (int n = -1; n < 2; n++) {
	//     newCol = col+n;
	//     if (validPosition(rowAbove, newCol)){
	//       if (revealed[rowAbove][newCol] == 
	//     }
	//     if (validPosition(rowMid, newCol)){
	      
	//     }
	//     if (validPosition(rowBelow, newCol)){

	//     }
	// }
	// if a number in all surrounding squuares = false for sure
      }
    }
  }
  return false;
  *move = '\0';

}



