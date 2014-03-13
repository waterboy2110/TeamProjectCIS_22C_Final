//***************************************************************************************
// Implementation file for class restaurantInfo
//***************************************************************************************

#include "RestaurantInfo.h"

/*    restaurantInfo(string aName, int aNumber, streetList *aStreetPtr, typeList *aTypePtr);
 
 // Restaurant info functions
 bool getName(string &aName) const;
 bool getNumber(string &aNumber) const;*/

//***************************************************************************************
// Constructor
//***************************************************************************************
restaurantInfo::restaurantInfo(string aName, int aNumber, string aStreet, string aType)
{
    name = aName;
    number = aNumber;
    streetName = aStreet;
    type = aType;
    
}// End constructor

//***************************************************************************************
// Definition getName
//
//***************************************************************************************
string restaurantInfo::getName() const
{
    return name;
    
}// End getName

//***************************************************************************************
// Definition getNumber
//
//***************************************************************************************
int restaurantInfo::getNumber() const
{
    return number;
    
}// End getNumber