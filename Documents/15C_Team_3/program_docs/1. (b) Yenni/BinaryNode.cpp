//***********************************************************************************************************
// Implementation file for binary node class
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// BinaryNode.cpp class implements the methods that allow access to the nodes private members. There are sets
// and gets for each member as well as a method to return a bool if a node is a leaf. The constructor builds
// a restaurant object and sets the intitial left / right pointers to null.
//***********************************************************************************************************

#include "BinaryNode.h"

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
BinaryNode:: BinaryNode (class restaurantInfo* RestInfo)
{
    leftChildPtr=nullptr;
    rightChildPtr= nullptr;
    RestaurantInfoPtr = RestInfo;
    
}// End constructor

//***********************************************************************************************************
// Definition of getLeftChildPtr
// Returns a pointer to the left child node
// Pre - none
// Post the LeftChildPtr is returned as a BinaryNode
//***********************************************************************************************************
BinaryNode* BinaryNode::BinaryNode::getLeftChildPtr() const
{
    return leftChildPtr;
    
}// End getLeftChildPtr

//***********************************************************************************************************
// Definition of getRightChildPointer
// Returns a pointer to the right child node
// Pre - none
// Post the RightChildPtr is returned as a BinaryNode
//***********************************************************************************************************
BinaryNode* BinaryNode::BinaryNode::getRightChildPtr() const
{
    return rightChildPtr;
    
} //End getRightChildPtr

//***********************************************************************************************************
// Definition of setRightChildPtr
// Accessor to set a pointer to the right child of a node
// Pre - A BinaryNode pointer.
// Post - The nodes rightChildPtr is updated
//***********************************************************************************************************
void BinaryNode::setRightChildPtr(BinaryNode* rightPtr)
{
    rightChildPtr = rightPtr;
    
} // End setRightChildPtr

//***********************************************************************************************************
// Definition of setLeftChildPtr
// Accessor to set a pointer to the left child of a node
// Pre - A BinaryNode pointer.
// Post - The nodes leftChildPtr is updated
//***********************************************************************************************************
void BinaryNode::setLeftChildPtr(BinaryNode* leftPtr)
{
    leftChildPtr = leftPtr;
    
}// End setRightChildPtr

//***********************************************************************************************************
// Definition of getRestaurantInfo
// Method that returns a pointer to a Restaurant object.
// Pre - none
// Post - The private member pointer is returned to the caller
//***********************************************************************************************************
restaurantInfo*  BinaryNode::getrestaurantInfo() const
{
    return RestaurantInfoPtr;
    
}// End getRestaurantInfo

//***********************************************************************************************************
// Definition of isLeaf
// Method determines if a node is a leaf by testing for null for each pointer in a given node.
// Pre - none
// Post - returns bool if both pointers to a given node are null
//***********************************************************************************************************
bool BinaryNode:: isLeaf() const
{
    return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
    
}

//***********************************************************************************************************
// Definition of setRestaurantInfo
// Method sets the private member restaurant pointer given a pointer to a restaurant that was passed in
// Pre - a pointer to a restaurant object
// Post - none
//***********************************************************************************************************
void BinaryNode::SetRestaurantInfo (restaurantInfo* restInfo)
{
    RestaurantInfoPtr= restInfo;
}

