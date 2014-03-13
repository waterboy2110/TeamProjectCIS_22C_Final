//***************************************************************************************
// Specification file for listHead class
//***************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// - Add BST pointer
// - Add deconstructor
//***********************************************************************************************************

#ifndef Project_3_9_ListHead_h
#define Project_3_9_ListHead_h

#include "Hash.h"
#include "RestaurantInfo.h"
#include "CollisionTable.h"

//#define arraySize 21

class listHead
{
private:
    //collisionTable *hi;
    int numRestaurants;  // Number of restaurants
    int arraySize;       // Size of hash table
    Hash *hashPtr;    // Pointer to the hash table
    //binaryNode *BSTPtr; // Pointer to the binary search tree
    
public:
    // Constructor
    listHead(int aArraySize);
    
    // List Head operations
    int getNumRestaurants() const;
    Hash* getHashPtr() const;
    
};// End listHead

#endif
