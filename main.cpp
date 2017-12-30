#include "MD5.h"
#include "PwGenerator.h"
#include "HMAC.h"


int main()
{
    bool encryptMessage = true;

    while (encryptMessage) {

        system("CLS");
        fflush(stdin);

        printf("Your message (only ASCII characters): ");

        std::string password;

        // Put in comment this line if you want to use UTF-8 characters, and uncomment the line 23
        std::getline(std::cin, password);

        // Put between the "" you message with UTF-8 chars
        //password = "type here Your Password with UTF-8 chars (if you want to!)";

        printf("\nThe key (only ASCII characters): ");
        std::string key;
        std::getline(std::cin, key);

        char* hashedPw = MD5::encrypt(password);

        printf("Result of MD5: ");
        displayAsHex(hashedPw, 128);

        char *messageEncrypedHMAC = HMAC::encrypt(key,password);
        printf("Result of HMAC: ");
        displayAsHex(messageEncrypedHMAC, 128);

        free(hashedPw);
        free(messageEncrypedHMAC);

        bool notCorrect = true;
        char resp = 'x';
        do {

            printf("Would you like to hash a message again? (y/n)\n");
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

    printf("\t\tPART 2\n");
    generator.generatePws();
    generator.displayPws();

    system("pause");
    system("cls");
    printf("\t\tPART 2\n");
    generator.hashPasswords();
    generator.displayHashedPws();

    system("pause");
    system("cls");
    printf("\t\tPART 3\n");
    generator.saltAndHashPasswords();
    generator.displaySaltyHashedPws();

}
