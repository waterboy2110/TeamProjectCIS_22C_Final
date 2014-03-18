//
//  BinaryNode.h
//  Project 3.9
//
//  Created by Yenni Chu on 3/11/14.
//  Copyright (c) 2014 Yenni Chu. All rights reserved.
//

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
    // BinaryNode();
    
};



#endif
