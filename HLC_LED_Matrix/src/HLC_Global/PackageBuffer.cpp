#include "PackageBuffer.h"


PackageBuffer::PackageBuffer()
{
    myArray = new Package[20];
}

PackageBuffer::~PackageBuffer()
{
    delete [] myArray;
}

void PackageBuffer::addPackage(Package p)
{
    myArray[++lastIndex] = p;
}

Package PackageBuffer::returnFirstPackage()
{
    Package p = &myArray[0];

    for(int i = 0; i<myArray.length-1; i++)
    {
        myArray[i] = myArray[i+1];
    }
    myArray[lastIndex] = nullptr;
    lastIndex--;
    return p;
}