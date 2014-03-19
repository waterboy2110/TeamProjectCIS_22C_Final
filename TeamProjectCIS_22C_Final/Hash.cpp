//***********************************************************************************************************
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// Christina Sok, Yenni Chu, James Agua
//
//
//***********************************************************************************************************

//***********************************************************************************************************
// Implementation file for hash class
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// X Constructor so that the size is received from the ListHead
// - Add a deconstructor - may need to loop through the table and delete.
// X Display restaurants as they are added?
// X Update number of restaurants in list head when adding restaurants and deleting restaurants
//          (Done in main)
// X Fix displays to show all restaurant information (this means adding more "get" functions in restaurant
//          header file)
// X Change hash stat to the size of array from listhead (let it receive)
// X Add function: add only if the number does not already exist (unique key)
// X saveToFile to save Hash table to file
// - saving collision tables
// - remove cout debug statements
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
// Deconstructor
//***********************************************************************************************************
Hash::~Hash(){}

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
    return sum / str.length();
    
}// End hashFunction

//***********************************************************************************************************
// Definition of insertHash
//
//***********************************************************************************************************
bool Hash::insertHash(restaurantInfo *tRestaurant)
{
    int hashNum = hashFunction(tRestaurant->getNumber());
    
    // If there are no restaurants....
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        //cout << "DEBUG InsertHash Name: " << tRestaurant->getName() << endl;

        // Store the resraurant in aRestaurant
        hashAryPtr[hashNum].aRestaurant = tRestaurant;
        
        //cout << hashAryPtr[hashNum].aRestaurant->getName() << endl;
        
    }
    else    // Otherwise, there is a collision...
    {
        //cout << "DEBUG elseName: " << tRestaurant->getName() << endl;
        
        // Insert the restaurant in the collision table
        hashAryPtr[hashNum].aCollision->insertCollision(tRestaurant, hashAryPtr[hashNum].numRestaurants,
                                                        hashAryPtr[hashNum].aCollision);
        
        //cout << hashAryPtr[hashNum].aCollision->getRestaurantInfo()->getName();
        
    }// End if
    
    // Update number of restaurants 
    hashAryPtr[hashNum].numRestaurants++;
    totalRestaurants++;
            
    return true;
    
}// End insertHash

//***********************************************************************************************************
// Definition of deleteHash
//
//***********************************************************************************************************
bool Hash::deleteHash(int deleteNum, string &deleteName)
{
    int hashNum;
    //string deleteName;
    
    // Get the restaurant to be deleted's hash number
    hashNum = hashFunction(deleteNum);
    
    // Get the restaurant to be deleted's name (to delete in BST)
    deleteName = hashAryPtr[hashNum].aRestaurant->getName();
    
    // If there are no restaurants with the address number... 
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        cout << "\nThere is no restaurant with street number " << deleteNum;
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
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == deleteNum)
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
            hashAryPtr[hashNum].aCollision->deleteCollision(deleteNum, hashAryPtr[hashNum].aCollision);
            
        }// End if
        
    }// End if
    
    // Update number of restaurants
    hashAryPtr[hashNum].numRestaurants--;
    totalRestaurants--;
    
    return true;
    
}// End insertHash

//***********************************************************************************************************
// Definition of searchHash
//
//***********************************************************************************************************
bool Hash::searchHash(int searchNum)
{
    int hashNum;
    
    hashNum = hashFunction(searchNum);
    
    if (hashAryPtr[hashNum].numRestaurants == 0)
    {
        cout << "\nThere are no restaurants with street number " << searchNum;
        return false;
    }
    
    if (hashAryPtr[hashNum].numRestaurants == 1)
    {
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == searchNum)
        {
            cout << "\nRestaurant with street number " << searchNum << ":" << endl;
            hashAryPtr[hashNum].aRestaurant->displayRestaurant();
            
            return true;
        }
    }
    else
    {
        cout << "\nRestaurant(s) with street number " << searchNum << ":" << endl;
        
        // Display restaurant in hash array (aRestaurant) if it is equal to searchNum
        if (hashAryPtr[hashNum].aRestaurant->getNumber() == searchNum)
        {
            hashAryPtr[hashNum].aRestaurant->displayRestaurant();
        }
        
        // Display restaurant(s) in collision table linked list
        hashAryPtr[hashNum].aCollision->searchCollisionList(hashAryPtr[hashNum].aCollision, searchNum);
    }
    
    return true;
}

//***********************************************************************************************************
// Definition of hashStatistics
// Determines the number of collision nodes for each table node
// and accumilates that data. Finds the longest list (LL)
// PRE - NONE
// Post - Determines the load factor (number of collisions / total objects)
// and displays the data.
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
    
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants in the hash array.";
        cout << "\nCannot compute statistics.";
        
        return;
    }

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
    dis = noCollision;
        
    cout << "\nLoad factor: " << setprecision(1) << dis/totalRestaurants << "%";
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
//
//***********************************************************************************************************
bool Hash::addHash(int addNum, restaurantInfo *addRestaurant)
{
    int addHashNum = hashFunction(addNum);
        
    if (hashAryPtr[addHashNum].numRestaurants == 0)
    {
        hashAryPtr[addHashNum].aRestaurant = addRestaurant;
        return true;
    }
    else
    {
        if (hashAryPtr[addHashNum].aRestaurant->getNumber() == addNum)
        {
            cout << "\nA restaurant with address number " << addNum << " already exists.";
            return false;
        }
        else
        {
            if (hashAryPtr[addHashNum].aCollision->searchForAdd(hashAryPtr[addHashNum].aCollision, addNum))
            {
                hashAryPtr[addHashNum].aCollision->insertCollision(addRestaurant, addHashNum, hashAryPtr[addHashNum].aCollision);
                cout << "\nRestaurant with address number " << addNum << " has been added.";
                return true;
            }
            else
            {
                cout << "\nA restaurant with address number " << addNum << " already exists.";
                return false;
            }
        }

    }
}

//***********************************************************************************************************
// Definition of printHashTableSequence
//
//***********************************************************************************************************
void Hash::printHashTableSequence() const
{
    cout << endl;
    cout << "\n=========================== H - L I S T ===========================";
    cout << "\n========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========\n\n";
    
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants to display.";
        return;
    }
    
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAryPtr[i].numRestaurants > 0)
        {
            hashAryPtr[i].aRestaurant->displayRestaurant();
        }
        
        if (hashAryPtr[i].numRestaurants > 1)
        {
            hashAryPtr[i].aCollision->displayCollisionList(hashAryPtr[i].aCollision);
        }
    }
    
    cout << "\n===================================================================\n";
}


//**************************************************
// Definition of function saveToFile.
// Writes to file from the hash table.
//**************************************************
bool Hash::saveToFile()
{
    ofstream outFile;
    string fileName ="RestaurantsOutfile.txt";
    bool success = true;
    
    // Open file to write, if unable, display error and exit with false
    outFile.open(fileName);
    if (!outFile)
    {
        cout << "Error opening " << fileName << "!\n";
        return false;
    }
    
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAryPtr[i].numRestaurants > 0)
        {
            outFile << hashAryPtr[i].aRestaurant->getName();
            outFile << to_string(hashAryPtr[i].aRestaurant->getNumber()) << endl;
            outFile << hashAryPtr[i].aRestaurant->getStreet();
            outFile << hashAryPtr[i].aRestaurant->getType();

        }
        
        if (hashAryPtr[i].numRestaurants > 1)
        {
            cout << "DEBUG in saveToFile: " << hashAryPtr[i].numRestaurants << endl;
            //cout << hashAryPtr[i].aCollision->getNextCollision()->getRestaurantInfo() << endl;
           // while(hashAryPtr[i].aCollision->getNextCollision() != NULL)
            {
            outFile << hashAryPtr[i].aCollision->getRestaurantInfo()->getName();
            outFile << to_string(hashAryPtr[i].aCollision->getRestaurantInfo()->getNumber()) << endl;
            outFile << hashAryPtr[i].aCollision->getRestaurantInfo()->getStreet();
            outFile << hashAryPtr[i].aCollision->getRestaurantInfo()->getType();
            }
            
            /*
             // Insert the restaurant in the collision table
             hashAryPtr[hashNum].aCollision->insertCollision(tRestaurant, hashAryPtr[hashNum].numRestaurants,
             hashAryPtr[hashNum].aCollision);
             */
        }
    }

    outFile.close();

    if (!success)
        return false;

    return true;
}


//***********************************************************************************************************
// Definition of printInKeySequence
//
//***********************************************************************************************************
void Hash::printInKeySequence() const
{
    int current;
    int walk;
    int temp;
    
    cout << endl;
    cout << "\n=========================== K - L I S T ===========================";
    cout << "\n======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========\n\n";
    
    if (totalRestaurants == 0)
    {
        cout << "\nThere are no restaurants to display.";
        return;
    }
    
    hashTable *tempArray = new hashTable[totalRestaurants];
    
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAryPtr[i].numRestaurants > 0)
        {
            tempArray[i].aRestaurant = hashAryPtr[i].aRestaurant;
        }
        
        if (hashAryPtr[i].numRestaurants > 1)
        {
            // Call collision to return restaurant
        }
        
    }
    
    /**
    for (current = 1; current < totalRestaurants; current++)
    {
        temp = hashAryPtr[current].aRestaurant->getNumber();
        walk = current-1;
        
        while (walk >= 0 && temp < hashAryPtr[walk].aRestaurant->getNumber())
        {
            hashAryPtr[walk+1] = 
        }
    }**/
    
    delete [] tempArray;
    
    cout << "\n===================================================================\n";
}


