//***********************************************************************************************************
// Implementation file for CollisionTable class
//***********************************************************************************************************

#include "CollisionTable.h"

//***********************************************************************************************************
// Default constructor
//***********************************************************************************************************
collisionTable::collisionTable()
{
    cRestaurant = nullptr;
    nextC = nullptr;
    
}// End default constructor

//***********************************************************************************************************
// Definition insertCollision
//
// insertCollision receives a restaurant object that is to be inserted as well as a pointer to the
// collision linked-list to be inserted. It will then insert the restaurant accordingly. 
//***********************************************************************************************************
bool collisionTable::insertCollision(restaurantInfo *collisionPtr, collisionTable *&ptr)
{
    collisionTable *newNode;             // A new node
    collisionTable *nodePtr;             // To traverse the list
    collisionTable *previousNode;       // The previous node
    
    newNode = new collisionTable;
    newNode->cRestaurant = collisionPtr;
    
    nodePtr = ptr;
    
    previousNode = nullptr;
    
    while (nodePtr != nullptr)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->nextC;
    }
    
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

//***********************************************************************************************************
// Definition of deleteCollision
//
// deleteCollision receives a restaurant's address number and a pointer to the apprpriate collision table.
// If the restaurant to be deleted is found, it will return by referene the restaurant's name and number and
// return true. If no such restaurant was found, the function will return false.
//***********************************************************************************************************
bool collisionTable::deleteCollision(int tStreetNum, collisionTable *&ptr, string &tempName, int &tempNumber)
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
        tempNumber = nodePtr->cRestaurant->getNumber();
        tempName = nodePtr->cRestaurant->getName();

        ptr = ptr->nextC;
        
        delete nodePtr;
        
        return true;
    }
    else
    {
        // otherwise (node-to-delete found & not first node)
       // nodeData = nodePtr->country;  // return the deleted data
        
        tempNumber = nodePtr->cRestaurant->getNumber();
        tempName = nodePtr->cRestaurant->getName();
        
        previousNode->nextC = nodePtr->nextC;
        delete nodePtr;
    }

    return true;
}

//***********************************************************************************************************
// Definition of getFirstCollision
//
// This function returns the first collision in the collision linked-list.
//***********************************************************************************************************
restaurantInfo* collisionTable::getFirstCollision()
{
    return cRestaurant;
}

//***********************************************************************************************************
// Definition of getRestaurantInfo
//
// This function returns the restaurant information.
//***********************************************************************************************************
restaurantInfo* collisionTable::getRestaurantInfo()
{
    return cRestaurant;
}

//***********************************************************************************************************
// Definition of displayCollisionList
//
// This function displays all of the restaurant infomration stored in the collision list.
//***********************************************************************************************************
bool collisionTable::searchCollisionList(collisionTable *ptr, int searchNum)
{
    collisionTable *pWalk;
    pWalk = ptr;
    
    while (ptr != nullptr)
    {
        if (ptr->cRestaurant->getNumber() == searchNum)
        {
            ptr->cRestaurant->displayRestaurant();
            
            return true;
        }
        
        ptr = ptr->nextC;
    }
    
    return false;
}

//***********************************************************************************************************
// Definition of searchForAdd
//
// This function searches the collision list to see if the restaurant with the received address number
// already exists in the collision table. If it does, the function will return false. If it doens't the
// function will return true;
//***********************************************************************************************************
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

//***********************************************************************************************************
// Definition of displayCollisionList
//
// This function displays the restaurants stored in the collision list received.
//***********************************************************************************************************
void collisionTable::displayCollisionList(collisionTable *ptr)
{
    while (ptr != nullptr)
    {
        ptr->cRestaurant->displayRestaurant();
        ptr = ptr->nextC;
    }
}

//***********************************************************************************************************
// Definition of returnRestaurant
//
// This function returns the restaurant in the collision list received. 
//***********************************************************************************************************
restaurantInfo* collisionTable::returnRestaurant(collisionTable *&ptr)
{
    restaurantInfo *value;
    
    value = ptr->cRestaurant;
    
    ptr = ptr->nextC;
    
    return value;
}

//***********************************************************************************************************
// Definition of searchDelete
//
// This function receives a pointer to a collision list as well as an address number. It then searches the
// collision list for the restaurant number received. If such a restaurant exists, the function will return
// a pointer to the restaurant found and return by reference true. If no such restaurant exists, the function
// will return null pointer and return by reference false.
//***********************************************************************************************************
restaurantInfo* collisionTable::searchForDelete(collisionTable *ptr, int searchNum, bool &status)
{
    while (ptr != nullptr)
    {
        if (ptr->cRestaurant->getNumber() == searchNum)
        {
            status = true;
            return ptr->cRestaurant;
        }
        
        ptr = ptr->nextC;
    }

    status = false;
    
    return nullptr;
}

