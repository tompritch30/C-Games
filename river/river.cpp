#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

#include "river.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
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

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++) 
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else 
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}


void bubbleSort(char arr[], int size) {
  for (int i = 0; i < size -1;i++) {
    for (int j = 0; j < size -i-1; j++) {
      if (arr[j] > arr[j+1]) {
	char temp = arr[j];
	arr[j] = arr[j+1];
	arr[j+1] = temp;
      }
    }
  }
}

/* insert your functions here */
char ** make_river_scene(const char * left, const char * boat){
  char **scene = create_scene();
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 19, 19, "river.txt");

  int BOAT_LEFT[2] = {18, 19};
  int BOAT_RIGHT[2] = {18, 35};

  int boatPos[2] = {BOAT_LEFT[0], BOAT_LEFT[1]};
 
  // char total[8] = "BCCCMMM";
  char boatContainer[3] = "";
  char goal[8] = "";

  char sortedLeft[8];
  strcpy(sortedLeft, left);
  int length = strlen(sortedLeft);
  bubbleSort(sortedLeft, length);
  // cout << sortedLeft << endl; 

  int missionaryCount = 0;
  int boatCount = 0;
  int cannibalCount = 0;
  for (int i = 0; sortedLeft[i] != '\0'; i++){
    cout << i << ": " << sortedLeft[i] << endl;
    // as it is sorted
    if (sortedLeft[0] == 'B'){
      boatCount++;
      boatPos[0] = BOAT_LEFT[0];
      boatPos[1] = BOAT_LEFT[1];
      add_to_scene(scene,boatPos[0] , boatPos[1], "boat.txt");
    }
    else{
      boatPos[0] = BOAT_RIGHT[0];
      boatPos[1] = BOAT_RIGHT[1];
      add_to_scene(scene,boatPos[0] , boatPos[1], "boat.txt");
      // boat has to be on the right
    }
    if (sortedLeft[i] == 'C'){
      cannibalCount++;
      // ordered list means that it should be at indexes 1, 2, 3only
      add_to_scene(scene,10, (0 + (i-1)*5), "cannibal.txt");
    }
    if (sortedLeft[i] == 'M'){
      // ordered list == could be at index 1 --> 6
      missionaryCount++;
    }
  }

  for (int i = 0; i < missionaryCount; i++){
    add_to_scene(scene, 1, 0 +(i*5), "missionary.txt");
  }


  for (int i = 0; boat[i] != '\0'; i++){
     int boatEntity1[2] = {boatPos[0]-5, boatPos[1]+3};
      int boatEntity2[2] = {boatPos[0]-5, boatPos[1]+10};

    if (boat[i] == 'C') {
      add_to_scene(scene,boatPos[0]-5, boatPos[1] +3 + (i *7), "cannibal.txt");
      cannibalCount++;
    }
    else if (boat[i] == 'M') {
      add_to_scene(scene,boatPos[0]-5, boatPos[1] +3 + (i *7), "missionary.txt");
      missionaryCount++;
    }
   
  }

  // now add cannibals and missionaries to the right side
  for (int i = 0; i < (3-cannibalCount); i++) {
    add_to_scene(scene,10, (60 + (i-1)*5), "cannibal.txt");
  }

  for (int i = 0; i < (3-missionaryCount); i++) {
  add_to_scene(scene,1, (60 + (i-1)*5), "missionary.txt");
  }
  
  // // add entities to the boat
  // 
  // add_to_scene(scene,boatEntity2[0], boatEntity2[1], "missionary.txt");
  
  // // 10 height and 55-65 +5 = the right cannibals
  // add_to_scene(scene,10, 55, "cannibal.txt");
  // add_to_scene(scene,10, 60, "cannibal.txt");
  // add_to_scene(scene,10, 65, "cannibal.txt");
  // // 1 height for missionaries and 55-65 +5 for right
  // add_to_scene(scene, 1, 55, "missionary.txt");
  // add_to_scene(scene, 1, 60, "missionary.txt");
  // add_to_scene(scene, 1, 65, "missionary.txt");

  // // 10 height and 55-65 +5 = the right cannibals
  // add_to_scene(scene,10, 0, "cannibal.txt");
  // add_to_scene(scene,10, 5, "cannibal.txt");
  // add_to_scene(scene,10, 10, "cannibal.txt");
  // // 1 height for missionaries and 55-65 +5 for right
  
  // add_to_scene(scene, 1, 5, "missionary.txt");
  // add_to_scene(scene, 1, 10, "missionary.txt");
  
  //add_to_scene(scene, 8, 30, "missionary.txt");
  //add_to_scene(scene, 12, 20, "pot.txt");
  return scene;
}

int perform_crossing(char * left, const char * targets) {
  // should be able to crossings left and right
  // assumes only allowed moves?

  // loading the boat
  // crossing the river
  // unloading the boat

  // edit left string to remove the targets
  // call create scene with new left and tragets as boat
  // call create scene with same again but boat not in left but still have boat parameter
  // call create scene with new left, and empty boat.

  int boatCount = 0;
  int missionaryCount = 0;
  int cannibalCount = 0;

  cout << "here is the original  Left! ";
  for (int i = 0; left[i] != '\0'; i++) {
    cout << left[i];
  }
  cout << endl << endl;

  for(int i =0 ; left[i] != '\0'; i++){
    if (left[i] == 'B') {
      // cout << "we have a boat on the left!" << endl;
      boatCount++;
    }
    else if (left[i] == 'M') {
      missionaryCount++;
    }
    else if (left[i] == 'C') {
      cannibalCount++;
    }
  }

  for(int i =0 ; targets[i] != '\0'; i++){
    if (targets[i] == 'M') {
      missionaryCount--;
    }
    else if (targets[i] == 'C') {
      cannibalCount--;
    }
  }

  char newLeft[8] = "";
  for (int i = 0; i < cannibalCount; i++) {
    strcat(newLeft, "C");
  }
  for (int i = 0; i < missionaryCount; i++) {
    strcat(newLeft, "M");
  }
  for (int i = 0; i < boatCount; i++) {
    strcat(newLeft, "B");
  }


  cout << "here is the Left! ";
  for (int i = 0; newLeft[i] != '\0'; i++) {
    cout << newLeft[i];
  }
  cout << endl << endl;

  cout << "Loading onto the boat" << endl;
  
  char **scene = make_river_scene(newLeft, targets);
  print_scene(scene);

  cout << "boat moves" << endl;
  // int length = strlen(newLeft);
  // newLeft[length-1] = '\0';
  //char movingLeft[8];
  int leftLength = strlen(newLeft);
  if (boatCount == 1){
    newLeft[leftLength -1] = '\0';			   
    // remove B from the left string
  }
  else {
    newLeft[leftLength -1] = 'B';
    newLeft[leftLength] = '\0';
    // add B to the right string
  }
  scene = make_river_scene(newLeft, targets);
  print_scene(scene);

  cout << "here is the Left! ";
  for (int i = 0; newLeft[i] != '\0'; i++) {
    cout << newLeft[i];
  }
  cout << endl << endl;


  cout << "unloading the boat" << endl;

  scene = make_river_scene(newLeft, "");
  print_scene(scene);

  // "BCCMM" "CM"

  return 1;
}


int play_game(){
  cout << "lets play the game";
  cout << "The initial state: "<< endl;
  char left[8] = "BCCCMMM";
  char **scene = make_river_scene(left,"");
  print_scene(scene);  

  char targets[3] = "";

  bool notEnd = true;
  while(notEnd){ 
  cout << "what do you want in the boat? choose 1-2, using letters M or C with no spaces";
  cin >> targets;

  // // work out the input string based on the boat
 
  perform_crossing(left, targets);
  // print_scene(scene);  
  
  // notEnd = false;
  
  }
  
  return 1;
}


 // char sortedLeft[8];
  // strcpy(sortedLeft, left);
  // int length = strlen(sortedLeft);
  // bubbleSort(sortedLeft, length);
  // // cout << sortedLeft << endl; 

  // int missionaryCount = 0;
  // int boatCount = 0;
  // int cannibalCount = 0;
  // if(sortedLeft[0] == 'B') {
  //     boatCount++;
  //   }
  // for (int i = 0 ; sortedLeft[i] != '\0'; i++) {
  //   if(sortedLeft[i] == 'M') {
  //     missionaryCount++;
  //   }
  //   else if(sortedLeft[i] == 'C') {
  //     cannibalCount++;
  //   }
  // }

  // for(int i =0 ; targets[i] != '\0'; i++){
  //   if (targets[i] == 'M') {
  //     missionaryCount--;
  //   }
  //   else if (targets[i] == 'C') {
  //     cannibalCount--;
  //   }
  // }
  
  // char newLeft[8] = "";
  // for (int i = 0; i < cannibalCount; i++) {
  //   strcat(newLeft, "C");
  // }
  // for (int i = 0; i < missionaryCount; i++) {
  //   strcat(newLeft, "M");
  // }
  // for (int i = 0; i < boatCount; i++) {
  //   strcat(newLeft, "B");
  // }
