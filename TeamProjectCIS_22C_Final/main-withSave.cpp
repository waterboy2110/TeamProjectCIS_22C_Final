//***********************************************************************************************************
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// Christina Sok, Yenni Chu, James Agua    
//
//
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO ADD:
//
// - Check for cost type (valid)
// - Edit delete
// - code searchBST manager
//***********************************************************************************************************

#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include "Hash.h"
#include "ListHead.h"

// Function prototypes
bool readFile(listHead *aList);
void insertManager(listHead *aList);
void deleteManager(listHead *aList);
bool searchHashManager(listHead *aList);
bool searchBSTManager(listHead *aList);
bool writeFile(listHead *aList);
void displayMenu();
char getUserInput();
void validateUserInput(char &tUserInput);
void operationManager(listHead *aList, char tUserInput);
int checkValidStreetNum(string num);
bool saveToFile(listHead *);

int main()
{
    char input;
    
    cout << "========= R E S T A U R A N T S   I N   C U P E R T I N O =========";
    
    listHead *restaurants = new listHead(hashSize);

    readFile(restaurants);
    
    restaurants->getHashPtr()->printHashTableSequence();
    

    // Display menu
    displayMenu();
    
    // Get user's input
    input = getUserInput();
    
    // While the user does not want to quit...
    while (input != 'q')
    {
        // Call appropriate operation
        operationManager(restaurants, input);
        
        // Get user's input
        input = getUserInput();
    }

    saveToFile(restaurants);
    
    cout << "\n======================== T H A N K  Y O U =========================";
}

//***********************************************************************************************************
// Definition readFile
//
//***********************************************************************************************************
bool readFile(listHead *aList)
{
    ifstream inFile;
    string tName;       // Restaurant name
    int tStreetNum;     // Street number
    string tStreetName; // Street name
    string tType;       // Type
    string tCost;       // Cost
    
    // Open file
    inFile.open("Restaurants.txt");
    
    // If file could not be opened, display error and return false
    if (!inFile)
    {
        cout << "\nError opening Restaurants.txt!" << endl;
        return false;
    }
    else    // Otherwise, read in restaurant information
    {
        cout << "\n\nRestaurants.txt has opened successfully!" << endl;
        
        while (getline(inFile, tName))  // While not end of file get restaurant name...
        {
            // Read in customer information
            getline(inFile, tType);
            tStreetNum = atoi(tType.c_str());
            getline(inFile, tStreetName);
            getline(inFile, tType);
            getline(inFile, tCost);
            
            // Create restaurant object
            restaurantInfo *tRestPtr = new restaurantInfo(tName, tStreetNum, tStreetName, tType);
            
            // Insert new restaurant to hash and BST
            aList->getHashPtr()->insertHash(tRestPtr);
            //aList->getBSTPtr()->addNode(tRestPtr);
            
            aList->addNumRestaurants();
            
        }// End while
    }// End if
    
    // Close file
    inFile.close();
    
    return true;
}// End readFile

//***********************************************************************************************************
// Definition insertManager
//
//***********************************************************************************************************
void insertManager(listHead *aList)
{
    string tName;
    int tNumber;
    string tStreet;
    string tType;
    bool status;
    
    cout << endl;
    cout << "\n========================= I - I N S E R T =========================";
    
    // Get restaurant information from user
    cout << "\n\nEnter restaurant name: ";
    getline(cin, tName);
    cout << "\nEnter street number: ";
    getline(cin, tStreet);
    tNumber = checkValidStreetNum(tStreet); // Validate street number
    cout << "\nEnter street name: ";
    getline(cin, tStreet);
    cout << "\nEnter type: ";
    getline(cin, tType);
    //cout << "\nEnter cost: ";
    //getline(cin, tCost);
    
    // Create restaurant 
    restaurantInfo* addPtr = new restaurantInfo(tName, tNumber, tStreet, tType);
    
    // Insert hash
    status = aList->getHashPtr()->insertHash(addPtr);
    
    // If a restaurant with the entered street number does not exist
    // add to the BST. (Street number = unique). 
    if (status) 
    {
        // Insert BST
        aList->getBSTPtr()->addNode(addPtr);
        
        // Update number of restaurants in listHead (add 1)
        aList->addNumRestaurants();
        
        cout << endl << addPtr->getName() << " has been added successully!\n";
    }

    cout << "\n===================================================================\n";

    return;
}

//***********************************************************************************************************
// Definition of deleteManager
//
//***********************************************************************************************************
void deleteManager(listHead *aList)
{
    string input;
    bool status;
    char choice[2];
    
    cout << endl;
    cout << "\n========================= D - D E L E T E =========================";
    
    cout << "\n\nEnter N to delete by number or S t delete by restaurant name: ";
    getline(cin, input);
    
    // Get lowercase equivalent of user's input
    choice[0] = tolower(input[0]);
    
    // If the user wants to delete by number...
    if (choice[0] == 'n')
    {
        cout << "\nEnter the number of the restaurant to delete: ";
        getline(cin, input);
        
        // Delete from hash table
        status = aList->getHashPtr()->deleteHash(atoi(input.c_str()));
        
        if (status)
        {
            // Insert delete BST
            
            // Update number of restaurants in listHead (subtract 1)
            aList->subNumRestaurants();
        }
        else
        {
            // If the user wants to delete by name...
            if (choice[0] == 's')
            {
                cout << "\nEnter the name of the restaurant to delete: ";
                getline(cin, input);
                
                // Delete BST status = aList->getBSTPtr()->
                // If exists delete from hash
            }
            else
            {
                cout << "\nYou have entered an invalid letter.";
                
            }// End if
            
        }// End if

    }// End if

    cout << "\n===================================================================\n";
    
    return;
}// End deleteManager

//***********************************************************************************************************
// Definition of searchHashManager
//
//***********************************************************************************************************
bool searchHashManager(listHead *aList)
{
    string streetNum;
    int tempNum;
    
    cout << endl;
    cout << "\n========================== P - S E A R C H ========================";
    cout << "\n=================== ( S T R E E T   N U M B E R ) =================";
    
    cout << "\n\nEnter street number: ";
    getline(cin, streetNum);
    
    // Validate street number
    tempNum = checkValidStreetNum(streetNum);
    
    // Search hash
    aList->getHashPtr()->searchHash(atoi(streetNum.c_str()));
    
    cout << "\n===================================================================\n";
    
    return true;
}// End searchHashManager

//***********************************************************************************************************
// Definition of searchBSTManager
//
//***********************************************************************************************************
//
//
//
//
//
//
//

//***********************************************************************************************************
// Definition displayMenu
//
//***********************************************************************************************************
void displayMenu()
{
    cout << endl;
    cout << "\n============================= M E N U =============================";
    cout << "\n=  I - Insert new data                                            =";
    cout << "\n=  D - Delete data                                                =";
    cout << "\n=  P - Search using street number                                 =";
    cout << "\n=  N - Search using restaurant name                               =";
    cout << "\n=  K - List data in street number sequence                        =";
    cout << "\n=  H - List data in hash table sequence                           =";
    cout << "\n=  T - Print indented tree                                        =";
    cout << "\n=  S - Print hash statistics                                      =";
    cout << "\n=  M - Display menu                                               =";         
    cout << "\n=  Q - Quit                                                       =";
    cout << "\n===================================================================\n";

}// End displayMenu

//***********************************************************************************************************
// Definition getUserInput
//
//***********************************************************************************************************
char getUserInput()
{
    string userInput;
    
    cout << endl;
    cout << "\n======================== U S E R  I N P U T =======================";
    cout << "\n\nEnter a letter (to display menu, enter the letter 'm'): ";
    getline(cin, userInput);
    
    // Validate the user's input
    validateUserInput(userInput[0]);
    
    cout << "\n===================================================================\n";

    // Return user's input
    return userInput[0];
    
}// End getUserInput

//***********************************************************************************************************
// Definition validateUserInput
//
//***********************************************************************************************************
void validateUserInput(char &tUserInput)
{
    string userInput;
    tUserInput = tolower(tUserInput);
    
    // While the input is not valid....
    while (tUserInput != 'i' & tUserInput != 'd' & tUserInput != 'p' & tUserInput != 'n'
           & tUserInput != 'k' & tUserInput != 'h' & tUserInput != 't' & tUserInput != 's'
           & tUserInput != 'q' & tUserInput != 'm')
    {
        cout << "\nYou have entered an invalid letter.";
        cout << "\nPlease enter a letter: ";
        getline(cin, userInput);
        tUserInput = tolower(userInput[0]);
        
    }// End while
    
}// End validateUserInput

//***********************************************************************************************************
// Definition operationManager
//
//***********************************************************************************************************
void operationManager(listHead *aList, char tUserInput)
{
    if (tUserInput == 'i')
    {
        insertManager(aList);
    }
    else
    {
        if (tUserInput == 'd')
        {
            deleteManager(aList);
        }
        else
        {
            if (tUserInput == 'p')
            {
                searchHashManager(aList);
            }
            else
            {
                if (tUserInput == 'n')
                {
                    // Insert search bst manager
                }
                else
                {
                    if (tUserInput == 'k')
                    {
                        // Insert list data in street number sequence
                    }
                    else
                    {
                        if (tUserInput == 'h')
                        {
                            // Insert list data in hash table sequence
                        }
                        else
                        {
                            if (tUserInput == 't')
                            {
                                // Insert print indented tree
                            }
                            else
                            {
                                if (tUserInput == 's')
                                {
                                    // Display hash statistics
                                    aList->getHashPtr()->hashStatistics();
                                }
                                else
                                {
                                    // Otherwise, display menu
                                    displayMenu();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    return;
}// End operation manager

//***********************************************************************************************************
// Definition of checkValidStreetNum
//
//***********************************************************************************************************
int checkValidStreetNum(string num)
{
    int status;
    
    // Check for valid street number
    status = num.find_first_not_of("0123456789");
    
    // If street number is not valid
    while (status >= 0 || atoi(num.c_str()) < 0)
    {
        cout << "\nYou have entered an invalid street number.";
        cout << "\nA valid street number contains only digits and is greater than 0.";
        cout << "\nEnter street number: ";
        getline(cin, num);
        
        // Check for valid street number
        status = num.find_first_not_of("0123456789");
        
    }// End if

    return atoi(num.c_str());
}

//**************************************************
// Definition of function saveToFile.
// This function will read all the data from
// the file.
// Really should have put this in the cpp file
// but since ListNode is private I didn't have
// access. Well - I think.
//**************************************************
bool saveToFile(listHead *restaurants)
{
    cout << "DEBUG in save\n";
    ofstream outFile;
    string fileName ="Restaurants2.txt";
    bool success = true;
    
    // Open file to write, if couldn't open, display error
    // and exit with false
    outFile.open(fileName);
    if (!outFile)
    {
        cout << "Error opening " << fileName << "!\n";
        return false;
    }
    
    restaurants->getHashPtr()->printHashTableSequence();
    
    
/*
    ListNode<T> *nodePtr;  // To move through the list.
	nodePtr = sentinel;		// Position nodePtr to the sentinel.
    
    while (nodePtr)
    {
        outFile << nodePtr->value << endl;	// Write to the file.
        nodePtr = nodePtr->next;				// Move to the next node.
    }
  */  
    outFile.close();
    
    if (!success)
        return false;
    
    return true;
}