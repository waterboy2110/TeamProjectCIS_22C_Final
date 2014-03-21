//***********************************************************************************************************
// Specification file for binary search tree class
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// BinarySearchTree is a class that defines the methods and accessors requried to build and maintain a BST
// The class has one member - a pointer to the BinaryNode.
// Within the class are methods to get / set the root, add / remove a node, print the indented tree
// search for restaurant by name, remove the left most node and save to file.
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
    
    BinaryNode* RootPtr;                                                                    // Pointer to BinaryNode
public:
    // Constructor
    BinarySearchTree();
    
    // Binary Search Tree Functions
    BinaryNode* getroot()const;                                                             // Return the root of the tree
    void setRoot(BinaryNode* node){RootPtr = node; };                                       // In line - set the root to a node
    bool addNode(restaurantInfo* RestaurantInfoPtr);                                        // Add new node in BST
    void printIndentedList(BinaryNode* root, int i)const;                                   // Print Indented List
    BinaryNode* SearchName(BinaryNode* root, string name)const;                             // Search by restaurant name
    BinaryNode* removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success);    // Remove a restaurant by name
    BinaryNode* removeNode(BinaryNode* root);                                               // Remove a node
    BinaryNode* removeLeftmostNode(BinaryNode* root, restaurantInfo*&Arestaurant );         // Return the most left Node
    bool saveToFile(BinaryNode* rootPtr);                                                   // Save the tree to a file

};
#endif