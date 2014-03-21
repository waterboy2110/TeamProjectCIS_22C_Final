//***********************************************************************************************************
// Implementation file for ListHead class
//***********************************************************************************************************

#include "ListHead.h"

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
    BSTPtr = new BinarySearchTree();
    
}

//***********************************************************************************************************
// Deconstructor
//***********************************************************************************************************
listHead::~listHead()
{
    // Destroy hash
    //hashPtr->destroyHash();
    
    //delete BSTPtr;
    
}// End deconstructor

//***********************************************************************************************************
// Definition of getNumRestaurants
//
// Returns the number of restaurants stored.
//***********************************************************************************************************
int listHead::getNumRestaurants() const
{
    return numRestaurants;
}

//***********************************************************************************************************
// Definition of addNumRestaurants
//
// Updates the number of restaurants stored by adding one.
//***********************************************************************************************************
void listHead::addNumRestaurants()
{
    numRestaurants++;
}

//***********************************************************************************************************
// Definition of subNumRestaurants()
//
// Updates the number of restaurants stored by subtracting one. 
//***********************************************************************************************************
void listHead::subNumRestaurants()
{
    numRestaurants--;
}

//***********************************************************************************************************
// Definition of getHashPtr
//
// Returns a pointer to the hash array.
//***********************************************************************************************************
Hash* listHead::getHashPtr() const
{
    return hashPtr;
}

//***********************************************************************************************************
// Definition of getBSTPtr
//
// Returns a pointer to the BST.
//***********************************************************************************************************
BinarySearchTree* listHead::getBSTPtr() const
{
    return BSTPtr;
}