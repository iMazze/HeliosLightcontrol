/****************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
#include "PackageBuffer.h"


PackageBuffer::PackageBuffer()
{
}

PackageBuffer::~PackageBuffer()
{
    delete [] myArray;
}

void PackageBuffer::addPackage(Package p)
{
	lastRecievedIndex = numberOfElements;
    myArray[numberOfElements] = p;
    numberOfElements += 1;
}

void PackageBuffer::overritePackage(Package p)
{
	for(int i = 0; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
	{
		if(myArray[i].id == p.id)
		{
			myArray[i] = p;
			lastRecievedIndex = i;
			return;
		}
	}
	
    addPackage(p);
}

Package PackageBuffer::getPackageWithId(MSG_ID id)
{
	for(int i = 0; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
	{
		if(myArray[i].id == id)
		{
			return myArray[i];
		}
	}
}

Package PackageBuffer::returnFirstPackage()
{
    Package p = myArray[0];

    for(int i = 0; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
    {
        myArray[i] = myArray[i+1];
    }
    myArray[numberOfElements-1] = Package();
    numberOfElements--;
    return p;
}

Package PackageBuffer::readLastPackage()
{
    return myArray[lastRecievedIndex];
}

void PackageBuffer::deleteIndex(uint16_t index)
{
	for(int i = index; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
	{
		myArray[i] = myArray[i+1];
	}
	myArray[numberOfElements-1] = Package();
    numberOfElements--;
}

void PackageBuffer::deleteLastRecieved()
{
	deleteIndex(lastRecievedIndex);
}

boolean PackageBuffer::hasPackages()
{
    return numberOfElements != 0;
}