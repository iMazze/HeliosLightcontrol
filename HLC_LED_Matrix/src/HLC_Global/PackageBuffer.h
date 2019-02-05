#include "WirelessConnection.h"

class PackageBuffer
{

private:
    // Declaration
    Package* myArray = 0;
    uint16_t lastIndex = 0;
public:
    PackageBuffer();
    ~PackageBuffer();

    void addPackage(Package p);
    Package returnFirstPackage();

};