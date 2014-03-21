//***********************************************************************************************************
// Specification file for collisionTable class
//***********************************************************************************************************

#ifndef Project_3_9_CollisionTable_h
#define Project_3_9_CollisionTable_h

//#include "Hash.h"
#include "RestaurantInfo.h"

class collisionTable
{
private:
    restaurantInfo *cRestaurant;    // Pointer to restaurant info
    collisionTable *nextC;          // Pointer to next restaurant info    
    
public:
    // Constructor
    collisionTable();
    
    // Collision table operations
    bool insertCollision(restaurantInfo *collisionPtr, collisionTable *&ptr);
    bool deleteCollision(int tStreetNum, collisionTable *&ptr, string &tempName, int &tempNumber);
    restaurantInfo* getFirstCollision();
    restaurantInfo* getRestaurantInfo();
    bool searchCollisionList(collisionTable *ptr, int searchNum);
    bool searchForAdd(collisionTable *ptr, int addNum);
    void displayCollisionList(collisionTable *ptr);
    restaurantInfo* returnRestaurant(collisionTable *&ptr);
    restaurantInfo* searchForDelete(collisionTable *ptr, int searchNum, bool &status);
    
};// End collisionTable

#endif
