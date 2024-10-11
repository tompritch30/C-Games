#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */

/*
Write an integer-valued function tile_score(tile) which returns the tile score for a given tile. Here
tile is an input parameter of character type. If tile is a letter (whether uppercase or lowercase) then
the function should return the tile score for that letter. If tile is ' ' or '?' (both of which can be used
to represent the blank tile), the function should return 0. Otherwise the function should return -1.
 */
int tile_score(const char tile){
  char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z', ' ', '?'};
  char pointsArray[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8,
    5, 1, 3, 1, 1, 3, 10, 1, 1, 1,
    1, 4, 4, 8, 4, 10, 0, 0}; 
    
  if (tile == '?' || tile == ' ') {
    return 0;
  }

  if (isalpha(tile)) {
    char lowerTile = tolower(tile);
    // cout << lowerTile;
    // alphabet = 26 + ' '+ '?' = 28
    for (int i = 0; i < 28; i++){
      if (alphabet[i] == lowerTile) {
	return pointsArray[i];
      }
    }
  }
  cout << "\n\n\n\n\n\n\n\nPANIC STATIONS!!! \n\n\n\n\n\n\n" << endl;
  return -1;
  

}

// void bubbleSort(char arr[], int size) {
//   for(int i = 0; i < size-1; i++){
//     for (int j = 0; j < size -i - 1; j++) {
//       if (arr[j] > arr[j+1]) {
// 	int temp = arr[j];
// 	arr[j] = arr[j+1];
// 	arr[j+1] = temp;
//       }
//     }
//   }
// }

// bool wordTilesRecur(char * word, char * tiles) {
//   if (*word == '\0') {
//     // Reached end of word using tiles == can make it
//     return true;
//   }
//   if (*tiles == '\0') {
//     // used all tiles and not end of word = false
//     return false;
//   }
//   // ensure dont push tiles pointer ppassed end of string
//   while (tolower(*word) != tolower(*tiles)) {
//     if (*tiles == '\0'){
//       // NEED TO CHECK THIS! 
//       return false;
//     }  
//     // as they are sorted advance until hit tile required
//     tiles++;
//   }
//   // if statement may be redunant
//   if (tolower(*word) == tolower(*tiles)) {
//     return wordTilesRecur(++word, ++tiles);
//   }
//   return false;
  
// }

// bool can_form_word_from_tiles(const char * word, const char * tiles, char * played_tiles){
//   int wordLength = strlen(word);
//   //for (int i = 0; i < wordLength; i++) {
//   //}
//   int tilesLength = strlen(tiles);
//   char sortedWord[wordLength];
//   strcpy(sortedWord, word);
//   bubbleSort(sortedWord, wordLength);
//   char sortedTiles[tilesLength];
//   strcpy(sortedTiles, tiles);
//   bubbleSort(sortedTiles, tilesLength);
//   //cout << sortedWord <<  endl;
//   //cout << sortedTiles << endl;
//   //? will be the at the start of the tiles
//   // count how many tiles are ?
//   // then want to add to sortedTiles, even combination of alphabet x times
//   int questionCount = 0;
//   for (int i = 0; i < tilesLength; i++) {
//     if (sortedTiles[i] == '?' ||sortedTiles[i] == ' '){
//       questionCount++;
//     }
//   }
  
//   char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
//     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
//     'U', 'V', 'W', 'X', 'Y', 'Z'};
//   // need a way to for loop for multiple questioCount
//   // proof of concept first assuming one question count
//   if (questionCount >0) {
//     for (int i = 0; i < 26; i++) {
//       sortedTiles[tilesLength] = alphabet[i];
//       sortedTiles[tilesLength+1] = '\0';
//       bubbleSort(sortedTiles, tilesLength+1);
//       //cout << sortedTiles << " " << sortedWord << endl;
//       if (wordTilesRecur(sortedWord,sortedTiles)) {
// 	// THIS IS WRONG, this does not add the ? but the whole word back!
// 	int count = 0;
// 	for (int idx = 0; idx < wordLength ;idx++) {
// 	  if (word[idx] == alphabet[i] && count < questionCount) {
// 	    *played_tiles = '?';
// 	    count++;
// 	  }
// 	  else {
// 	    *played_tiles = word[idx];
// 	  }
// 	  played_tiles++;
// 	}
        
// 	//strcpy(played_tiles, word);
	
// 	// enusre null termiantion
// 	strcat(played_tiles, "\0");
// 	return true;
//       }
//       // null terminate and repeat
//       // want to replace the last character with highest ascii value == z
//       bool found = false;
//       for (int idx = 0; !found ;idx++) {
// 	// cout << sortedTiles[idx] << " " << alphabet[i] << endl;
// 	if (sortedTiles[idx] == alphabet[i]) {
// 	  sortedTiles[idx] = 'z';
// 	  found = true;
// 	  // cout << "FOUND";
// 	}
// 	// if !(i < tilesLength+1){
// 	//     found = true;
// 	//   }
//       }
//       bubbleSort(sortedTiles, tilesLength+1);
//       sortedTiles[tilesLength] = '\0';
      
// 	}
//   }
  
//   if (wordTilesRecur(sortedWord,sortedTiles)) {
//     // will need a way to favour using the letters in tiles over using the ?
//     // how to include that used the ?
//     strcpy(played_tiles, word);
//     // enusre null termiantion
//     strcat(played_tiles, "\0");
//     return true;
//   }
//   strcpy(played_tiles, "\0");
  
//   return false;
// }

bool isIn(char target, char * array) {
  int length = strlen(array);
  for (int i = 0; i < length; i++) {
    if (array[i] == target ) {
      return true;
    }
  }
  return false;
}


bool can_form_word_from_tiles(const char * word, const char * tiles, char * played_tiles, bool * used, int &count){
  if (*word == '\0'){
    played_tiles[count] = '\0';
    return true;
  }
  const char * findTile = tiles;
  int idx = 0;
  // int tile_idx = 0;
  // find the position of the current char in word
  while (findTile[idx] != '\0') {
    // loop through to find if find word 
    if ((findTile[idx] == *word) && used[idx] == false){
      used[idx] = true;
      played_tiles[count] = findTile[idx];
      count++;
      return can_form_word_from_tiles(++word, tiles, played_tiles, used, count);
    }
    //findTile++;
    idx++;
    // tile_idx++;
  }

  idx = 0;
  // int tile_idx = 0;
  // find the position of the current char in word
  while (findTile[idx] != '\0') {
    // loop through to find if find word 
    if (findTile[idx] == '?' && used[idx] == false){
      used[idx] = true;
      played_tiles[count] = findTile[idx];
      count++;
      return can_form_word_from_tiles(++word, tiles, played_tiles, used, count);
    }
    // findTile++;
    idx++;
    // tile_idx++;
  } 

  return false;
}

bool can_form_word_from_tiles(const char * word, const char * tiles, char * played_tiles){
  int length = strlen(tiles);
  bool used[length];
  for (int i = 0; i < length; i++) {
    used[i] = false;
  }
  int count = 0;
  // played_tiles = "";
  return can_form_word_from_tiles(word, tiles,played_tiles, used, count);
}

//return false;


// void compute_score_recursive(const char* played_tiles, const ScoreModifier* score_modifiers, 
//                              int &score, int &wordMultiplier) {
//     if (*played_tiles == '\0') {
//         score *= wordMultiplier; // Apply the word multiplier at the base case of recursion.
//         return;
//     }

//     int letterScore = tile_score(*played_tiles);
//     if (letterScore == -1) {
//         std::cerr << "Invalid tile encountered: " << *played_tiles << std::endl;
//         return; // Skip the invalid tile or handle it as needed.
//     }

//     // Apply letter score modifiers if any.
//     switch (*score_modifiers) {
//         case DOUBLE_LETTER_SCORE:
//             letterScore *= 2;
//             break;
//         case TRIPLE_LETTER_SCORE:
//             letterScore *= 3;
//             break;
//         case DOUBLE_WORD_SCORE:
//             wordMultiplier *= 2;
//             break;
//         case TRIPLE_WORD_SCORE:
//             wordMultiplier *= 3;
//             break;
//         default:
//             break; // No modifier or NONE.
//     }

//     score += letterScore;
//     compute_score_recursive(played_tiles + 1, score_modifiers + 1, score, wordMultiplier);
// }

void compute_score(const char * played_tiles, ScoreModifier * score_modifiers, int length, int &score, int &currentMultiplier) {
  if (*played_tiles == '\0'){
    score *= currentMultiplier;
    return;
  }
  int current_tile_score = tile_score(*played_tiles);
  // cout << current_tile_score << endl;
  // for some reason adding Z as 10 doesnt work?
  switch (*score_modifiers)
    {
       case DOUBLE_LETTER_SCORE:
	  current_tile_score *= 2;
            break;
        case TRIPLE_LETTER_SCORE:
	  current_tile_score *= 3;
            break;
    case DOUBLE_WORD_SCORE:
      currentMultiplier *= 2;
      break;
      
    case TRIPLE_WORD_SCORE:
      currentMultiplier *= 3;
      break;
    default:
      break;
    }
  // if (*score_modifiers == DOUBLE_LETTER_SCORE) {
  //   //if (
  //   cout << "bt letter"
  //   current_tile_score *= 2;
  // }
  // else if (*score_modifiers == TRIPLE_LETTER_SCORE) {
  //   current_tile_score *= 3;
  // }
  // else if (*score_modifiers == DOUBLE_WORD_SCORE) {
  //   currentMultiplier *=2;
  // }
  // else if (*score_modifiers == TRIPLE_WORD_SCORE) {
  //   currentMultiplier *=3;
  // }
  // else if (*score_modifiers == NONE) {
  //   current_tile_score *=1;
  // }
  // else{
  //   cout << "\n\n\n\n BIG PROBLEM NO MODIFIER FOUND\n\n\n\n\n" << endl;
  // }
  score += current_tile_score;
  // cout << "current letter is " << *played_tiles << " and tiles score is " << current_tile_score << " score is " << score << endl;
  compute_score(++played_tiles, ++score_modifiers, length, score, currentMultiplier);
  
}

int compute_score(const char * played_tiles, ScoreModifier * score_modifiers) {
  // cout << "{NONE, TRIPLE_LETTER_SCORE, NONE, NONE, DOUBLE_WORD_SCORE, NONE, NONE};" << endl;
  int length = strlen(played_tiles);
  int currentMultiplier = 1;
  int score = 0;
  compute_score(played_tiles, score_modifiers, length, score, currentMultiplier);
  //compute_score_recursive(played_tiles, score_modifiers, score, currentMultiplier);
  if (length == 7){
    score += 50;
  }
  return score;
}

int highest_scoring_word_from_tiles(const char * tiles, ScoreModifier sm1[], char * word){
  // for every word in the dictionary
  // can_form_word_from_tiles(const char * word, const char * tiles, char * played_tiles)
  // compute score
  // if score is greater than current score, new word = wprd and update current score
  ifstream in;

  in.open("words.txt");
  char dictWord[512];
  // char played_tiles[8] = "";

  if (!in) {
    cout << "err" ;
    return -1;
  }

  int score = 0;
  int currentScore = 0;
  in >> dictWord;
  while (in) {
    char played_tiles[8] = "";
    if (can_form_word_from_tiles(dictWord, tiles, played_tiles)) {
      currentScore = compute_score(played_tiles, sm1);
      //cout << currentScore << " " << dictWord << " " << played_tiles << " " << tiles <<  endl;
      if (currentScore > score) {
	// cout << word << " with score of " << score << " is replace by " << dictWord << " with score of " << currentScore << endl;
	    strcpy(word, dictWord);
	    score = currentScore;
	  }

    }
    in >> dictWord;
  }
  
  in.close();
  return score;

}
