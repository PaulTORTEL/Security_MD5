#include "operations.h"
#include "Utils.h"
#include <bitset>

char* newString(int length) {
    return (char*)malloc(length * (sizeof(char)));
}

char* And(char X[4], char Y[4]) {

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
}
