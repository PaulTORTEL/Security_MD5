#include "../include/PwGenerator.h"

PwGenerator::PwGenerator()
{
    _noPws = 100;
}

PwGenerator::~PwGenerator()
{

}

void PwGenerator::generatePws() {

    _idsPws.clear();
    srand (time(NULL));

    for (int i = 0; i < _noPws; i++) {

        int pwSize = (rand() % 25) + 10; // Size from 10 to 35
        std::string password = genRandString(pwSize);

        std::stringstream s;
        s << (i+1);

        std::string index = "id" + s.str();

        _idsPws[index] = password;
    }
}

void PwGenerator::displayPws() {
    std::map<std::string, std::string>::iterator it;

    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }

}

std::string PwGenerator::genRandString(const int length) {

    std::string result = "";

    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }


    return result;
}
