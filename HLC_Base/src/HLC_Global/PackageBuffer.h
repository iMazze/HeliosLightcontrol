/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
#include "WirelessConnection.h"

class PackageBuffer
{
private:
    // Declaration
    Package myArray[20];

    uint16_t numberOfElements = 0;
    uint16_t lastRecievedIndex = 0;
public:
    PackageBuffer();
    ~PackageBuffer();

    void addPackage(Package p);
    void overritePackage(Package p);
    Package getPackageWithId(MSG_ID id);
    Package returnFirstPackage();
    Package readLastPackage();
    void deleteIndex(uint16_t index);
	void deleteLastRecieved();

    boolean hasPackages();

    



};