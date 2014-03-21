//***********************************************************************************************************
// Specification file for binary search tree class
//***********************************************************************************************************

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
private:
    BinaryNode* RootPtr; //Pointer to BinaryNode
    
public:
    // Constructor
    BinarySearchTree();
    
    // Binary Search Tree Functions
    BinaryNode* getroot()const;
    void setRoot(BinaryNode* node){RootPtr = node; };
    bool addNode(restaurantInfo* RestaurantInfoPtr);            //Add new node in BST
    void printIndentedList(BinaryNode* root, int i)const;       //Print Indented List
    BinaryNode* SearchName(BinaryNode* root, string name)const; //Search by restaurant name
    BinaryNode* removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success);// Remove a restaurant by name
    BinaryNode* removeNode(BinaryNode* root);                   // Remove node
    BinaryNode* removeLeftmostNode(BinaryNode* root, restaurantInfo*&Arestaurant ); //Return the most left Node
    bool saveToFile(BinaryNode* rootPtr)const;  // Save to output file
    void DestroyTree(BinaryNode* root);         // Destroy tree
    
};
#endif