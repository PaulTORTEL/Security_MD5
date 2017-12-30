#ifndef PWGENERATOR_H
#define PWGENERATOR_H

#include "Utils.h"
#include <time.h>
#include <map>
#include <sstream>

class PwGenerator
{
    private:

        // Nested class in order to hide details
        class Pair {
            public:
                char* _hashedPassword;
                std::string _salt;
        };

        // Number of passwords
        int _noPws;

        // Map which stores [ID] -> [Password]
        std::map<std::string, std::string> _idsPws;

        // Map which stores [ID] -> [****HASHED PASSWORD****]
        std::map<std::string, char*> _idsHashedPws;

        // Map which stores [ID] -> Pair { [Salt] & [****HASHED PASSWORD****] }
        std::map<std::string, Pair> _idsSaltyHashedPws;

    public:
        PwGenerator();
        ~PwGenerator();

        // Generate random passwords
        void generatePws();

        // Display the password of each ID
        void displayPws();
        void displayHashedPws();
        void displaySaltyHashedPws();

        // Hash the passwords
        void hashPasswords();

        // Salt and hash the passwords
        void saltAndHashPasswords();


    private:
        // Generate a random string
        std::string genRandString(const int length);
};

#endif // PWGENERATOR_H
