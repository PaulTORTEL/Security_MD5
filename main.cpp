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

int main()
{
/*
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    generator.displayPws();*/

    std::string password = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678";
    int bytesMissing = padding(password.length());
    unsigned int totalSize = password.length() + 1 + 8 + bytesMissing;

    char* newPassword = (char*) malloc(totalSize * sizeof(char));

    for (unsigned int i = 0; i < totalSize; i++) {

        if (i < password.length())
            newPassword[i] = password[i];

        else if (i == password.length())
            newPassword[i] = '\x80';

        else if (i < (totalSize - 8))
            newPassword[i] = '\x00';

        else
            newPassword[i] = 'A';
    }

    for (unsigned int i = 0; i < totalSize; i++) {
        cout << i+1 << " => " << bitset<8>(newPassword[i]) << endl;
    }

    free(newPassword);

}
