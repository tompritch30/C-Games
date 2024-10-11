#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

#include"maze.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch ,char ** maze, int height, int width, int &row, int &col){
  for (int irow = 0; irow < height; irow++){
    for (int jcol = 0; jcol < width; jcol++) {
      // if the letter in pos in maze if the same, update row and return true
      if (maze[irow][jcol] == ch) {
        row = irow;
        col = jcol;
        return true;
      }
    }
  }
  // letter not found set to -1 and return false
  row = -1;
  col = -1;
  return false;
}

Direction dirStrToEnum(char dir){
  if (dir == 'N'){
    return NORTH;
  }
  else if (dir == 'E'){
    return EAST;
  } 
  else if (dir == 'S'){
    return SOUTH;
  }
  else if (dir == 'W') {
    return WEST;
  }
  else {
    return UNKNOWN;
  }
}

bool isInBounds(const int height, const int width, const int row, const int col){
  return (row >=0 && col >=0 && row < height && col < width);
}

// default end is 'X'
bool isSpaceOrEnd(char ** maze, const int height, const int width, const int row, const int col, char end){
  // check in bounds
  if (!isInBounds(height, width, row, col)) {
    return false;
  }
  //if the character is a space or not
  return (maze[row][col] == ' ' || maze[row][col] == end);
}

bool newDir(char ** maze, const int height, const int width, int &row, int &col, Direction currentDir, char end){
  // North is -1, and W is -1. row is up/down, col = west/east
  // N, E, S, W
  int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  // Direction enum has the same order of values  
  int tempRow = row + offset[currentDir][0];
  int tempCol = col + offset[currentDir][1];

  // check that the new space is a space or the end
  if (isSpaceOrEnd(maze, height, width, tempRow, tempCol, end)) {
    row = tempRow;
    col = tempCol;
    return true;
  }
  // the current position (row, col) is unchanged
  return false;
}

bool valid_solution(const char * path, char ** maze, int height, int width, int currentRow, int currentCol, const int endRow, const int endCol, Direction currentDir){
  // if the path is the end and we are at the target position
  if (*path == '\0' && currentRow == endRow && currentCol == endCol) {
    return true;
  }
  // ensure direction is known
  if (currentDir == UNKNOWN) {
      return false;
    }
  // update the current position using the direction, if not a space or X will return false
  
  if (newDir(maze, height, width, currentRow, currentCol, currentDir, 'X')){
    // need to update direction for the new elemeent in path
    path++;
    // update current Dir using the next letter in path
    currentDir = dirStrToEnum(*path);
    return valid_solution(path, maze, height, width, currentRow, currentCol, endRow, endCol, currentDir);

  }
  return false;
}

bool valid_solution(const char * path, char ** maze, int height, int width){
  // wall characters: -, +, | vs free characters = ' ' and 'X' for end
  // start character >, end character X
  // enum Direction {NORTH, EAST, SOUTH, WEST, UNKNOWN};
  int currentRow, currentCol, endRow, endCol;
  find_marker('>' ,maze, height, width, currentRow, currentCol);
  find_marker('X' ,maze, height, width, endRow, endCol);
  if (!isInBounds(height, width, currentRow, currentCol) || !isInBounds(height, width, endRow, endCol)){
    return false;
  } 
  
  // get the current direction as an enum
  Direction currentDir = dirStrToEnum(*path);
  if (currentDir == UNKNOWN) {
    //cout << *path << "unknown dir" << endl;
    return false;
  }
  return valid_solution(path, maze, height ,width, currentRow, currentCol, endRow, endCol, currentDir);
}

#include <cmath>
#include <algorithm>

// Function to calculate Euclidean distance
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Comparator function for sorting
bool comp(const std::pair<char, double>& a, const std::pair<char, double>& b) {
    return a.second < b.second;
}

void newDirArray(int currentRow, int currentCol, int endRow, int endCol, char *directions) {
    std::pair<char, double> dirDistances[4];

    // Calculate distances for each direction
    dirDistances[0] = {'N', distance(currentRow - 1, currentCol, endRow, endCol)};
    dirDistances[1] = {'W', distance(currentRow, currentCol - 1, endRow, endCol)};
    dirDistances[2] = {'S', distance(currentRow + 1, currentCol, endRow, endCol)};
    dirDistances[3] = {'E', distance(currentRow, currentCol + 1, endRow, endCol)};

    // Sort the directions based on distance
    std::sort(dirDistances, dirDistances + 4, comp);

    // Update the directions array
    for (int i = 0; i < 4; ++i) {
        directions[i] = dirDistances[i].first;
    }
}

bool find_path(char ** maze, const int height, const int width, int currentRow, int currentCol, const int endRow, const int endCol, char * path, char end){
   static int count = 0;
  if (currentRow == endRow && currentCol == endCol) {
    // ensure null termination
    cout << count << endl;
    *path = '\0';
    return true;
  }
 
  
  
  char directions[] = "NWSE";
  // newDirArray(currentRow, currentCol, endRow, endCol, directions);
  for (int i = 0; i < 4; i++) {
    char strDir = directions[i];
    // get the current direction as an enum
    Direction currentDir = dirStrToEnum(strDir);
    
    // need to maintain row in loops as newDir will change it
    int row = currentRow;
    int col = currentCol;
    // if the new position is valid
    if (newDir(maze, height, width, row, col, currentDir, end) && maze[row][col] != '#'){
        count++;
      // update path to have the current direction, increment done after
      //print_maze(maze, height, width);
      *path++ = directions[i];
      // terminator be overwritten in next loop
      *path = '\0';
      
      // update the current pos on the maze  
      maze[row][col] = '#';
      // pass in end to allow ending on not just 'X'
      if (find_path(maze, height, width, row, col,endRow, endCol, path, end)){
        return true;
      }
      // undo changes to the maze
      maze[row][col] = ' ';
      // revert to the previous position, not sure is required.
      row = currentRow;
      col = currentCol;
      // the position we added to path should be removed
      *(--path) = '\0';
    } 
  }
  // tried every position and failed
  return false;
}

char * find_path(char ** maze, int height, int width, char start, char end){
  // static as not sure if we can alter main for the exam?
  static char path[MAX_SIZE] = "";
  strcpy(path, "no solution");
  
  // find the starting and endpos
  int currentRow, currentCol, endRow, endCol;
  find_marker(start ,maze, height, width, currentRow, currentCol);
  find_marker(end ,maze, height, width, endRow, endCol);
  
  // overwrite the starting square
  maze[currentRow][currentCol] = '#';
  // check in bounds before continuing
  if (!isInBounds(height, width, currentRow, currentCol) || !isInBounds(height, width, endRow, endCol)){
    return path;
  } 
  // strcpy(path, "no solution");
  if(find_path(maze, height, width, currentRow, currentCol, endRow, endCol, path, end)){
    return path;
  }
  else{
    // find path may not have updated if false
    strcpy(path, "no solution");
    return path;
  }
  
}









































// bool find_marker(char ch ,char ** maze, int height, int width, int &row, int &col){
//   for (int rowIdx = 0; rowIdx < height; rowIdx++) {
//     for (int colIdx = 0; colIdx < width; colIdx++) {
//       if (maze[rowIdx][colIdx] == ch) {
// 	row = rowIdx;
// 	col = colIdx;
// 	return true;
//       }
//     }
//   }
//   return false;
// }

// bool valid_solution_finder(const char * path, char ** maze, int height, int width, int row, int col){
//   if (*path == '\0') {
//     // cout << " in the base case for " << *path << endl;
//     // Base case
//     // Check if we are the final case
//     if (maze[row][col] == 'X'){
//       return true;
//     }
//     // cout << "the final pos is not an X" << endl;
//     return false;
//   }

//   if (maze[row][col] == '+' || maze[row][col] == '|' || maze[row][col] == '-' || maze[row][col] == '#'){
//     // print_maze(maze, height, width);
//     // cout << "valid_solution_finder hit a wall!" << endl;
//     return false;
//   }
//   // if out of bounds
//   if (!(row >=0 && row < height && col >=0 && col < width)) {
//     return false;
//   }

//   // cout << "the current pos is: " << row << col << endl;

//  enum Direction {NORTH, EAST, SOUTH, WEST };
//   Direction currentDir;
//   if (*path == 'N') {
//     // row--;
//     currentDir = NORTH;
    
//   }
//   else if (*path == 'E') {
//     // col++;
//     currentDir = EAST;
//   }
//   else if (*path == 'S') {
//     // row++;
//     currentDir = SOUTH;
//   }
//   else if (*path == 'W') {
//     // col--;
//     currentDir = WEST;
//   }
  
//     switch (currentDir)
//     {
//         case NORTH:
// 	  row--;
// 	  //     std::cout << "NORTH\n";
//             break;
//         case EAST:
// 	  col++;
// 	  //std::cout << "EAST\n";
//             break;
//         case SOUTH:
// 	  row++;
// 	  //std::cout << "SOUTH\n";
//             break;
//         case WEST:
// 	  col--;
// 	  //std::cout << "WEST\n";
//             break;
//     }
    
//     return valid_solution_finder(++path, maze, height, width, row, col);
// }

// bool valid_solution(const char * path, char ** maze, int height, int width){
//   int currentRow = -1;
//   int currentCol = -1;
//   // int finalRow = -1;
//   // int finalCol= -1;
 
//   find_marker('>', maze, height, width, currentRow, currentCol);
//   // find_marker('X', maze, height, width, finalRow, finalCol);

//   // if path == '\0' { end and check at finalRow, finalCol)
//   // move in direction for N, E, S, W == row--, col++, row++, col--
//   // check if square is: -, +, | --> return false;
//   // if not update currentPos and repeat

//   return valid_solution_finder(path, maze, height, width, currentRow, currentCol);
// }

// void make_move(char ** maze, int currentRow, int currentCol) {
//   maze[currentRow][currentCol] = '#';
// }


// bool empty_square(char direction, char **maze, int row, int col, int height, int width, char end) {
//     // Check if the move is within bounds
//     if (row < 0 || row >= height || col < 0 || col >= width) {
//         return false;
//     }
//     // Check if the square is empty or the goal 'X'
//     return maze[row][col] == ' ' || maze[row][col] == end;
// }



// bool find_path(char ** maze, int height, int width, int currentRow, int currentCol, int finalRow, int finalCol, char * path, char end) {
//     if (currentRow == finalRow && currentCol == finalCol) {
//         *path = '\0'; // Null-terminate the path string
//         return true;
//     }

//     // print_maze(maze, height, width);

//     // Directions: N, E, S, W
//     const char *directions = "NWSE";
//     int dRow[] = {-1, 0, 1, 0};
//     int dCol[] = {0, -1, 0, 1};

//     for (int i = 0; i < 4; ++i) {
//         int newRow = currentRow + dRow[i];
//         int newCol = currentCol + dCol[i];
//         char direction = directions[i];

//         // Check if the move is valid and not revisiting a previously visited path
//         if (empty_square(direction, maze, newRow, newCol, height, width, end) && maze[newRow][newCol] != '#') {
//             // Make the move
//             maze[newRow][newCol] = '#';
//             *path = direction;
//             // Recurse
//             if (find_path(maze, height, width, newRow, newCol, finalRow, finalCol, path + 1, end)) {
//                 return true;
//             }
//             // Undo the move if it did not lead to a solution
//             maze[newRow][newCol] = ' ';
//             *path = '\0'; // This step is crucial for backtracking
//         }
//     }

//     // If none of the moves lead to a solution, return false to backtrack
//     return false;
// }

// char * find_path(char ** maze, int height, int width, char start, char end){
//   // char path[512] = "No Solution";
//  static char path[512];
//  int currentRow;
//  int currentCol;
//  int finalRow;
//  int finalCol;

//  find_marker(start, maze, height, width, currentRow, currentCol);
//  find_marker(end, maze, height, width, finalRow, finalCol);

//  // cout << currentRow << currentCol << " " << finalRow << finalCol << endl;
//  // if no path is found
//  if (!find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path, end)) {
//    strcpy(path, "No Solution");
//  };

//   // if no path found!  
//   return path;
// }



// bool empty_square(const char * direction, char ** maze, int currentRow, int currentCol, int height, int width){
//   // Variable to hold the new position
//   int newRow = currentRow;
//   int newCol = currentCol;

//   // Update the new position based on the direction
//   if (*direction == 'N') newRow--;
//   else if (*direction == 'E') newCol++;
//   else if (*direction == 'S') newRow++;
//   else if (*direction == 'W') newCol--;

//   // Check bounds
//   if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
//     return false;
//   }

//   // Check if the new position is either empty or the goal ('X')
//   char square = maze[newRow][newCol];
//   return (square == ' ' || square == 'X');
// }


// bool find_path(char ** maze, int height, int width, int currentRow, int currentCol, int finalRow, int finalCol, char * path) {
//   // *path = 'A';
//   // *(path+1) = '\0';
//   if (currentRow == finalRow && currentCol == finalCol) {
//     cout << "we have found the path!";
//     *path = '\0';
//     return true;
//   }

//   print_maze(maze, height, width);
  
//   // check every direction to see if it is a wall or a #?
//   // if(!(empty_square("N", maze, currentRow, currentCol, height, width)
//   //      || empty_square("E", maze, currentRow, currentCol, height, width)
//   //      || empty_square("S", maze, currentRow, currentCol, height, width)
//   //      || empty_square("W", maze,currentRow, currentCol, height, width)
//   //      )){
//   if (!find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path)) {
//   cout << "need to backtrace" << endl;
//        // remove the last move and move the pointer back for a different direction
       
//        path--;
//        *path = '\0';
//        // remove the #
//        maze[currentRow][currentCol] = ' ';
//        return false;
//     }

//   // find an empty square bool and returns a 
//   // try south
//   if (empty_square("S", maze, currentRow, currentCol, height, width)){
//     make_move(maze, ++currentRow, currentCol);
//     *path = 'S';
//     path++;
//     if (find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path)){
//       return true;
//     }
//   }
//   // try east
// if (empty_square("E", maze,currentRow, currentCol, height, width)){
//   make_move(maze, currentRow, ++currentCol);
//   *path = 'E';
//   path++;
//   if(find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path)){
//     return true;
//   }
//  }

//    // try north
//   if (empty_square("N", maze, currentRow, currentCol, height, width)){
//     make_move(maze, --currentRow, currentCol);
//     *path = 'N';
//     path++;
//     if (find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path)){
//       return true;
//     }
//   }

//   // try west
//  if (empty_square("W", maze, currentRow, currentCol, height, width)){
//    make_move(maze, currentRow, --currentCol);
//    *path = 'W';
//     path++;
//    if(find_path(maze, height, width, currentRow, currentCol, finalRow, finalCol, path)){
//      return true;
//    }
//   } 
  
//   return false;
// }