//***********************************************************************************************************
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// Christina Sok, Yenni Chu, James Agua
//
//
//***********************************************************************************************************

//***********************************************************************************************************
// Specification file for hash class
//***********************************************************************************************************

#ifndef Project_3_9_Hash_h
#define Project_3_9_Hash_h

#include <string>
#include <iostream>
#include <iomanip>
#include "CollisionTable.h"
#include "RestaurantInfo.h"
using namespace std;

#define nullptr 0
#define hashSize 53

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
    int totalRestaurants;
    
public:
    // Constructor
    Hash(int aSize);
    
    // Deconstructor
    ~Hash();
    
    // Hash operations
    int hashFunction(int tNum);
    bool insertHash(restaurantInfo *tRestaruant);
    bool deleteHash(int deleteNum, string &deleteName);
    bool searchHash(int searchNum);
    void hashStatistics();
    bool addHash(int addNum, restaurantInfo *addRestaruant);
    void printHashTableSequence() const;
    void printInKeySequence() const;
    int getTotalRestaurants(){return totalRestaurants;}
};

#endif

