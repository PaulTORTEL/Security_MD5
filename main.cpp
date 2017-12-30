/*#include "operations.h"
#include "Utils.h"
#include "ArraysUtils.h"
#include <bitset>
#include <math.h>*/
#include "MD5.h"
#include "PwGenerator.h"

#include "HMAC.h"


int main()
{
/*
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    //generator.displayPws();
    generator.hashPasswords();*/
/*
    std::string password = "49003\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\d▒ DÕ▓`v-☻@┼▬jÏ";
    char* hashedPw = MD5::encrypt(password);

    free(hashedPw);*/

    std::string key = "azertyuiop";
    std::string message = "HELLO";

    char *messageEncrypedHMAC = HMAC::encrypt(key,message);
    //displayAsHex(messageEncrypedHMAC,128);

    free(messageEncrypedHMAC);

}
