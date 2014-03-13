//***************************************************************************************
// Implementation file for typeList class
//***************************************************************************************

#include "TypeList.h"

//***************************************************************************************
// Constructor
//***************************************************************************************
typeList::typeList()
{
    typeListHead = typeListTail = nullptr;
    numType = 0;
    
}// End constructor

//***************************************************************************************
// Definition insertRestaurantType
//
//***************************************************************************************
bool typeList::insertRestaurantType(string aType)
{
    // Create a type object and store parameter
    typeListNode *insertType;
    insertType = new typeListNode;
    if (!insertType)
    {
        return false;
    }
    insertType->restaurantType = aType;
    insertType->nextType = nullptr;
    
    if (numType == 0) // If the type list is empty...
    {
        // Update pointers
        typeListHead = typeListTail = insertType;
    }
    else    // Otherwise, the type list is not empty
    {
        // Store new type at the end of the list
        typeListTail->nextType = insertType;
        
        // Update tail pointer
        typeListTail = insertType;
        
    }// End if
    
    // Update number of types
    numType++;
    
    return true;
}