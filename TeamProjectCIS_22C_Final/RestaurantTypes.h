//**************************************************************************************************
// Specification file for restaurant types
//**************************************************************************************************

#ifndef Project_RestaurantTypes_h
#define Project_RestaurantTypes_h

#include <iostream>
#include <string>
using namespace std;

//********************************************************
// List of restaurant types
//********************************************************
class typeList
{
private:
    string restaurantType;  // Restaurant type
    typeList* nextType;     // Pointer to next type
public:
    bool getRestaurantType(string &aRestaurant) const;
    bool setRestaurantType(string &aType);
    bool setNextType(typeList*);
    
};// End typeList

#endif
