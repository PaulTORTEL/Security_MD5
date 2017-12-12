#include "operations.h"
#include "Utils.h"
#include <bitset>
#include <math.h>

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

void intToHex(int numberBlocks,int passwordLen,char* blocks){

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
        result[i] = newString(4);

    int counter = 0;

    for (int i = 0; i < length; i++) {

        if (i != 0 && i % 4 == 0) {
            counter++;
        }

        result[counter][i%4] = message[i];

    }

    return result;
}

int main()
{
    char wordA[4] = {'\x01','\x23','\x45','\x67'};
    char wordB[4] = {'\x89','\xab','\xcd','\xef'};
    char wordC[4] = {'\xfe','\xdc','\xba','\x98'};
    char wordD[4] = {'\x76','\x54','\x32','\x10'};

/*
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    generator.displayPws();*/

    std::string password = "BONJOUR";
    int bytesMissing = padding(password.length());
    unsigned int totalSize = password.length() + 1 + 8 + bytesMissing;

    char* newPassword = newString(totalSize);

    int numberBlocks = numberOfBlocks(password.length());
    char* blocks = newString(numberBlocks);
    intToHex(numberBlocks,password.length()*8,blocks);

    for (unsigned int i = 0; i < totalSize; i++) {

        if (i < password.length())
            newPassword[i] = password[i];

        else if (i == password.length())
            newPassword[i] = '\x80';

        else if (i < (totalSize - 8))
            newPassword[i] = '\x00';

        else{
            if(i >= totalSize - numberBlocks)
                newPassword[i] = blocks[(totalSize-i)-1]; //Last block :newPassword[i] = blocks[0] ; i < totalSize => we need to remove 1 to totalSize-i
                                                          //or we can never reach blocks[0], because i is always smaller
            else
                newPassword[i] = '\x00';
        }
    }
    for (unsigned int i = 0; i < totalSize; i++) {
        std::cout << i+1 << " => " << std::bitset<8>(newPassword[i]) << std::endl;
    }

    unsigned long T[64];

    for(int i = 0; i < 64;i++){
        float temp = ((int) (i+1) * 3.14159265359)/180 ;
        float temp2 = sin(temp);
        if(temp2 < 0)
            temp2 = -(temp2);
        long long x = 4294967296;
        x = x * temp2;
        T[i] = x;
        std::cout << T[i];
        std::cout << " => " << std::bitset<32>(T[i]) << std::endl;
    }

    printf("\n\nle M :\n");
    char** M = segmentMessage(newPassword, totalSize);
    for (int i = 0; i < 16; i++) {
        printf("%d => ", i+1);
        for (int j = 0; j < 4; j++) {
            printf("%c", M[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 16; i++)
        free(M[i]);

    free(M);




    free(newPassword);
    free(blocks);
}
