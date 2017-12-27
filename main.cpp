#include "operations.h"
#include "Utils.h"
#include "ArraysUtils.h"
#include <bitset>
#include <math.h>

int main()
{
    unsigned char wordA[4] = {(unsigned char)'\x67',(unsigned char)'\x45',(unsigned char)'\x23',(unsigned char)'\x01'};
    unsigned char wordB[4] = {(unsigned char)'\xef',(unsigned char)'\xcd',(unsigned char)'\xab',(unsigned char)'\x89'};
    unsigned char wordC[4] = {(unsigned char)'\x98',(unsigned char)'\xba',(unsigned char)'\xdc',(unsigned char)'\xfe'};
    unsigned char wordD[4] = {(unsigned char)'\x10',(unsigned char)'\x32',(unsigned char)'\x54',(unsigned char)'\x76'};

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

    char* blocks = newString(64);
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

    // main loop

    char *roundResult;

    char *finalRoundResult;
    char *AA = copyArray(ABit);
    char *BB = copyArray(BBit);
    char *CC = copyArray(CBit);
    char *DD = copyArray(DBit);

    char **passwordBeforeHash = passwordReadyToHash(newPassword,numberBlocks);


    for(int j = 0;j < 1/*numberBlocks*/;j++){


        // M is the segmented Message converted in bits
        //char** X = segmentMessage(newPassword, totalSize);
        char** X = segmentMessage(passwordBeforeHash[j], 64);

        for (int counter = 0; counter < 16; counter++) {

            for (int i = 0; i < 4; i++) {

                printf("%d (%c) => ", counter*4+i+1, passwordBeforeHash[j][counter*4 + i]);

                for (int j = 0; j < 8; j++)
                    printf("%d ", X[counter][(i*8)%32 + j]);

                printf("\n");
            }
        }
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


        for(int i = 0; i < 64 ; i++){

            char *firstAddition,*firstAdditionBis,*secondAddition,*finalAddition;
            int k=ArraysUtils::KValues[i];


            // on passe X[k] en little endian
            if(i < 14)
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
            printf("\n");
*/
            free(firstAddition);
            free(firstAdditionBis);
            free(secondAddition);
            free(finalAddition);

            ABit = copyArray(DBit);
            DBit = copyArray(CBit);
            CBit = copyArray(BBit);
            BBit = copyArray(finalRoundResult);

            /*displayAsHex(ABit,32);
            displayAsHex(BBit,32);
            displayAsHex(CBit,32);
            displayAsHex(DBit,32);
            system("pause");*/
        }

        ABit = AdditionBit(ABit,AA);
        BBit = AdditionBit(BBit,BB);
        CBit = AdditionBit(CBit,CC);
        DBit = AdditionBit(DBit,DD);

        displayAsHex(ABit,32);
        displayAsHex(BBit,32);
        displayAsHex(CBit,32);
        displayAsHex(DBit,32);
    }

    // TODO : corriger la fin du calcul du MD5
    char *resultA = littleEndian2Blocks(ABit);
    char *resultB = littleEndian2Blocks(BBit);
    char *resultC = littleEndian2Blocks(CBit);
    char *resultD = littleEndian2Blocks(DBit);

    char *finalMessage = appendArrays(resultA,resultB,resultC,resultD);

    displayAsHex(finalMessage,128);

    free(roundResult);
    free(finalRoundResult);

    free(resultA);
    free(resultB);
    free(resultC);
    free(resultD);

    free(ABit);
    free(BBit);
    free(CBit);
    free(DBit);


    //for (int i = 0; i < 16; i++)
       // free(X[i]);

    //free(X);
    free(newPassword);
    free(blocks);
}
