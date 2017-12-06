#include "include/PwGenerator.h"
#include "include/Utils.h"

using namespace std;

int main()
{
    PwGenerator generator = PwGenerator();
    generator.generatePws();
    generator.displayPws();
    return 0;
}
