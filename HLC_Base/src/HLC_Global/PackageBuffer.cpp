/****************************************************************************************************************
FILE: PackageBuffer.cpp
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description:    Its an buffer with a specific count of spaces. You can e.g. get the first item, 
                work with it and delete it. You also can get some items from specific index, etc.


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#include "PackageBuffer.h"


// Default CTOR is empty
PackageBuffer::PackageBuffer()
{
}

// Cleans the array
PackageBuffer::~PackageBuffer()
{
    delete [] myArray;
}

// Adds a package to the first free space
void PackageBuffer::addPackage(Package p)
{
	lastRecievedIndex = numberOfElements;
    myArray[numberOfElements] = p;
    numberOfElements += 1;
}

// overwrites the package in the buffer with the same message id.
// if there is no package with this id, it will create a new one.
void PackageBuffer::overritePackage(Package p)
{
    // Searches for the existing package
	for(int i = 0; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
	{
		if(myArray[i].id == p.id)
		{
            // overwrites the package
			myArray[i] = p;
			lastRecievedIndex = i;
			return;
		}
	}
	
    // adding the new one
    addPackage(p);
}

// Returns the package with the specific id
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

// Returns the first package in the buffer. Most times its the oldest one
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

// Returns the last incoming package
Package PackageBuffer::readLastPackage()
{
    return myArray[lastRecievedIndex];
}

// Deletes the package on the given index
void PackageBuffer::deleteIndex(uint16_t index)
{
	for(int i = index; i<(sizeof(myArray) / sizeof(myArray[0]))-1; i++)
	{
		myArray[i] = myArray[i+1];
	}
	myArray[numberOfElements-1] = Package();
    numberOfElements--;
}

// Deletes the last recieved package
void PackageBuffer::deleteLastRecieved()
{
	deleteIndex(lastRecievedIndex);
}

// Returns true if there are new packages in the buffer
boolean PackageBuffer::hasPackages()
{
    return numberOfElements != 0;
}