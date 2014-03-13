//***********************************************************************************************************
// Implementation file for hash class
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// - Constructor so that the size is received from the ListHead
// - Add a deconstructor
// - Display restaurants as they are added?
//***********************************************************************************************************

#include "Hash.h"

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
Hash::Hash()
{
    // Dynamically allocate heap array
    hashAryPtr = new hashTable[20];
    
}// End constructor

//***********************************************************************************************************
// Deconstructor
//***********************************************************************************************************
//
//
//
//
//
//


//***********************************************************************************************************
// Definition of hashFunction
//
//***********************************************************************************************************
int Hash::hashFunction(int tNum)
{
    int sum = 0;
    string s;
    
    // Convert street number to a string
    //char *intStr = itoa(tNum);
    string str = to_string(tNum);
    
    // Convert street number string to a c-string
    char cstr[str.length()+1];
    strcpy(cstr, str.c_str());
    
    // Add each integer in street number until the end of the string
    for (int i = 0; i < str.length(); i++)
    {
        s = cstr[i];
        sum = sum + atoi(s.c_str());
    }
    
    // Return the quotient of the sum of each integer and the number of integers
    // in the string.
    return sum/str.length();
}// End hashFunction

//***********************************************************************************************************
// Definition of insertHash
//
//***********************************************************************************************************
bool Hash::insertHash(int hashNum, restaurantInfo *tRestaurant)
{
    // If there are no restaurants....
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        //cout << "Name: " << tRestaurant->getName() << endl;

        // Store the resraurant in aRestaurant
        hashAryPtr[hashNum].aRestaurant = tRestaurant;
        
        //cout << hashAryPtr[hashNum].aRestaurant->getName() << endl;
        
    }
    else    // Otherwise, there is a collision...
    {
        //cout << "Name: " << tRestaurant->getName() << endl;
        
        // Insert the restaurant in the collision table
        hashAryPtr[hashNum].aCollision->insertCollision(tRestaurant, hashAryPtr[hashNum].numRestaurants,
                                                        hashAryPtr[hashNum].aCollision);
        
        //cout << hashAryPtr[hashNum].aCollision->getRestaurantInfo()->getName();
        
    }// End if
    
    // Update number of restaurants
    hashAryPtr[hashNum].numRestaurants++;
            
    return true;
}// End insertHash

//***********************************************************************************************************
// Definition of deleteHash
//
//***********************************************************************************************************
bool Hash::deleteHash(int tStreetNum)
{
    int hashNum;
    //restaurantInfo *dPtr;
    
    hashNum = hashFunction(tStreetNum);
    
    // If there are no restaurants with the address number... 
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        cout << "\nThere is no restaurant with street number " << tStreetNum;
        return false;
    }
    
    // If there is only one restaurant with the address number...
    if(hashAryPtr[hashNum].numRestaurants == 1)
    {
        // Display restaurant information
        cout << "\n'" << hashAryPtr[hashNum].aRestaurant->getName() << "'" << " with address number "
            << hashAryPtr[hashNum].aRestaurant->getNumber() << " has been deleted.";
        
        // Delete restaurant information
        delete hashAryPtr[hashNum].aRestaurant;
        
    }
    else    // Otherwise there are more than one restaurants with the address number...
    {
        
        // If the restaurant with the address number is not in a collision table...
        // (The restaurant is stored in aRestaurant)
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == tStreetNum)
        {
            
            // Display restaurant information
            cout << "\n'" << hashAryPtr[hashNum].aRestaurant->getName() << "'" << " with address number "
                << hashAryPtr[hashNum].aRestaurant->getNumber() << " has been deleted.";
            
            // Delete restaurant information
            delete hashAryPtr[hashNum].aRestaurant;
            
            // Get the last restaurant from the collision table linked list and store in aResataurant
            // (Remove from collision table linked list and store in aRestaurant)
            hashAryPtr[hashNum].aRestaurant = hashAryPtr[hashNum].aCollision->getLastCollision(hashAryPtr[hashNum].aCollision);
            
            // Delete the last restaurant from the collision table
            hashAryPtr[hashNum].aCollision->deleteCollision(hashAryPtr[hashNum].aRestaurant->getNumber(),
                                                    hashAryPtr[hashNum].aCollision);
            
        }
        else // Otherwise, the restaurant with the address number is in the collision table
        {
            
            // Search and delete the restaurant with the address number in the collision table linked list
            hashAryPtr[hashNum].aCollision->deleteCollision(tStreetNum, hashAryPtr[hashNum].aCollision);
            
        }// End if
        
    }// End if
    
    // Update number of restaurants
    hashAryPtr[hashNum].numRestaurants--;
    
    return true;
}// End insertHash


