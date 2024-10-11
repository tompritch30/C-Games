#include<iostream>
#include<cctype>
#include<cstring>

using namespace std;

void prepare(const char * input, char * output){
  // cout << "testing" << endl;
  int length = strlen(input);
  int output_idx = 0;
  for (int i = 0; i < length; i++) {
    if (isalnum(input[i]) && input[i] != ' '){
      char outputCh;
      outputCh = static_cast<char>(toupper(input[i]));
      output[output_idx] = outputCh;
      output_idx++;
      // cout << outputCh << endl;
    }
  }
  // the pointer is at the even point == not given a value yet
  if (output_idx %2 != 0) {
    output[output_idx] = 'X';
  }
  // ensure null termination
  output_idx++;
  output[output_idx] = '\0';
}

bool in(char character, char * used_letters, int idx = 0) {
  int length = strlen(used_letters);
  for (int i = 0; i < length; i++) {
    char letter = static_cast<char>(used_letters[i]);
    if (letter == character){
      idx = i;
      return true;
    }
  }
  return false;
}

void removeDuplicates(const char * input, char * output) {
  char used_letters[37];
  int length = strlen(input);
  int used_idx = 0;
  for (int i =0; i < length; i++) {
    char letter = static_cast<char>(input[i]);
    if (!in(letter, used_letters)) {
      // add to the used letters
      used_letters[used_idx] = letter;
      output[used_idx] = letter;
      used_idx++;
    }
    else {
      
    }
  }
  // should this be  +1?
  output[used_idx] = '\0';
}

void grid(const char * codeword, char square[6][6]) {
  // cout << "test"<< endl;
  // make string with only unique characters.
  // have string with all alphanum characters in order
  // make the string with the correct character order
  char defaultOrder[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  char codeNoDuplicates[37];
  //removeDuplicates("HELLOHELLO1231234QW78", codeNoDuplicates);
  // cout << "<" << codeNoDuplicates << ">" << endl;
  removeDuplicates(codeword, codeNoDuplicates);
  // cout << "<" << codeNoDuplicates << ">" << endl;
  int length = strlen(codeNoDuplicates);
  
  int wordIdx = 0;
  int remainingIdx = 0;
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      if (wordIdx < length) {
	// cout <<"codeNoDuplicates[wordIdx] " << codeNoDuplicates[wordIdx] << endl;
	square[row][col] = codeNoDuplicates[wordIdx];
	wordIdx++;
      }
      else {
	// if the letter is not in the codeNoDuplicates add it
	// advance while loop until find a letter that isnt used
	while(in(defaultOrder[remainingIdx], codeNoDuplicates)){ 
	    remainingIdx++;
	  }
	// cout << row << " " << col << " <current pos" << endl;
	square[row][col] = defaultOrder[remainingIdx];
	remainingIdx++;

	
	// the non used squares
      }
    }
  }  
}

int findrow(const char square[6][6], char ch){
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      if (square[row][col] == ch ){
	return row;
      }
    }
  }
  return -1;
}

int findcol(const char square[6][6], char ch){
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      if (square[row][col] == ch ){
	return col;
      }
    }
  }
  return -1;
}


void bigram(char square[6][6], const char inchar1, const char inchar2, char& outchar1, char &outchar2) {
  int inchar1row = findrow(square, inchar1); 
  int inchar1col = findcol(square, inchar1); 
  // cout << "row:" << inchar1row << " col:" << inchar1col << endl;

  int inchar2row = findrow(square, inchar2); 
  int inchar2col = findcol(square, inchar2); 
  // cout << "row:" << inchar2row << " col:" << inchar2col << endl;

  outchar1 = static_cast<char>(square[inchar1row][inchar2col]);
  outchar2 = square[inchar2row][inchar1col];
  // cout << "char1<" << outchar1 << "> and char 2//  <" << outchar2 << "> " << endl;
  //   for (int row=0; row<6; row++) {
  //   for (int col=0; col<6; col++) 
  //     cout << ((isalnum(square[row][col])) ? square[row][col] : '?') << ' ';
  //   cout << endl;
  // }
  // cout << endl;

}

void encode(char square[6][6], const char * prepared, char * encoded){
  char inchar1 = *prepared;
  if (inchar1 == '\0') {
    return;
  }
  char inchar2 = *(prepared +1);
  // cout << "input chars" << inchar1 << inchar2 << endl;

  char outchar1;
  char outchar2;
  bigram(square, inchar1, inchar2, outchar1, outchar2);
  // cout << "output chars" << outchar1 << outchar2 << endl <<endl;
  
  // cout << outchar1 << outchar2 ;
  *encoded = outchar1;
  encoded++;
  *encoded = outchar2;
  encoded++;

  encode(square, (prepared+2), encoded);
  
}

void decode(char square[6][6], const char * prepared, char * decoded){
  char inchar1 = *prepared;
  if (inchar1 == '\0') {
    return;
  }
  char inchar2 = *(prepared +1);
  // cout << "input chars" << inchar1 << inchar2 << endl;

  char outchar1;
  char outchar2;
  bigram(square, inchar1, inchar2, outchar1, outchar2);
  // cout << "output chars" << outchar1 << outchar2 << endl <<endl;
  
  // cout << outchar1 << outchar2 ;
  *decoded = outchar1;
  decoded++;
  *decoded = outchar2;
  decoded++;

  decode(square, (prepared+2), decoded);
  
}
