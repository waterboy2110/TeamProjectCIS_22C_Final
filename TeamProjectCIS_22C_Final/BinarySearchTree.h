//
//  BinarySearchTree.h
//  Project 3.9
//
//  Created by Yenni Chu on 3/11/14.
//  Copyright (c) 2014 Yenni Chu. All rights reserved.
//

#ifndef __Project_3_9__BinarySearchTree__
#define __Project_3_9__BinarySearchTree__

#include <iostream>
#include <string>
#include "BinaryNode.h"
#include "RestaurantInfo.h"
#include "Hash.h"
using namespace std;

class BinarySearchTree
{
    //friend class Hash;
private:
    
    BinaryNode* RootPtr;
public:
    BinarySearchTree();
    BinaryNode* getroot()const;
    bool addNode(restaurantInfo* RestaurantInfoPtr);
    void printIndentedList(BinaryNode* root, int i)const;
    
    BinaryNode* SearchName(BinaryNode* root, string name)const;
       
    //bool RemoveByAdressNumber(int addressNum, string deName);
   // delete functions
    bool remove(string deName, Hash* aHashTable);
    BinaryNode* removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success, Hash* aHashTable);
    BinaryNode* removeNode(BinaryNode* root, Hash* aHashTable);
    BinaryNode* removeLeftmostNode(BinaryNode* root, restaurantInfo*&Arestaurant, Hash* aHashTable );
};
#endif