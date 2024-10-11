#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char *binary);

void text_to_binary(const char * str, char * binary);
void binary_to_text(char * binary, char * str);

void add_error_correction(char * data, char * corrected);

int calculate_parity(char * data, int pos);

void add_part_error(char * data, char * corrected);

int decode(char * received, char * decoded);

void decode(char * received, char * decoded, int count);

#endif
