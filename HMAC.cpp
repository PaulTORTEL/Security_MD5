#include "HMAC.h"
#include <iostream>

void HMAC(){

    // HMAC
    std::string key = "hello";
    std::string message = "HELLO";

    char *hmacKey = newString(64);

    for(int i = 0; i < 64; i++){
        if(i< key.length())
            hmacKey[i] = key[i];
        else
            hmacKey[i] = 0;
    }

    char ipad[64];
    char opad[64];

    for(int i = 0; i < 64;i++){
        ipad[i] = '\x36';
        opad[i] = '\x5c';
    }


    char *ipadBit = charToBinary(ipad,64); // table ipad en bit: length 512
    char *opadBit = charToBinary(opad,64); // table opad en bit: length 512

    char *hmacKeyBit = charToBinary(hmacKey,64); // key en bit: length 512

    // FIRST STEP
    char *firstXOR = XOR64Bit(ipadBit,hmacKeyBit);

    char *tempMessage = conversionStringChar(message);

    char *messageBit = charToBinary(tempMessage,message.length());
    char *firstConcatenation = concatenation(firstXOR,512,messageBit,message.length()*8);

    int concatLength = 512 + message.length()*8;
    unsigned char *finalWord = binaryToChar(firstConcatenation,concatLength);

    char* hashedMessage = MD5::encrypt(fromCharToString(finalWord,concatLength/8));

    // SECOND STEP
    char *secondXOR = XOR64Bit(opadBit,hmacKeyBit);

    char *secondConcatenation = concatenation(secondXOR,512,hashedMessage,128);

    concatLength = 512 + 128;
    unsigned char *Word = binaryToChar(secondConcatenation,concatLength);

    char* hashedFinalMessage = MD5::encrypt(fromCharToString(Word,concatLength/8));
}

char *charToBinary(char *word,int length){

    char *result = newString(length*8);

    for(int i = 0; i < length ; i++){
        int temp = word[i];
        for(int j = 7 ; j >= 0 ; j--){
            result[i*8 + j] = temp%2;
            temp /= 2;
        }
    }
    return result;
}

char* conversionStringChar(std::string word){

    char *result = newString(word.length());

    for(int i = 0; i < word.length(); i++)
        result[i] = word[i];

    return result;
}

char *XOR64Bit(char *word,char *key){

    char *result = newString(512);

    for(int i = 0; i < 512; i++)
        result[i] = (word[i] + key[i])%2;

    return result;
}

char *concatenation(char* word,int wordLength,char *message,int messageLength){

    int length = wordLength+messageLength;
    char *result = newString(length); //512*2

    for(int i = 0; i <length;i++){
        if(i < wordLength)
            result[i] = word[i];
        else
            result[i] = message[i-wordLength];
    }

    return result;
}

unsigned char *binaryToChar(char *message,int length){

    int byteLength = length/8;
    unsigned char *result = (unsigned char*) malloc(byteLength*sizeof(unsigned char));

    for(int i = 0; i < byteLength;i++){
        int temp = 0;

        for(int j = 0; j < 8; j++)
            temp += (message[i*8+j]%2)*puissance(7-j,2);

        result[i] = temp;
    }

    return result;
}

// calculate y^x
int puissance(int x,int y){
    int temp = y;
    int cpt = 1;

    if(x == 0)
        return 1;
    else if(x == 1)
        return y;
    else{
        while(cpt != x){
            temp *=y;
            cpt++;
        }
    }
    return temp;
}

std::string fromCharToString(const unsigned char *message,int length){

    std::string s;
    for(int i = 0 ; i < length ; i++){
        s += message[i];
    }
    return s;
}
