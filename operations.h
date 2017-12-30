#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

// methods preparing the message for the MD5
char *newString(int length);
int padding(int passwordLen);
int numberOfBlocks(int passwordLen);
int intToHex(int passwordLen,char* blocks);
char **passwordReadyToHash(unsigned char *newPassword,int numberBlocks);
char **segmentMessage(char* message, int length);
char *HexToBinary(unsigned char X[4]);

// methods used during the MD5 main loop
char *IntToBinary(unsigned int Ti);
char *shiftArrayByS(char* array, int s, int length);
char *AdditionBit(char X[32],char Y[32]);
char *reverseArray(char* array, int length);
char *appendArrays(char* array1,char* array2,char* array3,char* array4 );
char *copyArray(char *array2);
char *littleEndian2Blocks(char *array);

// 'display' methods for the MD5
void displayAsHex(char *table, long tabsize);
void displayBitTable(char *table, long tabsize);

// specific methods for the MD5 using the binary operations
char *FBit(char X[32], char Y[32], char Z[32]);
char *GBit(char X[32], char Y[32], char Z[32]);
char *HBit(char X[32], char Y[32], char Z[32]);
char *IBit(char X[32], char Y[32], char Z[32]);

// binary operations
char *AndBit(char X[32], char Y[32]);
char *OrBit(char X[32], char Y[32]);
char *NotBit(char X[32]);
char *XorBit(char X[32], char Y[32]);


#endif // OPERATIONS_H_INCLUDED
