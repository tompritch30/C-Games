#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include "stamp.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */

int leading_zeros(const char * digest){
  int idx = 0;
  int count = 0;

  // check for non hex characters
  while(digest[idx] != '\0') {
  if (!isxdigit(digest[idx])) {
    return -1;
  }
   idx++;
  }
  // check count for trailing zeroes
  idx = 0;
  while(digest[idx] == '0') {
     count++;
     idx++;
  } 
  
  return count;
}

bool file_to_SHA1_digest(const char * filename, char * digest){
  // #include<fstream>
  ifstream in;

  in.open(filename);
  if (!in) {
    strcpy(digest, "error");
    return false;
  }
  char line[512];
  in.getline(line, 512);
  // cout << "<" << line << ">" << endl;
  text_to_SHA1_digest(line, digest);
  
  in.close();
  
  return true;
  
}


/* 
The sender computes the SHA1 digest of the message body they wish to send.
 The sender prepares a header of the following format:
<recipient email address>:<SHA1 digest of message body>:<counter>
where counter is an integer initalised to 0. For example:
wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:0
 The sender then computes the SHA1 digest of the header. If the rst 5 hex digits (i.e. the
rst 20 bits) of the digest are zero, then this is an acceptable header. If not, the sender
increments the counter and tries the hash again4. In the example above, the rst counter
value that gives an acceptable header is 313889, since the SHA1 digest of the header
wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889
is 00000e269e4da81b701ed39646eafe17ae9aadd0.
*/

void gen_header(const char * recipient, char * digest, int count) {

}

void num_to_string(int num, char * output) {
  #include<string>
  string temp;
  temp = to_string(num);
  // cout << temp;
  // temp.copy(output, 5);
  int idx = 0;
  while (temp[idx] != '\0') {
    // cout << temp[idx] << endl;
    output[idx] = temp[idx];
    idx++;
  }
  output[idx] = '\0';
}

bool make_header(const char * recipient, const char * filename, char * header){
  
  char digest[0512];
  int count = 0;
  if (!file_to_SHA1_digest(filename, digest)){
      return false;
    }
  
  // then make into a string and compute SHA1 digest
  char header_digest[512];
  while (count < 10000000) {
  //while (count < 20) {
    strcpy(header, recipient);
    strcat(header, ":");
    strcat(header, digest);
    strcat(header, ":");
    // was getting null termination issues
    //strcat(header, count+"0");
    // strcat(header, "\0");
    // int length = strlen(header);
    char countStr[512] = "";
    num_to_string(count, countStr);
    // cout << "HEREHERHERHERH" << countStr << ">>>>>>" << endl;
    // header[length] = (char)(to_string(count));
    strcat(header, countStr);
    strcat(header, "\0");

    // cout << header << endl;
    // hash the header
    text_to_SHA1_digest(header, header_digest);
    //cout << header_digest << endl << endl;
    if (leading_zeros(header_digest) == 5) {
      // cout << "heres the count: " << count << endl;
      // finalCount = count;
      // strcpy(header, header_digest);
      return true;
    }
    count++;
  }
  
  return false;
}

/*
To validate a received email the receiver must:
 Conrm that the header is in the correct format (i.e. three elds separated by ':').
 Check the recipient mentioned in the rst eld of the header matches the expected recipient.
 Check that the SHA1 digest of the message body given in the header matches the actual
SHA1 digest of the received message.
 Check that the SHA1 digest of the header is an acceptable header.
*/

// enum MessageStatus {
//   INVALID_HEADER=-1,
//   WRONG_RECIPIENT=-2,
//   INVALID_MESSAGE_DIGEST=-3,
//   INVALID_HEADER_DIGEST=-4,
//   VALID_EMAIL=1
// };


MessageStatus check_header(const char * email, const char * header, const char * filename){
  // check valid header where three fields separated by :
  // may need more rigour to prevent ":::"
  int colonCount = 0;
  char headerEmail[512] = "";
  char headerDigest[512] = "";
  int digestIdx = 0;
  for (int i =0 ; header[i] != '\0' ; i++) {
    if (header[i] == ':') {
      colonCount++;
    }
    // get email string from header
    if (colonCount == 0) {
      headerEmail[i] = header[i];
    }
    if (header[i] != ':' && colonCount == 1) {
      headerDigest[digestIdx] = header[i];
      digestIdx++;
    }
    
  }
  // cout << "<" << headerDigest << ">"  << endl;
  if (colonCount != 2) {
    return INVALID_HEADER;
  }

  if (strcmp(email, headerEmail) != 0) {
    return WRONG_RECIPIENT;
  }

  // Check that the SHA1 digest of the message body given in the header matches the actuaSSHA1 digest of the received message.
  // use filename to generate the header and compare with current header
  char digest[512] = "";
  file_to_SHA1_digest(filename, digest);
  // cout << digest << endl;
  // cout << headerDigest << endl;
  if (strcmp(digest, headerDigest) != 0 ){
    return INVALID_MESSAGE_DIGEST;
  }

  //Check that the SHA1 digest of the header is an acceptable header.
  
  if (!make_header(email, filename, digest) || strcmp(digest, header) != 0){
    //cout << digest << ">" <<endl;
    //cout << header << endl;
    return INVALID_HEADER_DIGEST;
  }
  //
  // if (

  

  return VALID_EMAIL;
  
}
