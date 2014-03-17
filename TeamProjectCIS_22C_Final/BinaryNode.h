//
//  BinaryNode.h
//  Project 3.9
//
//  Created by Christina Dee Sok on 3/16/14.
//  Copyright (c) 2014 Christina Sok. All rights reserved.
//

#ifndef Project_3_9_BinaryNode_h
#define Project_3_9_BinaryNode_h

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
    // BinaryNode();
    
};

#endif
