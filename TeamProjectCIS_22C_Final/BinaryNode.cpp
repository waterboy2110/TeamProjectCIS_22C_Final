//
//  BinaryNode.cpp
//  Project 3.9
//
//  Created by Yenni Chu on 3/11/14.
//  Copyright (c) 2014 Yenni Chu. All rights reserved.
//

#include "BinaryNode.h"

// get left child pointer
BinaryNode* BinaryNode::BinaryNode::getLeftChildPtr() const
{
    return leftChildPtr;
}  // end getLeftChildPtr

// get right child pointer
BinaryNode* BinaryNode::BinaryNode::getRightChildPtr() const
{
    return rightChildPtr;
}  // end getRightChildPtr

// set right child pointer
void BinaryNode::setRightChildPtr(BinaryNode* rightPtr)
{
    rightChildPtr = rightPtr;
}  // end setRightChildPtr

// set left child pointer
void BinaryNode::setLeftChildPtr(BinaryNode* leftPtr)
{
    leftChildPtr = leftPtr;
}  // end setRightChildPtr



BinaryNode:: BinaryNode( class restaurantInfo* RestInfo) ///@@@@@@@
{
    leftChildPtr=nullptr;
    rightChildPtr= nullptr;
    RestaurantInfoPtr = RestInfo;
}

restaurantInfo*  BinaryNode::getrestaurantInfo() const
{
    return RestaurantInfoPtr;
}
bool BinaryNode:: isLeaf() const
{
    return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
    
}

void BinaryNode::SetRestaurantInfo (restaurantInfo* restInfo)
{
    RestaurantInfoPtr= restInfo;
}

