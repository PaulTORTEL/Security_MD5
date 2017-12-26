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
    int i = 1;

    // We have to know how large is the number representing the length of the password
    // So we have to calculate how many bits we need to represent it, and we work with blocs of 8 bits
    while(passwordLen > i){
        blocks++;
        i=i*256;
    }
    return blocks;
}

void intToHex(int numberBlocks,int passwordLen,char* blocks) {

    // We calculate each block, then we divide by 256 : 256 = 2^8, meaning the binary number will be pushed by 8 bits to the right
    // for example 111100000001111 / 256 = 11110000
    for(int i = 0;i<numberBlocks;i++){
        blocks[i] = passwordLen%(256);
        passwordLen = passwordLen/256;

    }
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

        for (int j = 7; j >= 0; j--) {
            result[counter][(i*8)%32 + j] = temp % 2;
            temp /= 2;
        }
    }

    return result;
}

/*char* And(char X[4], char Y[4]) {

    char* result = newString(4);

    for (unsigned int i = 0; i < 4; i++) {
        result[i] = X[i] & Y[i];
    }

    return result;
}

char* Or(char X[4], char Y[4]) {

    char* result = newString(4);

    for (unsigned int i = 0; i < 4; i++) {
        result[i] = X[i] | Y[i];
    }

    return result;
}

char* Not(char X[4]) {

    char* result = newString(4);

    for (unsigned int i = 0; i < 4; i++) {
        result[i] = ~X[i];
    }

    return result;
}

char* Xor(char X[4], char Y[4]) {

    char* result = newString(4);

    for (unsigned int i = 0; i < 4; i++) {
        result[i] = X[i] ^ Y[i];
    }

    return result;
}

char* F(char X[4], char Y[4], char Z[4]) {

    char* XY = And(X, Y);
    char* NotX = Not(X);
    char* NotXZ = And(NotX, Z);

    char* result = Or(XY, NotXZ);

    free(XY);
    free(NotX);
    free(NotXZ);

    return result;

}

char* G(char X[4], char Y[4], char Z[4]) {

    char* XZ = And(X, Z);
    char* NotZ = Not(Z);
    char* YNotZ = And(Y, NotZ);

    char* result = Or(XZ, YNotZ);

    free(XZ);
    free(NotZ);
    free(YNotZ);

    return result;
}

char* H(char X[4], char Y[4], char Z[4]) {

    char* XxorY = Xor(X, Y);
    char* result = Xor(XxorY, Z);

    free(XxorY);

    return result;
}

char* I(char X[4], char Y[4], char Z[4]) {

    char* NotZ = Not(Z);
    char* XNotZ = Or(X, NotZ);
    char* result = Xor(Y, XNotZ);

    free(NotZ);
    free(XNotZ);

    return result;
}*/

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

char* shiftArrayByS(char* array, int s, int length) {

    char* result = newString(length);

    for (int i = 0; i < length; i++)
        result[((i+s)%length)] = array[i];

    return result;
}
