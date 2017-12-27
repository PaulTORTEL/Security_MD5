#ifndef PWGENERATOR_H
#define PWGENERATOR_H

#include "Utils.h"
#include <time.h>
#include <map>
#include <sstream>

class PwGenerator
{
    private:
        int _noPws;
        std::map<std::string, std::string> _idsPws;
        std::map<std::string, char*> _idsHashedPws;

    public:
        PwGenerator();
        ~PwGenerator();

        void generatePws();
        void displayPws();

        void hashPasswords();


    private:
        std::string genRandString(const int length);
};

#endif // PWGENERATOR_H
