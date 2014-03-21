//***********************************************************************************************************
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// Christina Sok, Yenni Chu, James Agua    
//
// This program processes Restaurants.txt using a hash table and a binary search tree. After reading in each
// restaurant's name (secondary key), street number (unique key), street name, and type and inserting them
// into the hash table and binary search tree, the program will be able to process a series of commands. These
// commands include searching by name, searching by street number, inserting a new restaurant, deleting
// a restaurant by address number, deleting restaurant(s) by name, printing an indented list, printing in
// hash table sequence, printing in sorted key sequence, displaying hash statistics, and saving to an output
// file. Once the user quits the program, the updated restaurant list will be automatically saved to an output
// file.
//***********************************************************************************************************

//***********************************************************************************************************
// THINGS TO CHANGE:
//
// GENERAL
// - (?) UML Needed?
//
// MAIN
// - (?) Should we add two delete functions for delete manager to call? (deleteByName and deleteByNumber)
//
// HASH
// - Check hash stats
// - Check display in order     ***** FIX FIRST (AT INDEX 0, IT DOESN'T WORK) ******
//
// BST
// X Add deconstructor in BST
// - Need deconstructor or only destroy (so that it calls in listhead)
//
// LISTHEAD
// X Add deconstructor       
//
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
bool searchBSTManager(listHead *aList);

int main()
{
    char input;
    bool fileStatus;
    
    cout << "========= R E S T A U R A N T S   I N   C U P E R T I N O =========\n";
    
    listHead *restaurants = new listHead(hashSize);

    fileStatus = readFile(restaurants);
    
    // If the file was opened successfully...
    if (fileStatus)
    {
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
            
        }// End while
        
        // Save to file on exit
        if(!restaurants->getBSTPtr()->saveToFile( restaurants->getBSTPtr()->getroot()))
        {
            cout << "\n\nSave to file failed\n";
            
        }// End if
    }// End if
          
    cout << "\n======================== T H A N K  Y O U =========================";
    
    delete restaurants;
    
    restaurants->getBSTPtr()->printIndentedList(restaurants->getBSTPtr()->getroot(), 0);
    
    cout << "\nYA";
    
    //restaurants->getHashPtr()->printInKeySequence();
    
    cout << "\nOk";
}

//***********************************************************************************************************
// Definition readFile
//
// readFile reads in restaurant information from Restaurants.txt, creates a restaurant object, and stores
// the objects in the hash array and binary search tree.
//***********************************************************************************************************
bool readFile(listHead *aList)
{
    ifstream inFile;
    string tName;       // Restaurant name
    int tStreetNum;     // Street number
    string tStreetName; // Street name
    string tType;       // Type
    
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
        while (getline(inFile, tName))  // While not end of file get restaurant name...
        {
            // Read in customer information
            getline(inFile, tType);
            tStreetNum = atoi(tType.c_str());
            getline(inFile, tStreetName);
            getline(inFile, tType);
            
            // Create restaurant object
            restaurantInfo *tRestPtr = new restaurantInfo(tName, tStreetNum, tStreetName, tType);
                        
            // Insert new restaurant to hash and BST
            aList->getHashPtr()->insertHash(tRestPtr);
            aList->getBSTPtr()->addNode(tRestPtr);
            
            // Update number of restaurants in listHead
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
// insertManager prompts the user for the restaurant to be inserted's name, street number, street name, and
// type. If the restaurant with the street number doesn't already exist, the function will insert to the hash
// table and binary search tree. If it already exists, the user will be prompted and the function will end.
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
    
    // Create restaurant
    restaurantInfo* addPtr = new restaurantInfo(tName, tNumber, tStreet, tType);
    
    // Insert hash
    status = aList->getHashPtr()->insertHash(addPtr);
    
    // If a restaurant with the entered street number does not exist add to the BST.
    // (Street number = unique).
    if (status)
    {
        // Insert BST
        aList->getBSTPtr()->addNode(addPtr);
        
        // Update number of restaurants in listHead (add 1)
        aList->addNumRestaurants();
        
        // Prompt user
        cout << endl << addPtr->getName() << " has been added successully!\n";
        
    }// End if
    
    cout << "\n===================================================================\n";
    
    return;
}// End insertManager

//***********************************************************************************************************
// Definition of deleteManager
//
// deleteManager will ask the user if they would like to delete by name or delete by number.
//
// - Delete by number -
// User will be prompted to enter a number. The function will then search for the restaurant in the hash array
// and if it exists, the function will call a BST function to find the respective node, set the restaurant
// pointer in that node to null, and delete the node. Then, the deleteManager function will delete the
// restaurant from the hash array. If no such restaurant was found in the hash array, the function will return.
//
// - Delete by name -
// User will be prompted to enter a number. The function will then search the BST for the restaurant and return
// a binary node if such a restaurant exists. If it does, the function will set the restaurant pointer in that
// node to null, delete the node, delete the respective restaurant in the hash array, and find the next
// restaurant with the entered name and repeat the process until no such restaurants exists. If no such
// restaurant was found in the BST, the function will return. 
//***********************************************************************************************************
void deleteManager(listHead *aList)
{
    string input;
    bool status;
    char choice[2];
    string name= "";
    bool DeleteSuccessful = true;
    BinaryNode* deleteNode=nullptr;
    restaurantInfo* restInfo = nullptr;
    int deNum;
    
    cout << endl;
    cout << "\n========================= D - D E L E T E =========================";
    
    // Prompt user
    cout << "\n\nEnter N to delete by number or S t delete by restaurant name: ";
    getline(cin, input);
    
    // Get lowercase equivalent of user's input
    choice[0] = tolower(input[0]);
    
    // If the user wants to delete by number...
    if (choice[0] == 'n')
    {
        // Get the address number from user
        cout << "\nEnter the number of the restaurant to delete: ";
        getline(cin, input);
        
        // Check if the restaurant with the street number exists
        // (Exists = true, otherwise false)
        status = aList->getHashPtr()->searchForDelete(atoi(input.c_str()), restInfo);        
        
        // If the restaurant with the address number exists
        if (status)
        {
            // Search for node in BST
            deleteNode = aList->getBSTPtr()->SearchName(aList->getBSTPtr()->getroot(), restInfo->getName());
            
            // If the node to be deleted is the same as the address number entered...
            if(deleteNode->getrestaurantInfo()->getNumber() == restInfo->getNumber())
            {
                // Reset root
                aList->getBSTPtr()->setRoot( aList->getBSTPtr()-> removeRestaurant(restInfo->getName(), aList->getBSTPtr()->getroot() , DeleteSuccessful));
                
                // Delete from hash
                aList->getHashPtr()->deleteHash(restInfo->getNumber(), name);
                
                // Update number of restaurants in listHead (subtract 1)
                aList->subNumRestaurants();
                
            }
            else
            {
                // While the restaurant to delete is not found...
                while(deleteNode!= nullptr && status!=false)
                {
                    // Find restaurant with address number
                    deleteNode = aList->getBSTPtr()->SearchName(deleteNode->getRightChildPtr(),  restInfo->getName());
                    
                    // If the node to be deleted is the same as the address number entered...
                    if(deleteNode->getrestaurantInfo()->getNumber() == restInfo->getNumber())
                    {
                        // Remove the restaurant node 
                        aList->getBSTPtr()->setRoot(aList->getBSTPtr()->removeRestaurant(restInfo->getName(), aList->getBSTPtr()-> getroot() , DeleteSuccessful));
                        
                        // Delete restaurant from hash table
                        aList->getHashPtr()->deleteHash(restInfo->getNumber(), name);
                        
                        // Update number of restaurants in listHead (subtract 1)
                        aList->subNumRestaurants();
                        
                        status= false;
                        
                    }// End if
                    
                }// End while
                
            }// End if
            
        }// End if
        
    }// End if
    else
    {
        // If the user wants to delete by name...
        if (choice[0] == 's')
        {
            // Get input from user
            cout << "\nEnter the name of the restaurant to delete: ";
            getline(cin, input);
            
            // Find node to delete 
            deleteNode=aList->getBSTPtr()->SearchName(aList->getBSTPtr()->getroot(), input);
            
            // While there is still a node to delete with the restaurant name...
            while( deleteNode != nullptr && DeleteSuccessful)
            {
                // Get the restaurant to delete's street number
                deNum=deleteNode->getrestaurantInfo()->getNumber();
                
                // Resert BST root
                aList->getBSTPtr()->setRoot( aList->getBSTPtr()-> removeRestaurant(input, aList->getBSTPtr()-> getroot() ,
                                                                                   DeleteSuccessful));
                
                // Delete restaurant from hash
                aList->getHashPtr()->deleteHash(deNum, name );
                
                // Update the number of restaurants in listHead
                aList->subNumRestaurants();
                
                // Find the next node to delete 
                deleteNode=aList->getBSTPtr()->SearchName(aList->getBSTPtr()->getroot(), input);
                
            }// End while

        }
        else    // Otherwise, the user entered an invalid input
        {
            cout << "\nYou have entered an invalid letter. Please try again.";
            
        }// End if
        
    }// Endd if
    
    cout << "\n===================================================================\n";
    
    return;
    
}// End deleteManager

//***********************************************************************************************************
// Definition of searchHashManager
//
// searchHashManager will prompt the user for a street number. Once the number is validated
// (checkValidStreetNum), the function will search in the hash and display accordingly. 
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
    
    // Search hash and display
    aList->getHashPtr()->searchHash(atoi(streetNum.c_str()));
    
    cout << "\n===================================================================\n";
    
    return true;
}// End searchHashManager

//***********************************************************************************************************
// Definition displayMenu
//
// displayMenu displays the operations available to the user. 
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
    cout << "\n=  A - Save to output                                             =";
    cout << "\n=  M - Display menu                                               =";         
    cout << "\n=  Q - Quit                                                       =";
    cout << "\n===================================================================\n";

}// End displayMenu

//***********************************************************************************************************
// Definition getUserInput
//
// getUserInput prompts the user to enter a letter according to what operation they would like to use.
// Once the input is validated, the function will return a character corresponding to an executable operation.
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
    
    cout << "\n===================================================================\n\n";

    // Return user's input
    return userInput[0];
    
}// End getUserInput

//***********************************************************************************************************
// Definition validateUserInput
//
// validateUserInput receives a character. The character is then validated. If it is valid, the character
// is returned by reference. If the character is invalid, the user will be prompted to enter another letter
// until the input is valid. 
//***********************************************************************************************************
void validateUserInput(char &tUserInput)
{
    string userInput;
    tUserInput = tolower(tUserInput);
    
    // While the input is not valid....
    while (tUserInput != 'i' & tUserInput != 'd' & tUserInput != 'p' & tUserInput != 'n'
           & tUserInput != 'k' & tUserInput != 'h' & tUserInput != 't' & tUserInput != 's'
           & tUserInput != 'q' & tUserInput != 'm' &tUserInput != 'a')
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
// operationManager receives a pointer to a listHead and a character. It will call the appropriate function
// according to the character received. 
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
                    searchBSTManager(aList);

                }
                else
                {
                    if (tUserInput == 'k')
                    {
                        aList->getHashPtr()->printInKeySequence();
                    }
                    else
                    {
                        if (tUserInput == 'h')
                        {
                            aList->getHashPtr()->printHashTableSequence();

                        }
                        else
                        {
                            if (tUserInput == 't')
                            {
                                aList->getBSTPtr()->printIndentedList( aList->getBSTPtr()->getroot(),0);
                            }
                            else
                            {
                                if (tUserInput == 's')
                                {
                                    aList->getHashPtr()->hashStatistics();
                                }
                                else
                                {
                                    if (tUserInput == 'a')
                                    {
                                        aList->getBSTPtr()->saveToFile(aList->getBSTPtr()->getroot());
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
    }
    
    return;
}// End operation manager

//***********************************************************************************************************
// Definition of checkValidStreetNum
//
// checkValidStreetNum validates the street number entered by the user so that there are no characters,
// the number is positive, and has at least three digits and at most five digits. If the input is not valid,
// the user will be prompted to enter a new value until it is valid. 
//***********************************************************************************************************
int checkValidStreetNum(string num)
{
    int status;
    int length;
    
    // Check to see if there are at least three digits
    length = num.length();
    
    // Check for valid street number
    status = num.find_first_not_of("0123456789");
    
    // If street number is not valid
    while (status >= 0 || atoi(num.c_str()) < 0 || length < 3 || length > 5)
    {
        cout << "\nYou have entered an invalid street number.";
        cout << "\nA valid street number contains only digits, is greater than 0,";
        cout << "\n      and has at least three digits and at most 5 digits.";
        cout << "\n\nEnter street number: ";
        getline(cin, num);
        
        length = num.length();
        
        // Check for valid street number
        status = num.find_first_not_of("0123456789");
        
    }// End if

    return atoi(num.c_str());
    
}// End checkValidStreetNum

//***********************************************************************************************************
// Definition of searchBSTManager
//
// searchBSTManager prompts the user for a restaurant name. It will then search the BST for the restaurant
// name and display the restaurants with the entered name until they are all displayed and return. If there
// are no restaurants with the name, the user will be prompted and the function will return. 
//***********************************************************************************************************
bool searchBSTManager(listHead *aList)
{
    string SearchName;
    
    cout << "\n========================== N - S E A R C H ========================";
    cout << "\n================ ( R E S T A U R A N T   N A M E ) ================";
    
    // Get name to search for from user
    cout<< "\n\nPlease enter the Restaurant Name: ";
    getline(cin, SearchName);
    
    // Search BST for restaurant with the entered name
    BinaryNode* tempNode = aList->getBSTPtr()->SearchName(aList->getBSTPtr()-> getroot(), SearchName);
    
    // If there is no such restaurant...
    if(tempNode==nullptr)
    {
        cout << SearchName << " is not found"<<endl;
        return false;
        
    }// End if
    
    // If there is a restaurant with the name...
    if (tempNode != nullptr)
    {
        cout << "\nRestaurant(s) with the name " << SearchName << " :" << endl;
        
        // While there are restaurants with the name...
        while(tempNode!= nullptr)
        {
            // Display restaurant
            tempNode->getrestaurantInfo()->displayRestaurant();
            
            // Find the next restaurant with the name
            tempNode = aList->getBSTPtr()->SearchName(tempNode->getRightChildPtr(), SearchName);
            
        }// End while

    }// End if
    
    
    cout << "\n===================================================================\n";

    return true;
}// End searchBSTManager
