#include "operations.h"
#include "Utils.h"
#include <bitset>
#include <math.h>

int main()
{
    unsigned char wordA[4] = {(unsigned char)'\x01',(unsigned char)'\x23',(unsigned char)'\x45',(unsigned char)'\x67'};
    unsigned char wordB[4] = {(unsigned char)'\x89',(unsigned char)'\xab',(unsigned char)'\xcd',(unsigned char)'\xef'};
    unsigned char wordC[4] = {(unsigned char)'\xfe',(unsigned char)'\xdc',(unsigned char)'\xba',(unsigned char)'\x98'};
    unsigned char wordD[4] = {(unsigned char)'\x76',(unsigned char)'\x54',(unsigned char)'\x32',(unsigned char)'\x10'};

    char *ABit = HexToBinary(wordA);
    char *BBit = HexToBinary(wordB);
    char *CBit = HexToBinary(wordC);
    char *DBit = HexToBinary(wordD);

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

    // Sin array
    unsigned int T[64];

    for(int i = 0; i < 64;i++){
        /*float temp = ((int) (i+1) * 3.14159265359)/180 ;
        float temp2 = sin((i+1));
        if(temp2 < 0)
            temp2 = fabs(temp2 * x);

        x = x * temp2;
        T[i] = x;*/

        long long x = 4294967296;

        T[i] = fabs(sin((i+1))) * x;

        //printf("0x%x", T[i]);
        std::cout << T[i];
        std::cout << " => " << std::bitset<32>(T[i]) << std::endl;
    }

    printf("\n\nle M :\n");

    // M is the segmented Message converted in bits
    char** M = segmentMessage(newPassword, totalSize);

    for (int counter = 0; counter < 16; counter++) {

        for (int i = 0; i < 4; i++) {

            printf("%d (%c) => ", counter*4+i+1, newPassword[counter*4 + i]);

            for (int j = 0; j < 8; j++)
                printf("%d ", M[counter][(i*8)%32 + j]);

            printf("\n");
        }
    }

    // main loop
    // ne marche absolument pas pour le moment

    /*char* f;

    for(int i = 0; i < 16 ; i++){
        if(i < 16){
            f = FBit(BBit,CBit,DBit);
            for(int i = 0; i < 32;i++){
                printf("%d",f[i]);
                if((i+1)%4 == 0)
                    printf(" ");
            }
            printf("\n");

        }

    }*/
/*
    for (int i = 0; i < 32; i++) {
        printf("%d ", M[0][i]);
    }
    printf("\nappres : \n");
    char* test = shiftArrayByS(M[0], 2, 32);
    for (int i = 0; i < 32; i++) {
        printf("%d ", test[i]);
    }

    free(test);
*/

    for (int i = 0; i < 16; i++)
        free(M[i]);

    free(M);

    free(newPassword);
    free(blocks);
}
