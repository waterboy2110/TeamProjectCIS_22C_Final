//***************************************************************************************
// Implementation file for class restaurantInfo
//***************************************************************************************

#include "RestaurantInfo.h"

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

//***************************************************************************************
// Definition of displayRestaurant
//
//***************************************************************************************
void restaurantInfo::displayRestaurant() const
{
    cout << "      - " << name << " " << number << " " << streetName << " " << type << endl;
    
}// End displayRestaurant


