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

    // free the maps
    for (it = _idsHashedPws.begin(); it != _idsHashedPws.end(); ++it) {
        free(it->second);
    }

    std::map<std::string, Pair>::iterator it2;

    for (it2 = _idsSaltyHashedPws.begin(); it2 != _idsSaltyHashedPws.end(); ++it2) {
        free(it2->second._hashedPassword);
    }
}

void PwGenerator::generatePws() {

    _idsPws.clear();
    srand (time(NULL));

    for (int i = 0; i < _noPws; i++) {

        // Random password size
        int pwSize = (rand() % 25) + 10; // Size from 10 to 35

        // Random password generated
        std::string password = genRandString(pwSize);

        std::stringstream s;
        s << (i+1);

        // id + number => ex: id1, id2, id3 ...
        std::string index = "id" + s.str();

        // Addition in the map
        _idsPws[index] = password;
    }
}

void PwGenerator::displayPws() {

    std::map<std::string, std::string>::iterator it;

    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {
        std::cout << it->first << " Pw => " << it->second << std::endl;
    }
}

void PwGenerator::displayHashedPws() {

    std::map<std::string, std::string>::iterator it;

    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {
        std::cout << it->first << " Pw => " << it->second << "\t\tHashed Pw => ";
        displayAsHex(_idsHashedPws[it->first], 128);
    }

    std::cout << std::endl;
}

void PwGenerator::displaySaltyHashedPws() {

    std::map<std::string, Pair>::iterator it;

    for (it = _idsSaltyHashedPws.begin(); it != _idsSaltyHashedPws.end(); ++it) {

        std::cout << it->first << " Pw => " << _idsPws[it->first] << "\tSalt => " << it->second._salt << "\t\tHashed Salty Pw => ";
        displayAsHex(it->second._hashedPassword, 128);
    }
    std::cout << std::endl;
}

std::string PwGenerator::genRandString(const int length) {

    std::string result = "";

    // All the characters that we use to generate a string
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return result;
}

void PwGenerator::saltAndHashPasswords() {

    std::map<std::string, std::string>::iterator it;

    // Go through all passwords
    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {

        Pair p;
        // Generate a salt
        p._salt = genRandString((rand() % 10) + 10); // 10-20 salt length

        // Append the password with the salt
        std::string passwordSalt = it->second + p._salt;

        // Encrypt the password + salt
        p._hashedPassword = MD5::encrypt(passwordSalt);

        // Store the result in the proper map
        _idsSaltyHashedPws[it->first] = p;
    }
}

void PwGenerator::hashPasswords() {

    std::map<std::string, std::string>::iterator it;

    // Go through all passwords
    for (it = _idsPws.begin(); it != _idsPws.end(); ++it) {
        // Encrypt the password and store the result
        _idsHashedPws[it->first] = MD5::encrypt(it->second);
    }
}
