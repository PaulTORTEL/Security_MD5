#include "MD5.h"
#include "PwGenerator.h"
#include "HMAC.h"


int main()
{
/*
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    generator.displayPws();
    generator.hashPasswords();
    generator.saltAndHashPasswords();
*/

    std::string password = "hello";
    char* hashedPw = MD5::encrypt(password);
    system("pause");

    free(hashedPw);

    std::string key = "azertyuiop";
    std::string message = "HELLO";

    char *messageEncrypedHMAC = HMAC::encrypt(key,message);
    //displayAsHex(messageEncrypedHMAC,128);

    free(messageEncrypedHMAC);
}
