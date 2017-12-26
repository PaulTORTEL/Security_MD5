#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

char* newString(int length);
int padding(int passwordLen);
int numberOfBlocks(int passwordLen);
void intToHex(int numberBlocks,int passwordLen,char* blocks);
char** segmentMessage(char* message, int length);
/*
char* F(char X[4], char Y[4], char Z[4]);
char* G(char X[4], char Y[4], char Z[4]);
char* H(char X[4], char Y[4], char Z[4]);
char* I(char X[4], char Y[4], char Z[4]);*/

char* FBit(char X[32], char Y[32], char Z[32]);
char* GBit(char X[32], char Y[32], char Z[32]);
char* HBit(char X[32], char Y[32], char Z[32]);
char* IBit(char X[32], char Y[32], char Z[32]);

char *HexToBinary(unsigned char X[4]);

#endif // OPERATIONS_H_INCLUDED
