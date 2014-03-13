//***************************************************************************************
// Implementation file for CollisionTable class
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
    
    /*
    collisionTable *pWalk;
    collisionTable *pPre;
    
    // Create a collision object and store parameter
    collisionTable *insertCollision;
    insertCollision = new collisionTable;
    if (!insertCollision)
    {
        return false;
    }
    
    // If there are no collisions...
    if (ptr == nullptr)
    {
        insertCollision->cRestaurant = collisionPtr;
        insertCollision->nextC = nullptr;
    }
    else    // Otherwise...
    {
        // Traverse the list until the end
        pWalk = ptr;        
        while (pWalk != nullptr)
        {
            pPre = pWalk;
            pWalk = pWalk->nextC;
            
        }// End while
        
        // Insert restaurant
        pPre->nextC = insertCollision;
        
    }// End if
    
    return true;*/
}// End insertCollision

//***************************************************************************************
// Definition of deleteCollision
//
//***************************************************************************************
bool collisionTable::deleteCollision(int tStreetNum, collisionTable *ptr)
{
    /*
    collisionTable *pWalk;
    collisionTable *pPrevious;*/
    
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
       // nodeData = head->country;     // return the deleted data
        //nodePtr = ptr->nextC;
        ptr = nullptr;
        delete nodePtr;

        //ptr = nodePtr;
    }
    else
    {
        // otherwise (node-to-delete found & not first node)
       // nodeData = nodePtr->country;  // return the deleted data
        previousNode->nextC = nodePtr->nextC;
        delete nodePtr;
    }

    
    /*
    pWalk = ptr;
    pPrevious = nullptr;
    
    while ((pWalk != nullptr) && (pWalk->cRestaurant->getNumber() != tStreetNum))
    {
        pPrevious = pWalk;
        pWalk = pWalk->nextC;
    }
    
    if (!pWalk)
        return false;

    if (!pPrevious)
    {
        ptr = nullptr;

        delete pWalk;

    }
    else
    {
        pPrevious->nextC = pWalk->nextC;
        delete pWalk;
    }*/
    
    return true;
}

//***************************************************************************************
// Definition of getLastCollision
//
//***************************************************************************************
restaurantInfo* collisionTable::getLastCollision(collisionTable *ptr)
{
    //collisionTable *pGet;
    //restaurantInfo *r;
    
    //pGet = nullptr;
    
       // r = ptr->cRestaurant;
        //ptr = nullptr;
        return cRestaurant;



    /*
    //collisionTable *pWalk;
    collisionTable *pPre;
    
    //pWalk = ptr;
    pPre = ptr;
    
    if (ptr == nullptr)
    {
        //cout << "NULL";
        //return pPre->cRestaurant;
    }
    
    while (ptr != nullptr)
    {
        pPre = ptr;
        ptr = ptr->nextC;
        //pPre = pWalk;
        //pWalk = pWalk->nextC;
        
    }// End while
    
    
    //cout << "\n\npPre: " << pPre->cRestaurant->getNumber();
    
    return pPre->cRestaurant;*/
}


//***************************************************************************************
//
//***************************************************************************************
restaurantInfo* collisionTable::getRestaurantInfo()
{
    return cRestaurant;
}


