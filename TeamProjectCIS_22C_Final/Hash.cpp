//***********************************************************************************************************
// Implementation file for hash class
//***********************************************************************************************************

#include "Hash.h"

//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
Hash::Hash(int aSize)
{
    // Dynamically allocate heap array
    hashAryPtr = new hashTable[aSize];
    
    totalRestaurants = 0;
    
}// End constructor

//***********************************************************************************************************
// Definition of destroyHash
//
// This function deletes all of the restaurant pointers stored in the hash array.
//***********************************************************************************************************
void Hash::destroyHash()
{
    string tempName = "";
    int tempNum;
    
    for (int i = 0; i < hashSize; i++)
    {
        // If there are restaurant(s) in table...
        if (hashAryPtr[i].numRestaurants > 0)
        {
            // If there is only one restaurant
            if (hashAryPtr[i].numRestaurants == 1)
            {
                delete hashAryPtr[i].aRestaurant;
                hashAryPtr[i].aRestaurant = nullptr;
            }
            else
            {
                delete hashAryPtr[i].aRestaurant;
                hashAryPtr[i].aRestaurant = nullptr;
                
                hashAryPtr[i].numRestaurants--;
                
                // Delete all restaurants in collision
                while (hashAryPtr[i].numRestaurants > 0)
                {
                    hashAryPtr[i].aCollision->deleteCollision(hashAryPtr[i].aCollision->getFirstCollision()->getNumber(), hashAryPtr[i].aCollision, tempName, tempNum);
                    
                }// End while
                
                hashAryPtr[i].aCollision = nullptr;
                
            }// End if

        }// End if
        
    }// End for
    
    delete [] hashAryPtr;
    
}// End destroyHash

//***********************************************************************************************************
// Definition of hashFunction
//
// hashFunction receives an integer and returns a corresponding hash number index.
//***********************************************************************************************************
int Hash::hashFunction(int tNum)
{
    string s;
    int sum = 0;
    int subSum =0;
    string sumString;
    string subSumString;
    //int length;
    string temp;
    string t;
    
    // Convert street number to a string
    string str = to_string(tNum);
    
    // Convert street number string to a c-string
    char cstr[str.length()+1];
    strcpy(cstr, str.c_str());
    
    // Add each integer in street number until the end of the string
    for (int i = 0; i < str.length(); i++)
    {
        s = cstr[i];
        sum = sum + atoi(s.c_str());
        
        if (i == 0 || i == 2)
        {
            subSum = subSum + atoi(s.c_str());
        }

    }
    
    // Convert sums to strings
    sumString = to_string(sum);
    subSumString = to_string(subSum);
    
    if (sumString.length() == 1)
    {
        if (sum/2 == 0)
        {
            sumString.append(sumString);
            return atoi(sumString.c_str());
        }
        else
        {
            if (subSumString.length() == 1)
            {
                sumString.append(subSumString);
                return atoi(sumString.c_str());
            }
            
            subSumString.append(subSumString);
            return atoi(sumString.c_str());
        }
    }
    
    return (sum+subSum)/2;
    
}// End hashFunction

//***********************************************************************************************************
// Definition of insertHash
//
// This function receives a pointer to a restaurant object to be inserted to the hash array. 
//***********************************************************************************************************
bool Hash::insertHash(restaurantInfo *tRestaurant)
{
    // Get hash index 
    int hashNum = hashFunction(tRestaurant->getNumber());
    
    // If there are no restaurants....
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        // Store the resraurant in aRestaurant
        hashAryPtr[hashNum].aRestaurant = tRestaurant;
                
    }
    else    // Otherwise, there is a collision...
    {        
        // Insert the restaurant in the collision table
        hashAryPtr[hashNum].aCollision->insertCollision(tRestaurant, hashAryPtr[hashNum].aCollision);
                
    }// End if
    
    // Update number of restaurants in hash table and hash array
    hashAryPtr[hashNum].numRestaurants++;
    totalRestaurants++;
            
    return true;
}// End insertHash

//***********************************************************************************************************
// Definition of deleteHash
//
// This function receives an integer of the restaurant to delete and will return the name of the restaurant
// to be deleted's name by reference. It accounts for whether there are no restaurants, one restaurant, or
// more than one restaurants in the table. If the restaurant to be deleted is store in the member variable
// aRestaurant, the function will get a restaurant object from the collision table and store it in aRestaurant
// (that is if there are restaurants in the collision table).
//***********************************************************************************************************
bool Hash::deleteHash(int deleteNum, string &deleteName)
{
    int hashNum;
    bool status;
    string tempName;
    int tempNumber;
    
    // Get the restaurant to be deleted's hash number
    hashNum = hashFunction(deleteNum);
    
    // Get the restaurant to be deleted's name (to delete in BST)
    deleteName = hashAryPtr[hashNum].aRestaurant->getName();
    
    // If there are no restaurants... 
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        cout << "\nThere is no restaurant with street number " << deleteNum;
        return false;
    }
    
    // If there is only one restaurant in table...
    if(hashAryPtr[hashNum].numRestaurants == 1)
    {
        // If the restaurant in table is the restaurant to be deleted...
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == deleteNum)
        {
            // Display restaurant information
            cout << "\n'" << hashAryPtr[hashNum].aRestaurant->getName() << "'" << " with address number "
            << hashAryPtr[hashNum].aRestaurant->getNumber() << " has been deleted. (ONE)";
            
            // Delete restaurant information
            delete hashAryPtr[hashNum].aRestaurant;
            
            // Reset pointer
            hashAryPtr[hashNum].aRestaurant = nullptr;

            // Update counters in table and in hash array
            hashAryPtr[hashNum].numRestaurants--;
            totalRestaurants--;
            
            return true;
        }// End if
        
        return false;
    }
    else    // Otherwise there are more than one restaurants with the hash number...
    {
        
        // If the restaurant with the address number is not in a collision table...
        // (The restaurant is stored in aRestaurant)
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == deleteNum)
        {
            
            // Display restaurant information
            cout << "\n'" << hashAryPtr[hashNum].aRestaurant->getName() << "'" << " with address number "
                << hashAryPtr[hashNum].aRestaurant->getNumber() << " has been deleted. (MORE THAN ONE)";
            
            // Delete restaurant information
            delete hashAryPtr[hashNum].aRestaurant;
            
            if (hashAryPtr[hashNum].numRestaurants >=2)
            {
                // Get the first restaurant from the collision table linked list and store in aResataurant
                // (Remove from collision table linked list and store in aRestaurant)
                hashAryPtr[hashNum].aRestaurant = hashAryPtr[hashNum].aCollision->getFirstCollision();
                
                // Delete the first restaurant from the collision table
                hashAryPtr[hashNum].aCollision->deleteCollision(hashAryPtr[hashNum].aRestaurant->getNumber(),
                                                                hashAryPtr[hashNum].aCollision, tempName, tempNumber);
            }
            else
            {
                hashAryPtr[hashNum].aRestaurant = nullptr;
                
            }// End if
                        
            // Update counters in hash table and hash array
            hashAryPtr[hashNum].numRestaurants--;
            totalRestaurants--;
            
            return true;
                        
        }
        else // Otherwise, the restaurant with the address number is in the collision table
        {
            // Search and delete the restaurant with the address number in the collision table linked list
            status = hashAryPtr[hashNum].aCollision->deleteCollision(deleteNum, hashAryPtr[hashNum].aCollision,
                                                                     tempName, tempNumber);
            
            // If the restaurant was found in the collision table...
            if (status == true)
            {
                cout << "\n'" << tempName << "'" << " with address number "
                << tempNumber << " has been deleted. (COLLISION)";
                
                // Update counters for table and array
                hashAryPtr[hashNum].numRestaurants--;
                totalRestaurants--;
                
                return true;
            }
            else    // Otherwise it is not in the collision table
            {
                cout << "\nThe restaurant with address number " << deleteNum << " was not found.";
                return false;
                
            }// End if
            
        }// End if
        
    }// End if
    
    return true;
}// End insertHash

//***********************************************************************************************************
// Definition of searchHash
//
// This function receives a restaurant number to be searched for. If the restaurant was not found, the user
// will be prompted and the function will return. Otherwise, the function will display restaurant information
// accordingly and return.
//***********************************************************************************************************
bool Hash::searchHash(int searchNum)
{
    int hashNum;
    
    // Get hash index
    hashNum = hashFunction(searchNum);
    
    // If there are no restaurants in the table...
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        cout << "\nThere are no restaurants with street number " << searchNum;
        return false;
    }
    
    // If there is only one restaurant in the table...
    if (hashAryPtr[hashNum].numRestaurants == 1)
    {
        // If the restaurant in the table is the restaurant searched for...
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == searchNum)
        {
            cout << "\nRestaurant with street number " << searchNum << ":" << endl;
            hashAryPtr[hashNum].aRestaurant->displayRestaurant();
            
            return true;
        }// End if
    }
    else    // Otherwise, there is more than one restaurant in the table
    {
        // Display restaurant in hash array (aRestaurant) if it is equal to searchNum
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == searchNum)
        {
            cout << "\nRestaurant with street number " << searchNum << ":" << endl;
            hashAryPtr[hashNum].aRestaurant->displayRestaurant();
        }
        else    // Otherwise, the restaurant may be in the collision table (search collision table)
        {
            // If the restaurant is in the collision table
            if (hashAryPtr[hashNum].aCollision->searchCollisionList(hashAryPtr[hashNum].aCollision, searchNum))
            {
                return true;
            }// End if
            
        }// End if
        
    }// End if
        
    return false; // Restaurant was not found
}// End searchHash

//***********************************************************************************************************
// Definition of searchForDelete
//
// This function receives an address number of the restaurant to delete. If the restaurant with the address
// number exists, the function will return true and return the restaurant by reference. If no such
// restaurant was found, the function will return false and nullptr. 
//***********************************************************************************************************
bool Hash::searchForDelete(int searchNum, restaurantInfo *&value)
{
    bool status;
    restaurantInfo *searchR;
    
    // Get hash index
    int tempHashNum = hashFunction(searchNum);
    
    // If there is only one restaurant in the hash table and it's address number is equal to the number to delete...
    if (hashAryPtr[tempHashNum].numRestaurants == 1 && hashAryPtr[tempHashNum].aRestaurant->getNumber() == searchNum)
    {
        value = hashAryPtr[tempHashNum].aRestaurant;
        return true;
    }
    
    // If the restaurant in the hash table and it's address number is equal to the number to delete...
    if (hashAryPtr[tempHashNum].aRestaurant->getNumber() == searchNum)
    {
        value = hashAryPtr[tempHashNum].aRestaurant;
        return true;
    }
    
    // Otherwise, the restaurant with the number to delete may be in the collision table
    // Search collision table
    searchR = hashAryPtr[tempHashNum].aCollision->searchForDelete(hashAryPtr[tempHashNum].aCollision, searchNum, status);
    
    // If the restaurant was found...
    if (status == true)
    {
        value = searchR;
        return true;
    }// End if
    
    return false;
}// End searchForDelete

//***********************************************************************************************************
// Definition of hashStatistics
//
// This function calculates the load factor as well as displays the number of nodes in the longest linked-list
// and the average number of nodes in the linked-list.
//***********************************************************************************************************
void Hash::hashStatistics()
{
    int noCollision = 0;
    int longestLL = 0;  // Longest linked-list
    int numNodes = 0;   // Number of nodes in linked-list
    int countLL = 0;    // To calculate average number of nodes in linked-list
    double dis;
    
    cout << endl;
    cout << "\n================== H A S H   S T A T I S T I C S ==================\n";
    
    // If there are no restaurants (no hash stats)
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants in the hash array.";
        cout << "\nCannot compute statistics.";
        
        return;
    }// End if

    // Traverse array to get information to calculate hash statistics
    for (int i = 0; i < 20; i ++)
    {
        if (hashAryPtr[i].numRestaurants == 1)
        {
            noCollision++;
        }
        else
        {
            if (hashAryPtr[i].numRestaurants > longestLL)
            {
                longestLL = hashAryPtr[i].numRestaurants - 1;
                
            }
            
            if (hashAryPtr[i].numRestaurants > 1)
            {
                numNodes += hashAryPtr[i].numRestaurants - 1;
                countLL++;
            }
        }
        
    }
    
    // Switch to double
    dis = totalRestaurants;
        
    cout << "\nLoad factor (" << totalRestaurants << "/" << hashSize << "): " << setprecision(4) << dis/hashSize * 100<< "%";
    cout << "\nLongest linked-list: " << longestLL;
    
    // Switch to double
    dis = numNodes;
    
    // Rounded up
    cout << "\nAverage number of nodes stored in linked-list: " << setprecision(1) << dis/countLL;
    
    cout << "\n\n===================================================================\n";
}

//***********************************************************************************************************
// Definition of addHash
//
// This function receives a restaurant object as well as the corresponding address number. If a restaurant
// with the address number does not already exist in the hash array, addHash will insert the object
// accordingly. 
//***********************************************************************************************************
bool Hash::addHash(int addNum, restaurantInfo *addRestaurant)
{
    // Get hash index
    int addHashNum = hashFunction(addNum);
    
    // If there are no restaurants at the index...
    if (hashAryPtr[addHashNum].numRestaurants == 0)
    {
        // Insert into aRestaurant member
        hashAryPtr[addHashNum].aRestaurant = addRestaurant;
        
        // Update number of restaurants in hash table
        hashAryPtr[addHashNum].numRestaurants++;
        
        return true;
    }
    else    // Otherwise, there is one or more restaurants in the hash table 
    {
        // If the new restaurant's address number already exists in hash table...
        // (In aRestaurant member)
        if (hashAryPtr[addHashNum].aRestaurant->getNumber() == addNum)
        {
            cout << "\nA restaurant with address number " << addNum << " already exists.";
            return false;
        }
        else
        {
            // If the new restaurant's address number does not already exist in the collision list...
            if (hashAryPtr[addHashNum].aCollision->searchForAdd(hashAryPtr[addHashNum].aCollision, addNum))
            {
                // Insert to collision table
                hashAryPtr[addHashNum].aCollision->insertCollision(addRestaurant, hashAryPtr[addHashNum].aCollision);
                
                cout << "\nRestaurant with address number " << addNum << " has been added.";
                
                // Update number of restaurants in hash table
                hashAryPtr[addHashNum].numRestaurants++;
                
                return true;
            }
            else    // Otherwise, it exists...
            {
                cout << "\nA restaurant with address number " << addNum << " already exists.";
                
                return false;
            }// End if
            
        }// End if

    }// End if
    
}// End addHash

//***********************************************************************************************************
// Definition of printHashTableSequence
//
// prinHashTableSequence prints each restaurant in the hash array in the sequence that it is in the hash array.
//***********************************************************************************************************
void Hash::printHashTableSequence() const
{
    cout << endl;
    cout << "\n=========================== H - L I S T ===========================";
    cout << "\n========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========\n\n";
    
    // If there are no restaurants to display...
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants to display.";
        return;
    }
    
    // Traverse array/collision lists and display restaurant information or
    // prompt if there is no restaurant at index
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAryPtr[i].numRestaurants == 1)
        {
            cout << "\nRestaurant(s) in Index: " << i << endl;
            hashAryPtr[i].aRestaurant->displayRestaurant();
        }
        else
        {
            
            if (hashAryPtr[i].numRestaurants > 1)
            {
                cout << "\nRestaurant(s) in Index: " << i << endl;
                hashAryPtr[i].aRestaurant->displayRestaurant();
                hashAryPtr[i].aCollision->displayCollisionList(hashAryPtr[i].aCollision);
            }
            else
            {
                cout << "\nIndex " << i << " is empty." << endl;
                
            }// End if
            
        }// End if
        
    }// End for
    
    cout << "\n===================================================================\n";

}// End printHashTableSequence

//***********************************************************************************************************
// Definition of printInKeySequence
//
// printInKeySequence creates a temporary array to store all of the restaurants in the hash array. It then
// sorts the temporary array, displays the restaurants sorted by address number, destroys the temporary array
// and returns.
//***********************************************************************************************************
void Hash::printInKeySequence()
{
    collisionTable *ptr;
    //collisionTable *ptrT;

    //restaurantInfo *tempR;
    
    int count= 0;
    int countP = 0;
    int p = 1;
    int colCount;
    
    cout << endl;
    cout << "\n=========================== K - L I S T ===========================";
    cout << "\n======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========\n\n";
    
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants to display.";
        return;
    }
    
    restaurantInfo *tempArray = new restaurantInfo[totalRestaurants];
    
    while (count < hashSize)
    {
        
        if (hashAryPtr[count].numRestaurants == 1)
        {
            tempArray[countP] = *hashAryPtr[count].aRestaurant;
            count++;
            countP++;
        }
        
        if (hashAryPtr[count].numRestaurants > 1)
        {
            tempArray[countP] = *hashAryPtr[count].aRestaurant;
            countP++;
            
            ptr = hashAryPtr[count].aCollision;
            
            colCount = 0;
            
            while (colCount < hashAryPtr[count].numRestaurants-1)
            {
                tempArray[countP] = *hashAryPtr[count].aCollision->returnRestaurant(ptr);
                
                countP++;
                colCount++;
            }
            
        }
        
        count++;
    }
    
    int current;
    int walk;
    restaurantInfo temp;
    
    for (current = 1; current < totalRestaurants; current ++)
    {
        temp = tempArray[current];
        walk = current-1;
        while (walk >= 0 && temp.getNumber() < tempArray[walk].getNumber())
        {
            tempArray[walk+1] = tempArray[walk];
            walk --;
        }
        
        tempArray[walk+1] = temp;
    }
    
    while ( p < totalRestaurants)
    {
        tempArray[p].displayRestaurant();
        p++;
    }
    
    delete [] tempArray;
    
    cout << "\n===================================================================\n";
}



