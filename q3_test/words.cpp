#include"words.h"
#include<cstring>
#include<iostream>

using namespace std;

void reverse(const char * input, char * output){
  int length = strlen(input);
  for (int i = length - 1; i >= 0; i--) {
    *output = input[i];
    output++;
  }

}

int compare(const char * string1, const char * string2) {
  
  // If either is at the end of the string
  if (*string1 == '\0' || *string2 == '\0'){
    // They are both at the end of the string
    if (*string1 == '\0' && *string2 == '\0'){
      // true
      return 1;
    } else {
      return 0;
    }
  }

  // Skip cases that are punctuation
  if (!isalpha(*string1)) {
    while (!isalpha(*string1)) {
	string1++;
      }
  }

  if (!isalpha(*string2)) {
    while (!isalpha(*string2)) {
	string2++;
      }
  }
  

  // if characters not the same
  if (tolower(*string1) != tolower(*string2)) {
    return 1;
  }

  // increment the pointers
  compare(++string1, ++string2);

  return 1;

}


int palindrome(const char * word) {
  int end = strlen(word) - 1;
  // floor div for odd number length
  int mid = strlen(word)/2;

  for (int i = 0; i != end ; i++){
  // Skip cases that are punctuation
  if (!isalpha(word[i])) {
    while (!isalpha(word[i])) {
	i++;
      }
  }

   if (!isalpha(word[end])) {
    while (!isalpha(word[end])) {
	end--;
      }
  }

   if (tolower(word[i]) != tolower(word[end])) {
     cout << word[i] << " i is" << i << endl; 
     cout << word[end] << " end is" << end << endl; 
     return 0;
   }
   end--;
  }
  return 1;
}
