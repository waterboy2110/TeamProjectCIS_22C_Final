//***************************************************************************************
// Specification file for typeList class
//***************************************************************************************

#ifndef Project_3_9_TypeList_h
#define Project_3_9_TypeList_h

#include <string>
#include <iostream>
using namespace std;

class typeList
{
private:
    struct typeListNode
    {
        string restaurantType;  // Restaurant type
        typeListNode* nextType;     // Pointer to next type
    };
    
    typeListNode *typeListHead; // Pointer to the first node in type list
    typeListNode *typeListTail; // Pointer to the last node in type list
    int numType;                // Number of restaurant types

public:
    // Constructor 
    typeList();
    
    // Type list operations
    bool insertRestaurantType(string aType);
    //bool getRestaurantType(string &aRestaurant) const;
    //bool setRestaurantType(string &aType);
    //bool setNextType(typeList*);
    
};// End typeList


#endif
