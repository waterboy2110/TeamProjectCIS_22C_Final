//***************************************************************************************
// Implementation file for ListHead class
//***************************************************************************************

#include "ListHead.h"

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// X Add pointers to hash and BST
// X Read in array size? Or created specifically? -> Send array size to Hash class constructor
//***********************************************************************************************************

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
listHead::listHead(int aArraySize)
{
    // Store hash table size
    arraySize = aArraySize;
    
    // Initialize number of restaurants stored
    numRestaurants = 0;
    
    // Create hash table and store in listHead    
    hashPtr = new Hash(aArraySize);
    
    // Create binary search tree and store in listHead
    //BSTPtr = new BinarySearchTree();
        
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
// Definition of addNumRestaurants
//
//***********************************************************************************************************
void listHead::addNumRestaurants()
{
    numRestaurants++;
}

//***********************************************************************************************************
// Definition of subNumRestaurants()
//
//***********************************************************************************************************
void listHead::subNumRestaurants()
{
    numRestaurants--;
}

//***********************************************************************************************************
// Definition of getHashPtr
//
//***********************************************************************************************************
Hash* listHead::getHashPtr() const
{
    return hashPtr;
}

//***********************************************************************************************************
// Definition of getBSTPtr
BinarySearchTree* listHead::getBSTPtr() const
{
    return BSTPtr;
}