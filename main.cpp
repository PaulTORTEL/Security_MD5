#include "include/PwGenerator.h"
#include "include/Utils.h"

#include <bitset>

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

int main()
{
/*
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    generator.displayPws();*/

    std::string password = "0123456789";
    int bytesMissing = padding(password.length());
    unsigned int totalSize = password.length() + 1 + 8 + bytesMissing;

    char* newPassword = (char*) malloc(totalSize * sizeof(char));

    int numberBlocks = numberOfBlocks(password.length());
    char* blocks = (char*) malloc(numberBlocks * sizeof(char));
    intToHex(numberBlocks,password.length(),blocks);

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
        }
    }

    for (unsigned int i = 0; i < totalSize; i++) {
        std::cout << i+1 << " => " << std::bitset<8>(newPassword[i]) << std::endl;
    }

    free(newPassword);
    free(blocks);

}
