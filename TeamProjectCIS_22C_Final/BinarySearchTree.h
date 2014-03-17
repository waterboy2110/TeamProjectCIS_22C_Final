//
//  BinarySearchTree.h
//  Project 3.9
//
//  Created by Christina Dee Sok on 3/16/14.
//  Copyright (c) 2014 Christina Sok. All rights reserved.
//

#ifndef Project_3_9_BinarySearchTree_h
#define Project_3_9_BinarySearchTree_h


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
    
    //BinaryNode* SearchName(BinaryNode* root, string name)const;
    //bool SearchNameManager(string searchName)
    //BinaryNode* getParent(BinaryNode* root, string name,BinaryNode* parent)const;
    void RemoveAllRestaurantWithMatchingName(string deName, Hash* aHashTable);
    bool remove(string deName, Hash* aHashTable);
    BinaryNode* removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success, Hash* aHashTable);
    BinaryNode* removeNode(BinaryNode* root, Hash* aHashTable);
    BinaryNode* removeLeftmostNode(BinaryNode* root, restaurantInfo*&Arestaurant, Hash* aHashTable );
};
#endif