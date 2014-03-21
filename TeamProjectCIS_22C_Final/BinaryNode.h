//***********************************************************************************************************
// Specification file for binary node class
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
    restaurantInfo* RestaurantInfoPtr;
    BinaryNode* rightChildPtr;
    BinaryNode* leftChildPtr;
    
public:
    BinaryNode(restaurantInfo*);
    BinaryNode* getLeftChildPtr() const;
    BinaryNode* getRightChildPtr() const;
    restaurantInfo* getrestaurantInfo() const;
    
    void setLeftChildPtr(BinaryNode* leftPtr);
    void setRightChildPtr(BinaryNode* rightPtr);
    void SetRestaurantInfo (restaurantInfo* restInfo);
    bool isLeaf()const;    
};



#endif
