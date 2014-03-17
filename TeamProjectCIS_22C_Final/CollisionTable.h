//***************************************************************************************
// Specification file for collisionTable class
//***************************************************************************************

#ifndef Project_3_9_CollisionTable_h
#define Project_3_9_CollisionTable_h

//#include "Hash.h"
#include "RestaurantInfo.h"

/*
struct collisionNode
{
    restaurantInfo* cRestaurant;    // Pointer to restaurant info
    collisionNode* nextC;          // Pointer to next restaurant info
};*/

class collisionTable
{
private:
    restaurantInfo *cRestaurant;    // Pointer to restaurant info
    collisionTable *nextC;          // Pointer to next restaurant info    
    
public:
    // Constructors
    collisionTable();
    collisionTable(restaurantInfo *collisionPtr);
    
    // Collision table operations
    bool insertCollision(restaurantInfo *collisionPtr, int hashNum, collisionTable *&ptr);
    bool deleteCollision(int tStreetNum, collisionTable *ptr);
    restaurantInfo* getLastCollision(collisionTable *ptr);
    restaurantInfo* getRestaurantInfo();
    bool searchCollisionList(collisionTable *ptr, int searchNum);
    bool searchForAdd(collisionTable *ptr, int addNum);
    void displayCollisionList(collisionTable *ptr);
    
    //bool getNextC(collisionTable* nextC)const;
    //bool setNextC(collisionTable*);
    
};// End collisionTable

#endif
