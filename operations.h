#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

char* newString(int length);
int padding(int passwordLen);
int numberOfBlocks(int passwordLen);
void intToHex(int numberBlocks,int passwordLen,char* blocks);
char** segmentMessage(char* message, int length);
char* F(char X[4], char Y[4], char Z[4]);
char* G(char X[4], char Y[4], char Z[4]);
char* H(char X[4], char Y[4], char Z[4]);
char* I(char X[4], char Y[4], char Z[4]);

#endif // OPERATIONS_H_INCLUDED
