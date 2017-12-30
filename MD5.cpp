#include "MD5.h"
#include "operations.h"
#include "ArraysUtils.h"
#include <bitset>
#include <math.h>

char* MD5::encrypt(std::string password) {

    unsigned char wordA[4] = {(unsigned char)'\x67',(unsigned char)'\x45',(unsigned char)'\x23',(unsigned char)'\x01'};
    unsigned char wordB[4] = {(unsigned char)'\xef',(unsigned char)'\xcd',(unsigned char)'\xab',(unsigned char)'\x89'};
    unsigned char wordC[4] = {(unsigned char)'\x98',(unsigned char)'\xba',(unsigned char)'\xdc',(unsigned char)'\xfe'};
    unsigned char wordD[4] = {(unsigned char)'\x10',(unsigned char)'\x32',(unsigned char)'\x54',(unsigned char)'\x76'};

    char *ABit = HexToBinary(wordA);
    char *BBit = HexToBinary(wordB);
    char *CBit = HexToBinary(wordC);
    char *DBit = HexToBinary(wordD);

    int bytesMissing = padding(password.length());
    unsigned int totalSize = password.length() + 1 + 8 + bytesMissing;

    //char* newPassword = newString(totalSize);
    unsigned char* newPassword = (unsigned char *) malloc(totalSize * sizeof(unsigned char));


    int numberBlocks = numberOfBlocks(password.length());

    // "blocks" stores the size of the message
    char* blocks = newString(8);
    int numberLinesPadding = intToHex(password.length()*8,blocks);

    for (unsigned int i = 0; i < totalSize; i++) {

        if (i < password.length())
            newPassword[i] = password[i];

        else if (i == password.length())
            newPassword[i] = '\x80';

        else if (i < (totalSize - 8))
            newPassword[i] = '\x00';

        else{
            if(i >= totalSize - numberLinesPadding)
                newPassword[i] = blocks[(totalSize-i)-1]; //Last block :newPassword[i] = blocks[0] ; i < totalSize => we need to remove 1 to totalSize-i
                                                          //or we can never reach blocks[0], because i is always smaller
            else
                newPassword[i] = '\x00';
        }
    }
for(int i = 0; i < totalSize;i++){
        printf("%d ",newPassword[i]);
    }
    system("pause");


    for (unsigned int i = 0; i < totalSize; i++) {
        std::cout << i+1 << " => " << std::bitset<8>(newPassword[i]) << std::endl;
    }

    // Sin array
    unsigned int T[64];

    for(int i = 0; i < 64;i++){

        long long x = 4294967296;

        T[i] = fabs(sin((i+1))) * x;

    }

    // main loop

    char *roundResult;

    char *finalRoundResult;
    char *AA;
    char *BB;
    char *CC;
    char *DD;

    char **passwordBeforeHash = passwordReadyToHash(newPassword,numberBlocks);

    for(int j = 0;j < numberBlocks;j++) {

        AA = copyArray(ABit);
        BB = copyArray(BBit);
        CC = copyArray(CBit);
        DD = copyArray(DBit);

        // X is the segmented Message converted in bits
        char** X = segmentMessage(passwordBeforeHash[j], 64);

        for (int counter = 0; counter < 16; counter++) {

            for (int i = 0; i < 4; i++) {

                printf("%d (%c) => ", counter*4+i+1, passwordBeforeHash[j][counter*4 + i]);

                for (int j = 0; j < 8; j++)
                    printf("%d ", X[counter][(i*8)%32 + j]);

                printf("\n");
            }
        }
        if(j == numberBlocks-1){
            char *endianConversion = newString(64);
            for(int i = 14; i< 16;i++){
                for(int j = 0; j < 32 ; j++){
                    endianConversion[(i-14)*32+j] = X[i][j];
                }
            }
            for(int i = 15; i>=14 ;i--){
                for(int j = 0; j < 32 ; j++){
                    X[i][j] = endianConversion[(15-i)*32+j];
                }
            }
        }
        /*for(int i = 0; i<16 ;i++){
            if(i < 14 || (i < 16 && numberBlocks-1>j))
                displayAsHex(littleEndian2Blocks(X[i]),32);
            else
                displayAsHex(X[i],32);
        }*/


        for(int i = 0; i < 64 ; i++) {

            char *firstAddition,*firstAdditionBis,*secondAddition,*finalAddition;
            int k=ArraysUtils::KValues[i];


            // on passe X[k] en little endian
            if((i < 14))
                X[k] = littleEndian2Blocks(X[k]);
            else if(i < 16 && (numberBlocks-1)>j)
                X[k] = littleEndian2Blocks(X[k]);

            char *sin = IntToBinary(T[i]);
            int s=ArraysUtils::SValues[i];

            if(i < 16){

                firstAdditionBis = FBit(BBit,CBit,DBit);
                firstAddition = AdditionBit(ABit,firstAdditionBis);
                secondAddition = AdditionBit(X[k],sin);
                finalAddition = AdditionBit(firstAddition,secondAddition);

                roundResult = shiftArrayByS(finalAddition,s,32);
                finalRoundResult = AdditionBit(roundResult,BBit);
            }
            else if(i < 32){

                firstAdditionBis = GBit(BBit,CBit,DBit);
                firstAddition = AdditionBit(ABit,firstAdditionBis);
                secondAddition = AdditionBit(X[k],IntToBinary(T[i]));
                finalAddition = AdditionBit(firstAddition,secondAddition);

                roundResult = shiftArrayByS(finalAddition,s,32);
                finalRoundResult = AdditionBit(roundResult,BBit);
            }
            else if(i < 48){

                firstAdditionBis = HBit(BBit,CBit,DBit);
                firstAddition = AdditionBit(ABit,firstAdditionBis);
                secondAddition = AdditionBit(X[k],IntToBinary(T[i]));
                finalAddition = AdditionBit(firstAddition,secondAddition);

                roundResult = shiftArrayByS(finalAddition,s,32);
                finalRoundResult = AdditionBit(roundResult,BBit);
            }
            else{

                firstAdditionBis = IBit(BBit,CBit,DBit);
                firstAddition = AdditionBit(ABit,firstAdditionBis);
                secondAddition = AdditionBit(X[k],IntToBinary(T[i]));
                finalAddition = AdditionBit(firstAddition,secondAddition);

                roundResult = shiftArrayByS(finalAddition,s,32);
                finalRoundResult = AdditionBit(roundResult,BBit);
            }


            /*printf("ABit => ");
            displayAsHex(ABit,32);

            printf("FF => ");
            displayAsHex(firstAdditionBis,32);

            printf("ki => ");
            displayAsHex(sin,32);

            printf("Xk => ");
            displayAsHex(X[k],32);

            printf("S => %d",s);
            printf("\n");*/

            free(firstAddition);
            free(firstAdditionBis);
            free(secondAddition);
            free(finalAddition);
            free(roundResult);

            ABit = copyArray(DBit);
            free(DBit);

            DBit = copyArray(CBit);
            free(CBit);

            CBit = copyArray(BBit);
            free(BBit);

            BBit = copyArray(finalRoundResult);
            free(finalRoundResult);

            /*displayAsHex(ABit,32);
            displayAsHex(BBit,32);
            displayAsHex(CBit,32);
            displayAsHex(DBit,32);system("pause");
            */

        }

        ABit = AdditionBit(ABit,AA);
        BBit = AdditionBit(BBit,BB);
        CBit = AdditionBit(CBit,CC);
        DBit = AdditionBit(DBit,DD);

        free(AA);
        free(BB);
        free(CC);
        free(DD);

        for (int o = 0; o < 16; o++)
            free(X[o]);

        free(X);

        /* DECALE AU DEBUT DE LA BOUCLE
        AA = copyArray(ABit);
        BB = copyArray(BBit);
        CC = copyArray(CBit);
        DD = copyArray(DBit);*/

        /*displayAsHex(ABit,32);
        displayAsHex(BBit,32);
        displayAsHex(CBit,32);
        displayAsHex(DBit,32);*/
    }

    char *resultA = littleEndian2Blocks(ABit);
    char *resultB = littleEndian2Blocks(BBit);
    char *resultC = littleEndian2Blocks(CBit);
    char *resultD = littleEndian2Blocks(DBit);

    char *hashedPassword = appendArrays(resultA,resultB,resultC,resultD);

    displayAsHex(hashedPassword,128);

    free(resultA);
    free(resultB);
    free(resultC);
    free(resultD);

    free(ABit);
    free(BBit);
    free(CBit);
    free(DBit);

    for (int i = 0; i < numberBlocks; i++)
        free(passwordBeforeHash[i]);

    free(passwordBeforeHash);
    //free(hashedPassword);


    //for (int i = 0; i < 16; i++)
       // free(X[i]);

    //free(X);
    free(newPassword);
    free(blocks);

    return hashedPassword;
}
