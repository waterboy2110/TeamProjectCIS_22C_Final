//
//  BinarySearchTree.cpp
//  Project 3.9
//
//  Created by Christina Dee Sok on 3/16/14.
//  Copyright (c) 2014 Christina Sok. All rights reserved.
//

#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree():RootPtr(nullptr){}

BinaryNode*  BinarySearchTree::getroot()const
{
    return RootPtr;
}

bool BinarySearchTree:: addNode(restaurantInfo* RestaurantInfoPtr)
{
    BinaryNode* newNode = new BinaryNode(RestaurantInfoPtr);
    BinaryNode* parent=NULL;
    
    
    
    if(!newNode)
    {
        return false;
    }
    
    
    if(!getroot())   // if there is no any node on the tree, make root points to newNode
    {
        RootPtr= newNode;    // root is newNodePtr
    }
    else
    {
        
        BinaryNode* current = RootPtr;
        while(current!=nullptr)
        {
            parent= current;
            
            if( newNode->getrestaurantInfo()->getName() < current->getrestaurantInfo()->getName() )
            {
                current = current->getLeftChildPtr();
            }
            else
            {
                current = current->getRightChildPtr();
                
            }
        }
        
        if (parent->getrestaurantInfo()->getName()  > newNode->getrestaurantInfo()->getName())
            // parent's child pointer points to new node
        {
            
            parent->setLeftChildPtr(newNode);
        }
        else
        {
            parent->setRightChildPtr(newNode);
            
            
        }
        
        
    }
    
    return true;
    
}


void BinarySearchTree::printIndentedList(BinaryNode* root, int i)const
{
    if(root)// check if the tree exsits
    {
        i++;
        cout <<i<<". ";                 // print the level number
        cout << root->getrestaurantInfo()->getName()<<endl;// print data
        
        if(root->getRightChildPtr())
        {
            for(int g=i; g>0;g--)
                cout << "     ";              // print the space
            printIndentedList(root->getRightChildPtr(),i);
            
        }
        if(root->getLeftChildPtr())
        {
            for(int g=i; g>0;g--)          // print the space
                cout << "     ";
            printIndentedList(root->getLeftChildPtr(),i);
            
        }
    }
}
/*
 BinaryNode* BinarySearchTree::SearchName(BinaryNode* root, string name)const
 {
 if(!root)
 {
 return nullptr;
 
 }
 else
 {
 if(name < (root->getrestaurantInfo()->getName()))
 {
 return SearchName(root->getLeftChildPtr(), name);
 }
 else
 {
 
 if(name > (root->getrestaurantInfo()->getName()))
 {
 return SearchName(root->getRightChildPtr(), name);
 }
 else
 {
 return root;
 
 }
 }
 
 }
 
 }
 
 bool BinarySearchTree::SearchNameManager(string searchName)
 {
 BinaryNode* tempNode = SearchName(RootPtr, searchName);
 
 if(tempNode==nullptr)
 {
 cout << searchName << " is not found"<<endl;
 return false;
 }
 
 while(tempNode!= nullptr)
 {
 tempNode = SearchName(tempNode->getRightChildPtr(), searchName);
 }
 return true;
 }*/
/*BinaryNode* BinarySearchTree::getParent(BinaryNode* root, string name, BinaryNode* parent)const
 {
 if(!root)
 {
 return nullptr;
 }
 else  //@@@@@ when node ==1
 {
 if(name < root->getrestaurantInfo()->getName())
 {
 parent=root;
 return  getParent( root->getLeftChildPtr(), name, parent);
 
 }
 else
 {
 
 if(name > root->getrestaurantInfo()->getName())
 {  parent=root;
 return getParent( root->getRightChildPtr(), name, parent);
 }
 else
 {
 return parent;
 }
 
 }
 }
 }*/
void BinarySearchTree::RemoveAllRestaurantWithMatchingName(string deName, Hash* aHashTable)
{
    bool find = remove(deName,aHashTable);
    
    while(find)
    {
        find = remove(deName,aHashTable);
        
    }
}
bool BinarySearchTree::remove(string deName, Hash* aHashTable)
{
    
    bool DeleteSuccessful = false;
    RootPtr = removeRestaurant(deName, RootPtr , DeleteSuccessful, aHashTable);
    return DeleteSuccessful;
    // end remove
}
BinaryNode* BinarySearchTree::removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success,  Hash *aHashTable)
{
    if (subTreePtr == nullptr)
    {
        // Not found here
        success = false;
        return nullptr;
    }
    if (subTreePtr->getrestaurantInfo()->getName() == DeName)
    {
        // Item is in the root of some subtree
        
        subTreePtr = removeNode(subTreePtr,aHashTable);
        success = true;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getrestaurantInfo()->getName() > DeName)
            // Search the left subtree
            subTreePtr->setLeftChildPtr(removeRestaurant(DeName, subTreePtr->getLeftChildPtr(), success, aHashTable));
        else
            // Search the right subtree
            subTreePtr->setRightChildPtr(removeRestaurant(DeName, subTreePtr->getRightChildPtr(),  success, aHashTable));
        
        return subTreePtr;
    }  // end if
    
    
}



BinaryNode* BinarySearchTree:: removeNode(BinaryNode* root, Hash *aHashTable)
{
    int DeAddressNum;
    
    if (root->isLeaf())
    {
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        root->SetRestaurantInfo(nullptr);
        delete root;
        root = nullptr;
        aHashTable->deleteHash(DeAddressNum);
        
        return  nullptr; // Assign and return (student maybe should have separate statements)
    }
    else if (root->getLeftChildPtr() == nullptr)  // Has rightChild only
    {
        BinaryNode* nodeToConnectPtr = root->getRightChildPtr();
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        root->SetRestaurantInfo(nullptr);
        delete root;
        root = nullptr;
        return nodeToConnectPtr;
    }
    else if(root->getRightChildPtr() == nullptr) // Has left child only
    {
        BinaryNode* nodeToConnectPtr = root->getLeftChildPtr();
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        root->SetRestaurantInfo(nullptr);
        delete root;
        root = nullptr;
        return nodeToConnectPtr;
    }
    else                                             // Has two children
    {
        
        // Traditional way to remove a value in a node with two children
        restaurantInfo* newrestaurant = nullptr;
        BinaryNode* deNode = removeLeftmostNode(root->getRightChildPtr(), newrestaurant, aHashTable);
        DeAddressNum= deNode->getrestaurantInfo()->getNumber();
        
        root->setRightChildPtr(deNode);
        root->SetRestaurantInfo(newrestaurant);
        return root;
    }
}
BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* root, restaurantInfo* &Arestaurant, Hash* aHashTable)
{
    
    if (root->getLeftChildPtr() == nullptr)
    {
        Arestaurant = root->getrestaurantInfo();
        return removeNode(root, aHashTable);
    }
    else
    {
        root->setLeftChildPtr(removeLeftmostNode(root->getLeftChildPtr(), Arestaurant, aHashTable));
        return root;
    }  // end if
}






