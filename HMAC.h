#ifndef HMAC_H
#define HMAC_H

#include "MD5.h"
#include "operations.h"

class HMAC
{
    public:
        // performs the HMAC (Keyed-Hash Message Authentication Code) operation
        static char* encrypt(std::string key,std::string message);

    private:
        // convert the char table to a string
        static char *charToBinary(unsigned char *word,int length);

        // converts a string to an unsigned char table
        static unsigned char* conversionStringChar(std::string word);

        // performs a XOR calculation between 2 tables of 512 bits
        static char *XOR64Bit(char *word,char *key);

        // concatenates 2 tables with the second being appended to the first one
        static char *concatenation(char* word,int wordLength,char *key,int keyLength);

        // calculates y^x
        static int puissance(int x,int y);

        // converts a bit table into its representation with bits
        static unsigned char *binaryToChar(char *message,int length);

        // converts a char table to a string
        static std::string fromCharToString(unsigned char *message,int length);
};

#endif // HMAC_H
