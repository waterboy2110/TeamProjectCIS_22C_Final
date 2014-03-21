//***********************************************************************************************************
// Specification file for binary node class
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// BinaryNode is a class to hold each node of the binary tree. The private members are the left and right
// child pointers along with a pointer to the restaurant object. Gets and sets are available for all private
// members as well as a method to return whether a node is a leaf.
//***********************************************************************************************************

#ifndef __Project_3_9__BinaryNode__
#define __Project_3_9__BinaryNode__

#include <iostream>
#include "RestaurantInfo.h"
#define nullptr 0

using namespace std;


class BinaryNode
{
private:
    restaurantInfo* RestaurantInfoPtr;                              // Pointer to a restaurant object
    BinaryNode* rightChildPtr;                                      // A nodes right child pointer
    BinaryNode* leftChildPtr;                                       // A nodes left child pointer
    
public:
    BinaryNode(restaurantInfo*);
    BinaryNode* getLeftChildPtr() const;                             // Gets for private members
    BinaryNode* getRightChildPtr() const;
    restaurantInfo* getrestaurantInfo() const;
    
    void setLeftChildPtr(BinaryNode* leftPtr);                        // Sets for private members
    void setRightChildPtr(BinaryNode* rightPtr);
    void SetRestaurantInfo (restaurantInfo* restInfo);
    bool isLeaf()const;    
};



#endif
