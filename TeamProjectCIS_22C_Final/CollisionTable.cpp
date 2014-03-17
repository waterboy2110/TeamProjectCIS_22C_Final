//***************************************************************************************
// Implementation file for CollisionTable class
//***************************************************************************************

//***************************************************************************************
// THINGS TO CHANGE
//
// - make sure no unncecessary paramters (some you do not need to receive a poiinter like get fcns)
// - remove unnecessary returns (a lot of bools)
//***************************************************************************************

#include "CollisionTable.h"

//***************************************************************************************
// Default constructor
//***************************************************************************************
collisionTable::collisionTable()
{
    cRestaurant = nullptr;
    nextC = nullptr;
}// End default constructor

//***************************************************************************************
// Constructor
//***************************************************************************************
/*
collisionTable::collisionTable(restaurantInfo *collisionPtr)
{
    cRestaurant = collisionPtr; 
    
}// End constructor*/

//***************************************************************************************
// Definition insertCollision
//
//***************************************************************************************
bool collisionTable::insertCollision(restaurantInfo *collisionPtr, int hashNum, collisionTable *&ptr)
{
    collisionTable *newNode;             // A new node
    collisionTable *nodePtr;             // To traverse the list
    collisionTable *previousNode = nullptr; // The previous node
    
    // Allocate a new node and store countryIn there.
    newNode = new collisionTable;
    newNode->cRestaurant = collisionPtr;
    
    // Position nodePtr at the head of list.
    nodePtr = ptr;
    
    // Initialize previousNode to NULL.
    previousNode = nullptr;
    
    // Skip all nodes whose value is less than code.
    while (nodePtr != nullptr)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->nextC;
    }
    
    // If the new node is to be the 1st in the list,
    // insert it before all other nodes.
    if (previousNode == nullptr)
    {
        ptr = newNode;
        newNode->nextC = nodePtr;
    }
    else  // Otherwise insert after the previous node.
    {
        previousNode->nextC = newNode;
        newNode->nextC = nodePtr;
    }
    
    return true;

}// End insertCollision

//***************************************************************************************
// Definition of deleteCollision
//
//***************************************************************************************
bool collisionTable::deleteCollision(int tStreetNum, collisionTable *ptr)
{
    
    collisionTable *nodePtr;       // To traverse the list
    collisionTable *previousNode;  // To point to the previous node
    
    // Initialize nodePtr to head of list
    nodePtr = ptr;
    previousNode = nullptr;
    
    // Skip all nodes whose code is not equal to the code pointed by pDeleteCode.
    while (nodePtr != nullptr && (nodePtr->cRestaurant->getNumber() != tStreetNum))
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->nextC;
    }
    
    // If node-to-delete not found OR no nodes
    if (!nodePtr)
        return false;
    
    // Determine if the first node is the one
    if (!previousNode)
    {
        ptr = nullptr;
        delete nodePtr;
    }
    else
    {
        // otherwise (node-to-delete found & not first node)
       // nodeData = nodePtr->country;  // return the deleted data
        previousNode->nextC = nodePtr->nextC;
        delete nodePtr;
    }

    
    
    return true;
}

//***************************************************************************************
// Definition of getLastCollision
//
//***************************************************************************************
restaurantInfo* collisionTable::getLastCollision(collisionTable *ptr)
{
    return cRestaurant;
}


//***************************************************************************************
//
//***************************************************************************************
restaurantInfo* collisionTable::getRestaurantInfo()
{
    return cRestaurant;
}

//***************************************************************************************
// Definition of displayCollisionList
//
//***************************************************************************************
bool collisionTable::searchCollisionList(collisionTable *ptr, int searchNum)
{
    collisionTable *pWalk;
    pWalk = ptr;
    
    while (ptr != nullptr)
    {
        if (ptr->cRestaurant->getNumber() == searchNum)
        {
            cout << "     - " <<  ptr->cRestaurant->getName() << endl;
        }
        
        ptr = ptr->nextC;
    }
    
    return true;
}

//***************************************************************************************
//
//***************************************************************************************
bool collisionTable::searchForAdd(collisionTable *ptr, int addNum)
{
    collisionTable *pWalk;
    pWalk = ptr;
    
    while (ptr != nullptr)
    {
        if (ptr->cRestaurant->getNumber() == addNum)
        {
            return false;
        }
        
        ptr = ptr->nextC;
    }
    
    return true;
}

//***************************************************************************************
//
//***************************************************************************************
void collisionTable::displayCollisionList(collisionTable *ptr)
{
    collisionTable *pWalk;
    pWalk = ptr;
    
    while (ptr != nullptr)
    {
        pWalk->cRestaurant->displayRestaurant();
        
        ptr = ptr->nextC;
    }
}


