#include "PwGenerator.h"
#include "MD5.h"
#include "operations.h"

PwGenerator::PwGenerator()
{
    _noPws = 100;
}

PwGenerator::~PwGenerator()
{
    std::map<std::string, char*>::iterator it;

    for (it = _idsHashedPws.begin(); it != _idsHashedPws.end(); ++it) {
        free(_idsHashedPws[it->first]);
    }
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

void PwGenerator::hashPasswords() {

    std::map<std::string, std::string>::iterator it;

    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {
        _idsHashedPws[it->first] = MD5::encrypt(it->second);
    }

    /*
    std::map<std::string, std::string>::iterator it2;

    for (it2 = _idsPws.begin(); it2 != _idsPws.end(); ++it2) {
        std::cout << it2->first << " => " << it2->second << std::endl;
        displayAsHex(_idsHashedPws[it2->first], 128);
        std::cout << std::endl << std::endl;
    }*/
}
