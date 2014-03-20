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
#include <fstream>
#include <vector>

using namespace std;

class BinarySearchTree
{
    //friend class Hash;
private:
    
    BinaryNode* RootPtr; //Pointer to BinaryNode
public:
    BinarySearchTree(); //constructor
    BinaryNode* getroot()const;
    void setRoot(BinaryNode* node){RootPtr = node; };
    bool addNode(restaurantInfo* RestaurantInfoPtr); //ass new node in BST
    void printIndentedList(BinaryNode* root, int i)const; //print Indented List
    BinaryNode* SearchName(BinaryNode* root, string name)const;//Search by restaurant name
    //bool RemoveByAdressNumber(string addressNum, string deName);// remove node by address number
    // remove node by restaurant name
    //bool remove(string deName);
    BinaryNode* removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success);
    BinaryNode* removeNode(BinaryNode* root);
    BinaryNode* removeLeftmostNode(BinaryNode* root, restaurantInfo*&Arestaurant );//return the most left Node
    bool saveToFile(BinaryNode* rootPtr);
};
#endif