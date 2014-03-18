//***********************************************************************************************************
// Implementation file for class restaurantInfo
//***********************************************************************************************************

#include "RestaurantInfo.h"

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
restaurantInfo::restaurantInfo(string aName, int aNumber, string aStreet, string aType)
{
    name = aName;
    number = aNumber;
    streetName = aStreet;
    type = aType;
    
}// End constructor

//***********************************************************************************************************
// Definition getName
//
//***********************************************************************************************************
string restaurantInfo::getName() const
{
    return name;
    
}// End getName

//***********************************************************************************************************
// Definition getNumber
//
//***********************************************************************************************************
int restaurantInfo::getNumber() const
{
    return number;
    
}// End getNumber

//***********************************************************************************************************
// Definition of getStreet
//***********************************************************************************************************
string restaurantInfo::getStreet() const
{
    return streetName;
}

//***********************************************************************************************************
// Definition of getType
//***********************************************************************************************************
string restaurantInfo::getType() const
{
    return type;
}
//***********************************************************************************************************
// Definition of displayRestaurant
//
//***********************************************************************************************************
void restaurantInfo::displayRestaurant() const
{
    cout << "      - " << name << endl;
    cout << "        " << number << " " << streetName << endl;
    cout << "        " << type << endl;
    
}// End displayRestaurant


