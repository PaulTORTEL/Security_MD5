#include "HMAC.h"
#include <iostream>

// performs the HMAC (Keyed-Hash Message Authentication Code) operation
char* HMAC::encrypt(std::string key,std::string message){

    // used if the key is too long to be used directly
    unsigned char* hashedKey = NULL;
    unsigned char ipad[64];
    unsigned char opad[64];

    // initialization of ipad and opad
    for(int i = 0; i < 64;i++){
        ipad[i] = '\x36';
        opad[i] = '\x5c';
    }

    if (key.length() > 64) {
        char* temp = MD5::encrypt(key);
        hashedKey = binaryToChar(temp, 128);
        free(temp);
    }

    // contains the key appended with 0 to be 64-bits long
    unsigned char *hmacKey = (unsigned char*)malloc(64 * sizeof(unsigned char));

    // if the length < 64, the md5 isn't called so the values are copied directly from the original string
    if (key.length() <= 64) {
        for(unsigned int i = 0; i < 64; i++){
            if(i < key.length())
                hmacKey[i] = key[i];
            else
                hmacKey[i] = 0;
        }
    } else {
        for(int i = 0; i < 64; i++){
            if(i < 16)
                hmacKey[i] = hashedKey[i];
            else
                hmacKey[i] = 0;
        }
    }

    char *ipadBit = charToBinary(ipad,64); // ipad contains 64 the same symbol : '6'
    char *opadBit = charToBinary(opad,64); // opad contains 64 the same symbol : '\'
    char *hmacKeyBit = charToBinary(hmacKey,64); // the key is contained as 512 char representing 512 bits
    unsigned char *tempMessage = conversionStringChar(message);
    char *messageBit = HMAC::charToBinary(tempMessage,message.length()); // the message is contained as char representing bits

    // FIRST STEP OF THE HMAC PROCESS

    // 512 is the size of the XOR word, which is always 512 bits; the length of the message depends on the user
    int lengthAfterConcat = 512 + message.length()*8;
    char *XOR = XOR64Bit(ipadBit,hmacKeyBit);
    char *Concatenation = concatenation(XOR,512,messageBit,message.length()*8);
    unsigned char *wordBeforeHash = binaryToChar(Concatenation,lengthAfterConcat);
    char* hashedMessage = MD5::encrypt(fromCharToString(wordBeforeHash,lengthAfterConcat/8));

    free(XOR);
    free(Concatenation);
    free(wordBeforeHash);

    // SECOND STEP OF THE HMAC PROCESS

    // 512 is the size of the XOR word, which is always 512 bits; the hashed message is always 128-bits long
    lengthAfterConcat = 512 + 128;
    XOR = XOR64Bit(opadBit,hmacKeyBit);
    Concatenation = concatenation(XOR,512,hashedMessage,128);
    wordBeforeHash = binaryToChar(Concatenation,lengthAfterConcat);

    free(hashedKey);
    free(hmacKey);
    free(ipadBit);
    free(opadBit);
    free(hmacKeyBit);
    free(messageBit);
    free(tempMessage);

    char *finalWord = MD5::encrypt(fromCharToString(wordBeforeHash,lengthAfterConcat/8));

    free(XOR);
    free(Concatenation);
    free(wordBeforeHash);

    return finalWord;
}

// converts the char table to a string
char *HMAC::charToBinary(unsigned char *word,int length){

    char *result = newString(length*8);

    //calculates for each char its value in binary
    for(int i = 0; i < length ; i++){
        int temp = word[i];
        for(int j = 7 ; j >= 0 ; j--){
            result[i*8 + j] = temp%2;
            temp /= 2;
        }
    }
    return result;
}

// converts a string to an unsigned char table
unsigned char* HMAC::conversionStringChar(std::string word){

    unsigned char *result = (unsigned char*)malloc(word.length() * sizeof(unsigned char));

    for(unsigned int i = 0; i < word.length(); i++)
        result[i] = word[i];

    return result;
}

// performs a XOR calculation between 2 tables of 512 bits
char *HMAC::XOR64Bit(char *word,char *key){

    char *result = newString(512);

    // the 'modulo 2' operation gives the same result as a XOR
    for(int i = 0; i < 512; i++)
        result[i] = (word[i] + key[i])%2;

    return result;
}

// concatenates 2 tables with the second being appended to the first one
char *HMAC::concatenation(char* word,int wordLength,char *message,int messageLength){

    // length is the size of the new table
    int length = wordLength+messageLength;
    char *result = newString(length); //512*2

    // if the counter is still smaller than the length of the first table, its value is in this table
    for(int i = 0; i <length;i++){
        if(i < wordLength)
            result[i] = word[i];
        else
            result[i] = message[i-wordLength];
    }

    return result;
}

// calculates y^x
int HMAC::puissance(int x,int y){
    int temp = y;
    int cpt = 1;

    // y^0 = 1 whatever the value of x is
    if(x == 0)
        return 1;
    // y^1 is obviously always equals to y
    else if(x == 1)
        return y;
    // calculates the value of y^x
    else{
        while(cpt != x){
            temp *=y;
            cpt++;
        }
    }
    return temp;
}

// converts a bit table into its representation with bits
// the new table contains only 1 value to represent 8 from the first table
// the first table contains only 0 and 1; the new table contains values between 0 and 255
unsigned char *HMAC::binaryToChar(char *message,int length){

    // the new length is 8 times smaller because we converts from bits to bytes
    int byteLength = length/8;
    unsigned char *result = (unsigned char*) malloc(byteLength*sizeof(unsigned char));

    for(int i = 0; i < byteLength;i++){
        int temp = 0;

        // calculates the decimal value for a block of 8 bits
        for(int j = 0; j < 8; j++)
            temp += (message[i*8+j]%2)*puissance(7-j,2);

        result[i] = temp;
    }

    return result;
}

// converts a char table to a string
std::string HMAC::fromCharToString(unsigned char *message,int length){

    std::string s;
    for(int i = 0 ; i < length ; i++){
        s += message[i];
    }
    return s;
}
