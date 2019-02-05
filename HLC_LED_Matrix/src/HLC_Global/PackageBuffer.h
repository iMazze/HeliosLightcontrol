#include "WirelessConnection.h"

class PackageBuffer
{
private:
    // Declaration
    Package myArray[20];

    uint16_t numberOfElements = 0;
public:
    PackageBuffer();
    ~PackageBuffer();

    void addPackage(Package p);
    Package returnFirstPackage();
    boolean hasPackages();

    



};