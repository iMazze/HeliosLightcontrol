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
    myArray[numberOfElements] = p;
    numberOfElements += 1;
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

boolean PackageBuffer::hasPackages()
{
    return numberOfElements != 0;
}