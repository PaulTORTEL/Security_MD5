#include <iostream>
#include <bitset>
#include <stdlib.h>

using namespace std;

int emptyString(string str){
    int passwordSize = str.length();
    int blocks = ((passwordSize + 8)/64) + 1;
    cout << "size : " << passwordSize << " | blocks : " << blocks << endl;


    int emptySize = passwordSize%64;
    int emptySizeBits = emptySize * 8;
    cout << "Size : " << emptySize << " octets | "<< emptySizeBits << " bits" << endl;

    int sizeToFull = 56 - emptySize;
    int sizeToFullBits = sizeToFull * 8;
    cout << "Size to full : " << sizeToFull << " octets| " << sizeToFullBits << " bits" <<endl;

    if(sizeToFull <= 0 && sizeToFull > -8){
        sizeToFull = 56 + sizeToFull;
        sizeToFull += 8; /* Si on est obligé d'avoir un bloc en plus, par exemple si la taille du password est de 61 octets*/
    }
    sizeToFull = sizeToFull + 8; /* On a besoin de rajouter 8 octets pour arriver aux 64 */

    return sizeToFull;
}

int main()
{
    string password = "01234567890123456789012345678901234567890123456789012345";

    int passwordSize = password.length();
    int sizeToFull = emptyString(password);
    int totalSize = passwordSize + sizeToFull;

    cout << "Bytes missing : " << sizeToFull << endl;
    cout << "New string length : " << totalSize << endl;

    char* newPassword = (char*) malloc(totalSize * sizeof(char));
    for(int i = 0;i<totalSize;i++){
        if(i < passwordSize)
            newPassword[i] = password[i];
        else if (i==passwordSize)
            newPassword[i] = '\x80';
        else if ((totalSize - i <= 8))
            newPassword[i] = 'A';
        else
            newPassword[i] = '\x00';
    }



    for (int i = 0; i < totalSize; i++)
    {
        cout << i << " => " << bitset<8>(newPassword[i]) << endl;
    }

    free(newPassword);
}
