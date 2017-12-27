#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

char* newString(int length);
int padding(int passwordLen);
int numberOfBlocks(int passwordLen);
void intToHex(int numberBlocks,int passwordLen,char* blocks);
char** segmentMessage(char* message, int length);

char* FBit(char X[32], char Y[32], char Z[32]);
char* GBit(char X[32], char Y[32], char Z[32]);
char* HBit(char X[32], char Y[32], char Z[32]);
char* IBit(char X[32], char Y[32], char Z[32]);

char *HexToBinary(unsigned char X[4]);
char *IntToBinary(unsigned int Ti);

char* shiftArrayByS(char* array, int s, int length);

char *AdditionBit(char X[32],char Y[32]);
char *reverseArray(char* array, int length);
char *appendArrays(char* array1,char* array2,char* array3,char* array4 );
char *copyArray(char *array2);
char *littleEndian2Blocks(char *array);
void displayAsHex(char *table, long tabsize);
void displayBitTable(char *table, long tabsize);
char **passwordReadyToHash(char *newPassword,int numberBlocks);


#endif // OPERATIONS_H_INCLUDED
