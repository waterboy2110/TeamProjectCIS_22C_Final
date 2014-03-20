//***********************************************************************************************************
// Specification file for restaurantInfo class
//
// Restaurant info - street number, name, street, type, and cost
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// - Insert costType string
// - Change constructor for cost type 
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
    restaurantInfo();
    restaurantInfo(string aName, int aNumber, string aStreet, string aType);
    
    // Restaurant info functions
    string getName() const;
    int getNumber() const;
    void displayRestaurant() const;
    //to facilitate saving street and type to file.
    string getStreet() const;
    string getType() const;
    
};// End restaurantInfo

#endif
