#include <iostream>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char * str, char* binary) {
  // if str points to null, base case and stop
  if (*str == '\0') {
    *(binary) = '\0';
    return;
  }
  // Make character that str points to into binary
  char binary_string[9];
  // binary string now holds ascii of value
  ascii_to_binary(*str, binary_string);
  // cout << binary_string << endl;
  // make binary same as 8 digit binary string

  for (int i = 0; i < 8 ; i++) {
    *binary = binary_string[i];
    binary++;
  }
  
  // move the binary pointer along + 8
  // Assumg ascii to binary adds null terminator
  text_to_binary(str+1, binary);
  
}

void binary_to_text(char * binary, char* str) {
  // if str points to null, base case and stop
  if (*binary  == '\0') {
    *(str) = '\0';
    return;
  }
  // want only 8 characters, auto done?
  char letter =  binary_to_ascii(binary);
  
  // cout << letter << endl;
  // make binary same as 8 digit binary string
  *str = letter;
  
  // Assumg ascii to binary adds null terminator
  binary_to_text(binary+8, str+1);
  
}

int calculate_parity(char * data, int pos) {
  if (pos == 1) {
    // return d1, d2, d4
    return (data[0] + data[1] + data[3]) % 2;
  }
  else if (pos == 2){
    // return d1, d3, d4
    return (data[0] + data[2] + data[3]) % 2;
  }
  else { // pos == 3
    // return d2, d3, d4
    return (data[1] + data[2] + data[3]) % 2;
  }
}

void add_part_error(char * data, char * corrected) {
 // data = "0100"
  char cArray[3];
  int cIntArray[3];
  cIntArray[0] = calculate_parity(data, 1);
  cIntArray[1] = calculate_parity(data, 2);
  cIntArray[2] = calculate_parity(data, 3);

  // make int into a character
  for (int i = 0; i <3; i++) {
    cArray[i] = (cIntArray[i] + '0');
    // cout << "here is cArray " << cArray[i] << endl;
  }
  // cout << "now about to assign to increment" << endl;
  char error[] = {cArray[0], cArray[1], data[0], cArray[2], data[1], data[2], data[3]};
  // cout << "here is the error " << error << endl;
  for (int i = 0; i < 8; i++) {
    corrected[i] = error[i];
  }
}

void add_error_correction(char * data, char * corrected){
  if ((*data == '\0')) {
    // not sure if need  + 1
    *corrected = '\0';
    return;
  }

  // will update corrected for first 7 char
  add_part_error(data, corrected);
  // cout << "here is corrected " << corrected << endl;
  // cout << "here is data " << data << endl;
  add_error_correction(data+4,corrected+7);
    
}

int check_7_bit_parity(char * receieved, int pos){
  if (pos == 1) {
    //p1 = b4 b5 b6 b7
    return (receieved[3] - '0' + receieved[4] -'0' + receieved[5]-'0' + receieved[6] -'0') % 2;
  }
  else if (pos == 2) {
    //p2 = b2 b3 b6 b7
    return (receieved[1]-'0' + receieved[2]-'0' + receieved[5]-'0' + receieved[6] -'0') % 2;
  }
  else {
    //p3 = b1 b3 b5 b7
    return (receieved[0] -'0'+ receieved[2]-'0' + receieved[4]-'0' + receieved[6]-'0') % 2;
  }

}

void decode(char * received, char * decoded, int& count){
  if (*received == '\0') {
    *decoded = '\0';
    return ;
  }
  // cout << "current count is " << count << " and recevied is " << received << endl;
    
  int p1 = check_7_bit_parity(received, 1);
  int p2 = check_7_bit_parity(received, 2);
  int p3 = check_7_bit_parity(received, 3);

  // cout << p1 << " " << p2 << " " << p3 << endl;
  if (!(p1 == 0 && p2 == 0 && p3 == 0)) {
    cout << p1 << " " << p2 << " " << p3 << endl;
    // cout << "we have detected an error! " << endl;
    int index = (p1 * 2 * 2) + (p2 * 2) + p3 - 1;
    // flip bit
    received[index] ^= 1;
    // if error increment the count
    count++;
  }
  //cout << received << endl;
  char part_decoded[] = {received[2], received[4], received[5], received[6]};
  cout << " here " << part_decoded << endl;
  
  for (int i = 0; i < 4; i++) {
    decoded[i] = part_decoded[i];
  }

  decode(received+7, decoded+4, count);
}


int decode(char * received, char * decoded){
  int count = 0;
  decode(received, decoded, count);
  // cout << "in decode the final count is " << count << endl << endl;
  return count;
}
