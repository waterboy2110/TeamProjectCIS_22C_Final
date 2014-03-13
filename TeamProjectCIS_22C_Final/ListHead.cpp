//***************************************************************************************
// Implementation file for ListHead class
//***************************************************************************************

#include "ListHead.h"

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// - Add pointers to hash and BST
// - Read in array size? Or created specifically? -> Send array size to Hash class constructor
//***********************************************************************************************************

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
listHead::listHead(int aArraySize)
{
    // Store hash table size
    //arraySize = aArraySize;
    arraySize = 21;
    
    // Create hash table and store in listHead
    //Hash *aHashPtr;
    //aHashPtr = new Hash[aArraySize];
    hashPtr =  new Hash[21];
    
    //hashPtr[0]->getNumRestaurants();
}
//***********************************************************************************************************
// Definition of getNumRestaurants
//
//***********************************************************************************************************
int listHead::getNumRestaurants() const
{
    return numRestaurants;
}

//***********************************************************************************************************
// Definition of getHashPtr
//
//***********************************************************************************************************
Hash* listHead::getHashPtr() const
{
    return hashPtr;
}