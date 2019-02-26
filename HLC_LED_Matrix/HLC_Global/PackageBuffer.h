/***************************************************************************************************************
FILE: PackageBuffer.h
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description:    Its an buffer with a specific count of spaces. You can e.g. get the first item, 
                work with it and delete it. You also can get some items from specific index, etc.

Compiler dependencies or special instructions:
- WirelessConnection.h

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#ifndef PACKAGEBUFFER_H
#define PACKAGEBUFFER_H

#include "WirelessConnection.h"

class PackageBuffer
{
private:
    // Declaration
    Package myArray[20]; // Max Buffer Space

    uint16_t numberOfElements = 0; // Actual number of elements in the buffer
    uint16_t lastRecievedIndex = 0; // Index where the last recieved (added) package is
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
    boolean hasPackageWithId(MSG_ID id);
    



};

#endif