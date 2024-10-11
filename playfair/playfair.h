#ifndef PLAYFAIR_H
#define PLAYFAIR_H

void prepare(const char * input, char * output);


void grid( const char * codeword, char square[6][6]);

void bigram(char square[6][6], char inchar1, char inchar2, char &outchar1, char &outchar2);


void encode(char square[6][6], const char * prepared, char * encoded);

void decode(char square[6][6], const char * prepared, char * decoded);
#endif 
