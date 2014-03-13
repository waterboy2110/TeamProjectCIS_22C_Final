//***********************************************************************************************************
// Specification file for hash class
//***********************************************************************************************************

#ifndef Project_3_9_Hash_h
#define Project_3_9_Hash_h

#include <string>
#include <iostream>
#include "CollisionTable.h"
#include "RestaurantInfo.h"
using namespace std;

#define nullptr 0

struct hashTable
{
    restaurantInfo *aRestaurant = nullptr;    // Pointer to a restaurant
    int numRestaurants = 0;                   // Number of restaurants in hash table
    collisionTable *aCollision = nullptr;     // Pointer to collision table
};

class Hash
{
private:
    hashTable *hashAryPtr;
    
public:
    // Constructor
    Hash();
    
    // Deconstructor
    //~Hash();
    
    // Hash operations
    int hashFunction(int tNum);
    bool insertHash(int hashNum, restaurantInfo *tRestaruant);
    bool searchHash();
    bool deleteHash(int tStreetNum);

};

#endif

