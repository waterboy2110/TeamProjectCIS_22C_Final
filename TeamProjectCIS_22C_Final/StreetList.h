//***************************************************************************************
// Specification file for streetList class
//***************************************************************************************

#ifndef Project_3_9_StreetList_h
#define Project_3_9_StreetList_h

#include <string>
#include <iostream>
using namespace std;

class streetList
{
private:
    struct streetListNode
    {
        string streetName;          // Street name
        streetListNode* nextStreet; // Pointer to the next street
    };
    
    streetListNode *streetListHead; // Pointer to first node in street list
    streetListNode *streetListTail; // Pointer to the last node in street list
    int numStreet;                  // Number of street names
    
public:
    // Constructor
    streetList();
    
    // Street list operations
    bool insertStreetName(string aStreetName);
    //string getStreetName() const;
    //bool setStreetName(string &aName);
    //bool setNextStreet(streetList*);
    
}; // End streetList


#endif
