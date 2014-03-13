//***************************************************************************************
// Specification file for restaurantInfo class
//
// Restaurant info - street number, name, street, type, and cost
//***************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// - Insert costType string
// - Change constructor for cost type 
// - Deconstructor
//***********************************************************************************************************

#ifndef Project_3_9_RestaurantInfo_h
#define Project_3_9_RestaurantInfo_h

#include "StreetList.h"
#include "TypeList.h"

//********************************************************
// Restaurant info - Street number, name, street, type,
// and cost
//********************************************************
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
    
};// End restaurantInfo

#endif
