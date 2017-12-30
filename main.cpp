#include "MD5.h"
#include "PwGenerator.h"
#include "HMAC.h"


int main()
{
    bool encryptMessage = true;

    while (encryptMessage) {

        system("CLS");
        fflush(stdin);
        int length = 0;
        printf("Please enter the size of your message: ");
        scanf("%d", &length);
        printf("\nYour message: ");
        unsigned char* input = (unsigned char*)malloc(length*sizeof(unsigned char));
        scanf("%49s", input);

        std::string password = (char*)input;

    std::cout << password << std::endl;

        free(input);
        for (unsigned int i = 0; i< password.length(); i++)
            printf("%d ", password[i]);

        length = 0;
        printf("\nPlease enter the size of your key: ");
        scanf("%d", &length);

        char* keyInput = (char*)malloc(length*sizeof(char));
        scanf("%49s", keyInput);

        std::string key = keyInput;

        free(keyInput);

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
