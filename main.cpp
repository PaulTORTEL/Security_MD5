#include "MD5.h"
#include "PwGenerator.h"
#include "HMAC.h"


int main()
{
    bool encryptMessage = true;

    while (encryptMessage) {

        system("CLS");
        fflush(stdin);

        printf("\t\t==== MD5 & H-MAC IMPLEMENTATIONS ====\n");
        printf("\t\t   Matthieu PILAUDEAU & Paul TORTEL\n\n");

        printf("Hashing of a message (MD5, H-MAC)\n\n");
        printf("Your message (only ASCII characters): ");

        std::string password;

        // Put in comment this line if you want to use UTF-8 characters, and uncomment the line 23
        std::getline(std::cin, password);

        // Put between the "" your message with UTF-8 chars
        //password = "type here Your Password with UTF-8 chars (if you want to!)";

        printf("\nThe key (only ASCII characters): ");
        std::string key;

        // Same for the key
        std::getline(std::cin, key);

        // Put between the "" your key with UTF-8 chars
        //key = "type here Your Key with UTF-8 chars (if you want to!)"

        char* hashedPw = MD5::encrypt(password);

        printf("\n");
        printf("Result of MD5: ");
        displayAsHex(hashedPw, 128);

        char *messageEncrypedHMAC = HMAC::encrypt(key,password);
        printf("Result of H-MAC: ");
        displayAsHex(messageEncrypedHMAC, 128);

        printf("\n");
        free(hashedPw);
        free(messageEncrypedHMAC);

        bool notCorrect = true;
        char resp = 'x';
        do {

            printf("Would you like to hash a message again (if not, we will hash random passwords with/without salt)? (y/n)\n");
            scanf(" %c", &resp);

            if (resp == 'y' || resp == 'n') {
                notCorrect = false;
            }

        } while (notCorrect);

        if (resp == 'n')
            encryptMessage = false;
    }

    system("CLS");
    PwGenerator generator = PwGenerator();

    printf("\t\tGENERATION AND STORAGE OF 100 random PASSWORDS\n\n");
    generator.generatePws();
    generator.displayPws();

    system("pause");
    system("cls");
    printf("\t\tHASHING OF PASSWORDS\n\n");
    generator.hashPasswords();
    generator.displayHashedPws();

    system("pause");
    system("cls");
    printf("\t\tGENERATION OF random SALT FOR EACH PASSWORDS ANS HASHING OF PASSWORDS + SALT\n\n");
    generator.saltAndHashPasswords();
    generator.displaySaltyHashedPws();

}
