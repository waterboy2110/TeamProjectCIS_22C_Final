//***************************************************************************************
// Implementation file for streetList class
//***************************************************************************************

#include "StreetList.h"

//***************************************************************************************
// Constructor
//***************************************************************************************
streetList::streetList()
{
    streetListHead = streetListTail = nullptr;
    numStreet = 0;
    
}// End constructor

//***************************************************************************************
// Definition insertStreetName
//
//***************************************************************************************
bool streetList::insertStreetName(string aStreetName)
{
    // Create a street object and store parameter
    streetListNode *insertStreet;
    insertStreet = new streetListNode;
    if (!insertStreet)
    {
        return false;
    }
    insertStreet->streetName = aStreetName;
    insertStreet->nextStreet = nullptr;
    
    if (numStreet == 0) // If the street list is empty...
    {
        // Update pointers 
        streetListHead = streetListTail = insertStreet;
    }
    else    // Otherwise, the street list is not empty
    {
        // Store new street at the end of the list
        streetListTail->nextStreet = insertStreet;
        
        // Update tail pointer
        streetListTail = insertStreet;

    }// End if
    
    // Update number of streets
    numStreet++;
    
    return true;
}// End insertStreetName


