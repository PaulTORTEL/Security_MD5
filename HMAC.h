#ifndef HMAC_H
#define HMAC_H

#include "Utils.h"
#include "MD5.h"
#include "operations.h"

void HMAC();
char *charToBinary(unsigned char *word,int length);
unsigned char* conversionStringChar(std::string word);
char *XOR64Bit(char *word,char *key);
char *concatenation(char* word,int wordLength,char *key,int keyLength);
unsigned char *binaryToChar(char *message,int length);
int puissance(int x,int y);
std::string fromCharToString(unsigned char *message,int length);

#endif // HMAC_H
