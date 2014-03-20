//
//  BinarySearchTree.cpp
//  Project 3.9
//
//  Created by Yenni Chu on 3/11/14.
//  Copyright (c) 2014 Yenni Chu. All rights reserved.
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



/*
bool BinarySearchTree::RemoveByAdressNumber(int addressNum, string deName)
{
    BinaryNode* tempNode = SearchName(RootPtr , deName);
    
    if(tempNode==nullptr)
    {
        cout << deName << " is not found"<<endl;
        return false;
    }
    
    while(tempNode!= nullptr)
    {
        cout << tempNode->getrestaurantInfo()->getName()<< " " ;
        cout << tempNode->getrestaurantInfo()->getNumber()<<endl;
        tempNode = SearchName(tempNode->getRightChildPtr(), deName);
        
    }
    
}
*/


/*****************
 Three clases:
 1) leaves
 2) has only one child
 3) has two children
*******************/
bool BinarySearchTree::remove(string deName, Hash* aHashTable)
{
      
    bool DeleteSuccessful = true;
    while (DeleteSuccessful)
    {
        RootPtr = removeRestaurant(deName, RootPtr , DeleteSuccessful, aHashTable);
        
    }
    return DeleteSuccessful;
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
    string tempName="ee";
    
    if (root->isLeaf())
    {
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        // set pointer to restaurant Info to nullptr
      
        root->SetRestaurantInfo(nullptr);
    //    tempName = root->getrestaurantInfo()->getName();
        delete root;
        root = nullptr;
        // delete from hash
        aHashTable->deleteHash(DeAddressNum, tempName);
        
        return  nullptr; 
    }
    else if (root->getLeftChildPtr() == nullptr)  // Has rightChild only
    {
        BinaryNode* nodeToConnectPtr = root->getRightChildPtr();
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        // set pointer to restaurant Info to nullptr
        root->SetRestaurantInfo(nullptr);
        delete root;
        root = nullptr;
        return nodeToConnectPtr;
    }
    else if(root->getRightChildPtr() == nullptr) // Has left child only
    {
        BinaryNode* nodeToConnectPtr = root->getLeftChildPtr();
        DeAddressNum= root->getrestaurantInfo()->getNumber();
        // set pointer to restaurant Info to nullptr
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

//**************************************************
// Definition of function saveToFile.
// Writes to file from the BST.
//**************************************************
bool BinarySearchTree::saveToFile(BinaryNode *binaryNodePtr)
{
    ofstream outFile;
    string fileName ="RestaurantsOutfile.txt";
    bool success = true;
    bool done = false;
    vector<BinaryNode> vBST;
    
    
    // Open file to write, if unable, display error and exit with false
    outFile.open(fileName);
    if (!outFile)
    {
        cout << "Error opening " << fileName << "!\n";
        return false;
    }
    cout << "Saving File...\n";
   
    BinaryNode *current = binaryNodePtr;
    while(!done)
    {
        if(current)
        {
            vBST.push_back(*current);
            current = current->getLeftChildPtr();
        }
        else
        {
            if(vBST.empty())
            {
                done = true;
            }
            else
            {
                current = &vBST.back();
                vBST.pop_back();
                outFile << current->getrestaurantInfo()->getName();
                outFile << to_string(current->getrestaurantInfo()->getNumber()) << endl;
                outFile << current->getrestaurantInfo()->getStreet();
                outFile << current->getrestaurantInfo()->getType();
                current = current->getRightChildPtr();
            }
        }
    }

    outFile.close();
    
    if (!success)
        return false;
    
    return true;
}




