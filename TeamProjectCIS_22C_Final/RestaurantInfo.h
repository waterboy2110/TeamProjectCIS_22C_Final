
//***********************************************************************************************************
// Specification file for restaurantInfo class
//
// Restaurant info - street number, name, street, type, and cost
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
// X getters for all private data (to save to file) 
// - Deconstructor
//***********************************************************************************************************

#ifndef Project_3_9_RestaurantInfo_h
#define Project_3_9_RestaurantInfo_h

#include <iostream>
using namespace std;

class restaurantInfo
{
private:
    string name;            // Restaurant name
    int number;             // Street number
    string streetName;      // Street 
    string type;            // Type 
    //costType *costPtr;    // Cost
    
public:
    // Constructor
    restaurantInfo(string aName, int aNumber, string aStreet, string aType);
    
    // Restaurant info functions
    string getName() const;
    int getNumber() const;
    string getStreet() const;
    string getType() const;
    void displayRestaurant() const;
    
};// End restaurantInfo

#endif
