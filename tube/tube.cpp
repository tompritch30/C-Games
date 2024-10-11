#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
// #include <cassert>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char ** map, int height, int width, char target, int &row, int &col){
  //for each row inthe height
  for (int irow =0 ; irow < height ; irow++){
    // for each col in the width
    for (int jcol = 0; jcol < width; jcol++) {
      if (map[irow][jcol] == target) {
	row = irow;
	col = jcol;
	return true;
      }
    }
  }
  row = -1;
  col = -1;
  return false;
}


bool find_file_target(const char * filename, const char * target, char &outputChar){
  
  char line[512];
  
  ifstream in(filename);
  if (!in){
    cerr << "file reading error " << endl;
    return false;
  }

  // 4 Oxford Circus
  in.getline(line, 512);
  while (in) {
    // to ensure only copy what we need
    // temp used to make sure that we dont get leftovers
    char temp[512];
    strcpy(temp, line);

    char symbol = temp[0];
    char name[512] = "";

    // start idx 2 to skip starting char and white space
    int idx = 2;
    while (temp[idx] != '\0') {
      name[idx-2] = temp[idx];
      idx++;
    }


    if (strcmp(target, name) == 0) {
      outputChar = symbol;
      return true;
    }
    in.getline(line, 512);
  }

  in.close();
  outputChar = ' ';
  return false;
}


char get_symbol_for_station_or_line(const char * target){
  // helpers to find symbol for station or line when opening the file
  char outputChar = ' ';
  if (find_file_target("stations.txt", target, outputChar)) {
    return outputChar;
  };

  if (find_file_target("lines.txt", target, outputChar)) {
    return outputChar;
  };

  return outputChar;
}

int validate_route(char **map, int height, int width, const char * target, const char *route, char destination[512], int &lineChangeCount, char prevLine, int prevRow, int prevCol){

  char symbol = get_symbol_for_station_or_line(target);
  // base case
  if (*route == '\0') {
    // changeCount = 0;
    if (true) { // is a station!
      cout << "\n\n\n";
      return lineChangeCount;
    }	
    return  ERROR_ROUTE_ENDPOINT_IS_NOT_STATION; //lineChangeCount;
  }
 
  

  int row = -1;
  int col = -1;
  // if the symbol is not found
  if (!get_symbol_position(map, height, width, symbol, row, col)){
    cout << "start";
    return ERROR_START_STATION_INVALID;
  }
  
  char currentDir[3] = "";
  currentDir[0] = *route;
  route++;
  // i.e. is another direction
  if (!(*route == ',')){
    currentDir[1] = *route;
    // will move route pointer to the comma
    route++;
  }
  // now on a commas either way
  // move to next stage for recusrive call
  route++;
  cout << currentDir << " ";
  Direction direction = string_to_direction(currentDir);
  if (direction == INVALID_DIRECTION) {
    cout << "invalid";
    // return ERROR_INVALID_DIRECTION;
  }

  // will this throw an error for the letter of the station?
  if (map[row][col] != symbol) {
    if (!isalnum(map[row][col])) {
      cout << "off";
	return ERROR_OFF_TRACK;
      }
    // we are at a station
    // if letter is not a station
    if (true){
      cout << "hop";
      return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
    }
    //lineChangeCount++;
    
    }
  // if (prevLine != symbol) {
    
  // }

  validate_route(map, height, width, target, route, destination, lineChangeCount, prevLine, prevRow, prevCol);

}

int validate_route(char **map, int height, int width, const char * target, const char *route, char destination[512]){
  char symbol = get_symbol_for_station_or_line(target);

  int row = -1;
  int col = -1;
  // if the symbol is not found
  if (!get_symbol_position(map, height, width, symbol, row, col)){
    return ERROR_START_STATION_INVALID;
  }
  char prevLine = symbol;

  int changeCount = 0;
  int prevRow = row;
  int prevCol = col;
  changeCount = validate_route(map, height, width, target, route, destination,changeCount, prevLine, prevRow, prevCol);
  cout << changeCount << endl;
  return 1000;
  
}

// #define ERROR_START_STATION_INVALID -1 
// #define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
// #define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
// #define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
// #define ERROR_INVALID_DIRECTION -5
// #define ERROR_OFF_TRACK -6
// #define ERROR_OUT_OF_BOUNDS -7
// enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};


  // strcpy(route, "W,W,E,W,W,W");
  // cout << "Starting at Sloane Square and taking the steps:" << endl;
  // cout << route << endl;
  // result = validate_route(map, height, width, "Sloane Square", route, destination);
  // if (result >= 0)


// int count = 0;
  // while (count < 3 || *route != '\0') {
  // dont think the string is null terminated properly?
  
  // //  while (*route != '\0'){

  // // start at 1 as 0 commas = 1 word
  //   int dirCount = 1;
  //   int length = strlen(route);
  //   for (int i = 0 ; i < length; i++) {
  //     if (route[i] == ',') {
  // 	dirCount++;
  //     }
  //   }
  //   // cout << dirCount << endl;

  //   // outside the loop to maintain the current pos
  //   int routeIdx = 0;
  //   for (int i = 0; i < dirCount; i++){

  //   char currentDir[] = "";
  //   int currentIdx = 0;
    
  //   // *route != '\0' &&
  //   while (!(route[routeIdx] == '\0' || route[routeIdx] == ',')) {
  //     // if (
  //     // 	;
  //     // }
  //     cout << "current IDx and routeIDx " << currentIdx << "|" << routeIdx << endl;
  //     currentDir[currentIdx] = route[routeIdx];
  //     routeIdx++;
  //     currentIdx++;
  //   }
  //   currentDir[currentIdx] = '\0';
  //   // to move passed the comma
  //   // SHOULD BE -1 but stack smashign ?? moving on for time
  //   if (!(i >= dirCount-1)) {
  //     routeIdx++;
  //   }
  //   cout << currentDir << endl;
  //   }
  
