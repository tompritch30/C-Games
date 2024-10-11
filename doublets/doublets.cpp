#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */


bool valid_step(const char * current_word, const char * next_word){
  // if both not a real word = false
  if (!(dictionary_search(current_word) && dictionary_search(next_word))) {
      return false;
    }
  int currentLength = strlen(current_word);
  int nextLength = strlen(next_word);
  if (currentLength != nextLength) {
    return false;
  }
  
  int diffCount = 0;
  for (int i = 0; i < currentLength; i++) {
    if (current_word[i] != next_word[i]) {
      diffCount++;
    }
  }
  
  return (diffCount == 1);

}

/* writes a given chain to an
output stream according to the conventions for the presentation of chains described in the Problem
Description. The input parameter chain is a NULL-terminated array of uppercase C-style strings
representing the words found at each step of the chain, while the input parameter output stream can
be any valid output stream, including cout. The function should return true if the entire chain was
successfully written to the output stream, and false otherwise
WITH start and end in upper case and inbetween it upper case*/
bool display_chain(const char ** chain, ostream &coutStream) {
  // Need to know index in char * where start and end = loop through to get count
  if (!coutStream) {
    return false;
  }
  int chainLength = 0;
  for ( ; chain[chainLength] != NULL; chainLength++) {
    // cout << chain[chainLength] << endl;
  }
  for (int i = 0; chain[i] != NULL; i++) {
    // should occur at start and end
    if (i == 0 || i == chainLength - 1) {
      for (int j = 0; chain[i][j] != '\0'; j++) {
	coutStream << static_cast<char>(toupper(chain[i][j]));
      }
      // cout << i << " HERE: " << chain[i] << endl;
    }
    else{
      for (int j = 0; chain[i][j] != '\0'; j++) {
	coutStream << static_cast<char>(tolower(chain[i][j]));
      }
      // cout << chain[i] << endl;
    }
    coutStream << endl;
    // cout << chain[chainLength] << endl;
  }
  // cout << chain
  return true;
}

/* 
bool valid_chain(const char ** chain) - NULL terminated uppercase strings*/


bool valid_chain(const char ** chain, int count, int chainLength, char * usedWords[512]){
  count++;
  // if next pos is NULL if above 2 then true = rule 1
  // to prevent deference null pointer?
  if (!(count < chainLength -1)) {
    //cout << "count: " << count << endl;
    return (count > 2);
  // return true;
  }
  // check if we have used the current word before
  int i = 0;
  while (usedWords[i] != NULL) {
    // cout << i;
    // if the word is in the used words
    if (strcmp(usedWords[i], *chain) == 0){
      return false;
    }
    i++;
  }
  //cout << "the count is " << count << endl;
  //cout << *chain << " " << *(chain+1) << endl;
  // need to keep tabs of used words, and need to prevent out of bounds
  if (valid_step(*chain, *(chain+1))) {
    // add into used words, can use count for total words added
    // cout << "bef copy<";
    // int wordIdx = 0;
    // while ((*chain)[wordIdx] != '\0') {
    //   //cout << (*chain)[wordIdx] ;
    //   cout << count << " " << wordIdx << endl;
    //   usedWords[count-1][wordIdx] = (*chain)[wordIdx]; 
    //   wordIdx++;
    // }
    usedWords[count-1] = new char[strlen(*chain)];
    strcpy(usedWords[count-1], *chain);
    //cout << ">bef call\n";
    return valid_chain(++chain, count, chainLength, usedWords);
    }
  else{
   return false;
  }
  // return false;
}

bool valid_chain(const char ** chain){
  int count = 0;
  int chainLength = 0;
  char * usedWords[512];
  
  for ( ; chain[chainLength] != NULL; chainLength++) {
    // cout << chain[chainLength] << endl;
  }
  // check 
  bool isValid = valid_chain(chain, count, chainLength, usedWords); 
  // for (int i = 0 ; i < 512; i++) {
  //   if (usedWords[i] !=  NULL){
  //     delete[] usedWords[i];
  //   }
  // }
  return isValid;
}

// recursive and on heap

bool isIn(char * target, const char ** array, int arrayLength) {
  for (int i = 0; i < arrayLength; i++) {
    if (strcmp(target, array[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool find_chain_recur(const char * start_word, const char * target_word, const char ** chain, int max_steps, int count, int wordLength){
  //return false;
  if (count > max_steps) {
    return false;
  }

  
  if (strcmp(chain[count], target_word) == 0){
      return true;
    }
  //cout << "2"<< endl;
  // try every permutation of each letter
  // at every index of the word
  for (int i = 0; i < wordLength; i++) {
    // try every letter
    for (int alphIdx = 0; alphIdx <26; alphIdx++){
      char currentChar = 'A' + alphIdx;
      // prevent the same letter from bein input??
      if (currentChar == (*chain)[i]) {
	continue;
      }
      char newWord[100] = "";
      // make the newWord
      for (int j = 0; j < wordLength; j++) {
	if (j == i ) {
	  newWord[j] = currentChar;
	}
	else{
	   newWord[j] = (*chain)[j];
	}
      }
      //cout << "3" << endl;
      // here now check if it is a word
      // if (strcmp(newWord, "BARE") == 0) {
      // 	cout << "bard!" << endl;
      // }
      if (dictionary_search(newWord) && strcmp(chain[count], newWord) != 0 && !isIn(newWord, chain, count+1) ){
	if (chain && valid_step(*chain, newWord)) {
	  // if (strcmp(newWord, "DRY") == 0) {
	  //   cout << "found it!" << endl;
	  // }
	  // cout << count << " " << newWord << endl;
	  // cout << newWord << " " << count << endl;
	  char * newMemory = new char[wordLength + 1]; 
	  // strcpy(const_cast<char*>(chain[count]), start_word);
	  strcpy(newMemory, newWord);
	  chain[++count] = newMemory;
	  if (find_chain_recur(start_word, target_word, chain, max_steps, count, wordLength)){
	    return true;
	  }
	  count--;
	  // cout << "heres the current chain element with count (post fail) " << count << "<" << chain[count] << ">" << endl;
	  // backtrace and undo the current word in chain
	  // or is this required as we can overwrite?
	}
	   
      }
      
    }
  }
  // if it is a word
  // if it is a valid step (just incase)
  // then add to chain and carry on
  // if recursive call fails, then change the char at idx back to what it was
  // if get to end of for loop at not found a word --> return false;
  // if (strcmp(chain[count], target_word) == 0){
  //   return true;
  // }

  // cout << chain[0] << endl;
  return false;
  
  
}

bool find_chain(const char * start_word, const char * target_word, const char * chain[100], int max_steps){
  int count = 0;
  int startLength = strlen(start_word);
  int targetLength = strlen(target_word);
  if (startLength != targetLength){
    return false;
  }
				 
  // ensure the starting words are the same
  char * newMemory = new char[startLength + 1]; 
  // strcpy(const_cast<char*>(chain[count]), start_word);
  strcpy(newMemory, start_word);
  chain[count] = newMemory;
  // cout << chain[count];
  
  // usedWords[count-1] = new char[strlen(*chain)];
  //   strcpy(usedWords[count-1], *chain);    
  return find_chain_recur(start_word, target_word, chain, max_steps, count, startLength);
}
