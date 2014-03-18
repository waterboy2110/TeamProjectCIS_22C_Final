//***********************************************************************************************************
// Specification file for listHead class
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// X Add BST pointer
// - Add deconstructor
//***********************************************************************************************************

#ifndef Project_3_9_ListHead_h
#define Project_3_9_ListHead_h

#include "Hash.h"
#include "RestaurantInfo.h"
#include "BinarySearchTree.h"
#include "CollisionTable.h"


class listHead
{
private:
    int numRestaurants;  // Number of restaurants
    int arraySize;       // Size of hash table
    Hash *hashPtr;    // Pointer to the hash table
    BinarySearchTree *BSTPtr; // Pointer to the binary search tree
    
public:
    // Constructor
    listHead(int aArraySize);
    
    // List Head operations
    int getNumRestaurants() const;
    void addNumRestaurants();
    void subNumRestaurants();
    Hash* getHashPtr() const;
    BinarySearchTree* getBSTPtr() const;
    
};// End listHead

#endif
