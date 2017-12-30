#include "MD5.h"
#include "PwGenerator.h"
#include "HMAC.h"


int main()
{

    PwGenerator generator = PwGenerator();
    generator.generatePws();
    //generator.displayPws();
    //generator.hashPasswords();
    generator.saltAndHashPasswords();

    /*
    std::string password = "49003\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\d▒ DÕ▓`v-☻@┼▬jÏ";
    char* hashedPw = MD5::encrypt(password);

    free(hashedPw);*/

    //HMAC();

}
