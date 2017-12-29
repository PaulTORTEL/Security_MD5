#include "operations.h"
#include "Utils.h"
#include <bitset>

char* newString(int length) {
    return (char*)malloc(length * (sizeof(char)));
}


int padding(int passwordLen) {

    // Empty space for the last block
    int emptySpace = 64 - (((passwordLen + 1) % 64) + 8);

    // Empty space can be negative if passwordLen+1 % 64 is close to 64 but still < 64.
    // So adding +8 (size of the password in bytes) and we go over 64.
    // We just need to calculate the empty space in the previous block + new block of 64 bytes which is 64 - 8 (size) = 56
    if (emptySpace < 0)
        emptySpace = (64 - ((passwordLen + 1) % 64)) + 56;

    return emptySpace;

}

int numberOfBlocks(int passwordLen){

    int blocks = 0;
    int i = 0;

    // We have to know how large is the number representing the length of the password
    // So we have to calculate how many bits we need to represent it, and we work with blocs of 8 bits
    // + 9 lines => size + 1 line with "1", in case it doesn't fit, then the no blocks is higher
    while(passwordLen + 9 > i){
        blocks++;
        i+=64;
    }
    return blocks;
}

int intToHex(int passwordLen,char* blocks) {

    // We calculate each block, then we divide by 256 : 256 = 2^8, meaning the binary number will be pushed by 8 bits to the right
    // for example 111100000001111 / 256 = 11110000
    int i = 0;
    while(passwordLen > 0){
        printf("%d ",passwordLen);
        blocks[i] = passwordLen%(256);
        passwordLen /= 256;
        i++;
    }
    return i;
}

char** segmentMessage(char* message, int length) {

    char **result = (char**) malloc(16 * sizeof(char*));
    for (int i = 0; i < 16; i++)
        result[i] = newString(32);

    int counter = 0;

    for (int i = 0; i < length; i++) {

        if (i != 0 && i % 4 == 0) {
            counter++;
        }

        unsigned char temp = message[i];

        for (int j = 7; j >=0; j--) {
            result[counter][(i*8)%32 + j] = temp % 2;
            temp /= 2;
        }
    }

    return result;
}

// AND Operation when we work with a char representing a bit
char* AndBit(char X[32], char Y[32]) {

    char* result = newString(32);

    for (unsigned int i = 0; i < 32; i++) {
        result[i] = X[i] & Y[i];
    }

    return result;
}

// OR Operation when we work with a char representing a bit
char* OrBit(char X[32], char Y[32]) {

    char* result = newString(32);

    for (unsigned int i = 0; i < 32; i++) {
        result[i] = X[i] | Y[i];
    }

    return result;
}

// NOT Operation when we work with a char representing a bit
char* NotBit(char X[32]) {

    char* result = newString(32);

    for (unsigned int i = 0; i < 32; i++) {
        result[i] = (X[i]+1)%2;
    }

    return result;
}

// XOR Operation when we work with a char representing a bit
char* XorBit(char X[32], char Y[32]) {

    char* result = newString(32);

    for (unsigned int i = 0; i < 32; i++) {
        result[i] = X[i] ^ Y[i];
    }

    return result;
}

// F method
char* FBit(char X[32], char Y[32], char Z[32]) {

    char* XY = AndBit(X, Y);
    char* NotX = NotBit(X);
    char* NotXZ = AndBit(NotX, Z);

    char* result = OrBit(XY, NotXZ);

    free(XY);
    free(NotX);
    free(NotXZ);

    return result;
}

// G method
char* GBit(char X[32], char Y[32], char Z[32]) {

    char* XZ = AndBit(X, Z);
    char* NotZ = NotBit(Z);
    char* YNotZ = AndBit(Y, NotZ);

    char* result = OrBit(XZ, YNotZ);

    free(XZ);
    free(NotZ);
    free(YNotZ);

    return result;
}

// H method
char* HBit(char X[32], char Y[32], char Z[32]) {

    char* XxorY = XorBit(X, Y);
    char* result = XorBit(XxorY, Z);

    free(XxorY);

    return result;
}

// I method
char* IBit(char X[32], char Y[32], char Z[32]) {

    char* NotZ = NotBit(Z);
    char* XNotZ = OrBit(X, NotZ);
    char* result = XorBit(Y, XNotZ);

    free(NotZ);
    free(XNotZ);

    return result;
}

char *HexToBinary(unsigned char X[4]){

    char *result = newString(32);
    for(int i = 0; i<4;i++){
        int temp = X[i];
        for(int j = 7; j>=0;j--){
            result[i*8 + j] = temp%2;
            temp /= 2;
        }
    }
    return result;
}

char *IntToBinary(unsigned int Ti){

    char *result = newString(32);
    unsigned int temp = Ti;
    for(int i = 31; i>=0;i--){
        result[i] = temp%2;
        temp /= 2;
    }
    return result;
}

char* shiftArrayByS(char* array, int s, int length) {

    char* result = newString(length);

    /*for (int i = 0; i < length; i++)
        result[((i+s)%length)] = array[i];*/

    for (int i = 0; i < length; i++){
        if((i-s) < 0)
            result[(length)+(i-s)] = array[i];
        else
            result[i-s] = array[i];
    }

    return result;
}

char *AdditionBit(char X[32],char Y[32]){

    char *result = newString(32);
    int addionalValue = 0; // retenue in french

    for(int i = 31;i>=0;i--){
        int resultAddition = X[i] + Y[i] + addionalValue;
        result[i] = resultAddition%2;
        if(resultAddition>1)
            addionalValue = 1;
        else
            addionalValue = 0;
    }
    return result;
}

char *reverseArray(char* array, int length) {

    char* result = newString(length);

    for (int i = 0; i < length; i++)
        result[i] = array[(length-i)-1];

    return result;
}

char *appendArrays(char* array1,char* array2,char* array3,char* array4 ) {

    char* result = newString(128);

    for (int i = 0; i < 128; i++){
        if(i < 32)
            result[i] = array1[i];
        else if (i < 64)
            result[i] = array2[i%32];
        else if (i < 96)
            result[i] = array3[i%32];
        else
            result[i] = array4[i%32];
    }

    return result;
}

char *copyArray(char *array2){

    char *result = newString(32);
    for(int i = 0; i < 32; i++){
        result[i] = array2[i];
    }

    return result;
}

char *littleEndian2Blocks(char *array){
    char *result = newString(32);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            result[i*8+j] = array[32-((i+1)*8)+j];
        }
    }

    return result;
}

void displayAsHex(char *table, long tabsize)
{
   long hexsize = tabsize/4;

   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i=0; i < hexsize;i++)
   {
       long value=0;

       for(long j=0; j <4; j++)
       {
            value = (2*value)+table[4*i+j];
       }

       std::cout << hexcodes[value];

        if(((i+1)%4)==0)
        {
            std::cout << " ";
        }
   }

   std::cout << std::endl;
}

void displayBitTable(char *table, long tabsize)
{
    for(long i=0; i < tabsize;i++)
    {
        std::cout << (int)table[i];

        if(((i+1)%4)==0)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

char **passwordReadyToHash(char *newPassword,int numberBlocks){


    char **result = (char**) malloc(numberBlocks * sizeof(char*));
    for(int i = 0; i < numberBlocks;i++){
        result[i] = newString(64);

        for(int j = 0; j < 64; j++){
            result[i][j] = newPassword[i*64 + j];
        }
    }
    return result;
}
