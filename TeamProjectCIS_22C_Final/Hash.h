//**************************************************************************************************
// Specification file for hash table
//**************************************************************************************************

#ifndef Project_Hash_h
#define Project_Hash_h

#include "CollisionTable.h"
#include "RestaurantInfo.h"

//********************************************************
// Hash table
// For array of hash tables
//********************************************************
class hashTable
{
private:
    //restaurantInfo* aRestaurant;    // Pointer to a restaurant
    int numRestaurants;             // Number of restaurants in hash table
    //collisionTable* aCollision;     // Pointer to collision table
    
public:
    int hashFunction(int tNum);
    bool search();
    bool getnumRestaurants(int aNumRestaurants);
    //bool getcollisionTable (collisionTable* aCollision);
    
};// End hashTable

#endif

