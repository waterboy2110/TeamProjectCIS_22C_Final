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
    inFile.open("/Users/christinasok/Desktop/Project 3.9/Project 3.9/Restaurants.txt");
    
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
    status = aList->getHashPtr()->addHash(tNumber, addPtr);
    
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
    int validInt;
    
    cout << endl;
    cout << "\n========================= D - D E L E T E =========================";
    
    // Prompt user
    cout << "\n\nEnter N to delete by number or S to delete by restaurant name: ";
    getline(cin, input);
    
    // Get lowercase equivalent of user's input
    choice[0] = tolower(input[0]);
    
    // If the user wants to delete by number...
    if (choice[0] == 'n')
    {
        // Get the address number from user
        cout << "\nEnter the number of the restaurant to delete: ";
        getline(cin, input);
        
        validInt = checkValidStreetNum(input);
        
        // Check if the restaurant with the street number exists
        // (Exists = true, otherwise false)
        status = aList->getHashPtr()->searchForDelete(validInt, restInfo);
        
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
            
            if (!deleteNode)
            {
                cout << "\nThere are no restaurants with name " << input;
            }
            
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
    
    cout << "\n\n===================================================================\n";
    
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
    
    streetNum = to_string(tempNum);
    
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
    size_t status;
    size_t length;
    
    // Check to see if there are at least three digits
    length = num.length();
    
    // Check for valid street number
    status = num.find_first_not_of("0123456789");
    
    // If street number is not valid
    while (int(status) >= 0 || atoi(num.c_str()) < 0 || length < 3 || length > 5)
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





/*
 
========================= OUTPUT =========================
 
 
 
 ========= R E S T A U R A N T S   I N   C U P E R T I N O =========
 
 
 ============================= M E N U =============================
 =  I - Insert new data                                            =
 =  D - Delete data                                                =
 =  P - Search using street number                                 =
 =  N - Search using restaurant name                               =
 =  K - List data in street number sequence                        =
 =  H - List data in hash table sequence                           =
 =  T - Print indented tree                                        =
 =  S - Print hash statistics                                      =
 =  A - Save to output                                             =
 =  M - Display menu                                               =
 =  Q - Quit                                                       =
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): t
 
 ===================================================================
 
 1. Curry House   10350
 2. Philz Coffee   20686
 3. Thai Square Restaurant   21467
 4. Yiassoo   10660
 5. Yogurtland   19700
 5. Wingstop   19620
 6. Venus Cafe   20956
 7. Vua Kho Bo   10919
 7. Tpumps   19959
 4. SmokeEaters   10650
 5. Spring Rice & Crawfish   10123
 6. Ten Ren Tea   10881
 7. Starbucks   20520
 8. Starbucks   10355
 9. Starbucks   82012
 10. Starbucks   19831
 5. Rio Adobe Southwest Cafe   10525
 6. Roasted Coffee Bean   19110
 7. Sheng Kee Bakery   11122
 6. Quickly   21269
 3. Gochi Japanese Fusion Tapas   19980
 4. One Pot Shabu Shabu   19648
 5. Peet's Coffee & Tea   22350
 6. Peet's Coffee & Tea   20807
 6. Orange Tree   21267
 5. Ike's Lair   21000
 6. La Terra Bakery & Cafe   19960
 7. Noah's Bagels   20525
 8. Marina Food   10122
 9. Moo Moo Tea House   20916
 7. Kee Wah Bakery   10370
 8. La Patisserie   19758
 6. Grain D'or Bakery   10126
 4. Fantasia Coffee & Tea   10933
 2. Bitter+Sweet   20560
 3. Chipotle Mexican Grill   10385
 4. Coffee Society   21265
 5. Cold Stone Creamery   11123
 5. Cinnabon   19123
 6. Coffee Bean Cafe   10631
 4. Bobbie's Cafe   1361
 5. Boudin SF   20682
 5. Black Tie Fine Catering and Desserts   20450
 3. 212 New York Pizza   19998
 4. Aijito   7335
 5. Beard Papa's   19748
 6. Beija Flor Cafe   19622
 6. Alexander's Steakhouse   10330
 7. BAMBU Desserts & Drinks   10963
 8. BJ's Restaurant and Brewhouse   10690
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): h
 
 ===================================================================
 
 
 
 =========================== H - L I S T ===========================
 ========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========
 
 
 Index 0 is empty.
 
 Index 1 is empty.
 
 Index 2 is empty.
 
 Index 3 is empty.
 
 Index 4 is empty.
 
 Index 5 is empty.
 
 Restaurant(s) in Index: 6
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant(s) in Index: 7
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 8
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant(s) in Index: 9
 - SmokeEaters
 10650 S De Anza Blvd
 Chicken wings
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 10
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 Restaurant(s) in Index: 11
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant(s) in Index: 12
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant(s) in Index: 13
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 14
 - Aijito
 7335 Bollinger Rd
 Japanese
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant(s) in Index: 15
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant(s) in Index: 16
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant(s) in Index: 17
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant(s) in Index: 18
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant(s) in Index: 19
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Index 20 is empty.
 
 Restaurant(s) in Index: 21
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Index 22 is empty.
 
 Restaurant(s) in Index: 23
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Index 24 is empty.
 
 Index 25 is empty.
 
 Index 26 is empty.
 
 Index 27 is empty.
 
 Index 28 is empty.
 
 Index 29 is empty.
 
 Index 30 is empty.
 
 Index 31 is empty.
 
 Restaurant(s) in Index: 32
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Index 33 is empty.
 
 Index 34 is empty.
 
 Index 35 is empty.
 
 Index 36 is empty.
 
 Index 37 is empty.
 
 Index 38 is empty.
 
 Index 39 is empty.
 
 Index 40 is empty.
 
 Index 41 is empty.
 
 Index 42 is empty.
 
 Index 43 is empty.
 
 Index 44 is empty.
 
 Index 45 is empty.
 
 Index 46 is empty.
 
 Index 47 is empty.
 
 Index 48 is empty.
 
 Index 49 is empty.
 
 Index 50 is empty.
 
 Index 51 is empty.
 
 Index 52 is empty.
 
 Index 53 is empty.
 
 Index 54 is empty.
 
 Index 55 is empty.
 
 Index 56 is empty.
 
 Index 57 is empty.
 
 Index 58 is empty.
 
 Index 59 is empty.
 
 Index 60 is empty.
 
 Index 61 is empty.
 
 Restaurant(s) in Index: 62
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Index 63 is empty.
 
 Index 64 is empty.
 
 Index 65 is empty.
 
 Index 66 is empty.
 
 Index 67 is empty.
 
 Index 68 is empty.
 
 Index 69 is empty.
 
 Index 70 is empty.
 
 Index 71 is empty.
 
 Restaurant(s) in Index: 72
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Index 73 is empty.
 
 Restaurant(s) in Index: 74
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Index 75 is empty.
 
 Index 76 is empty.
 
 Index 77 is empty.
 
 Index 78 is empty.
 
 Index 79 is empty.
 
 Index 80 is empty.
 
 Index 81 is empty.
 
 Restaurant(s) in Index: 82
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Index 83 is empty.
 
 Index 84 is empty.
 
 Index 85 is empty.
 
 Index 86 is empty.
 
 Index 87 is empty.
 
 Index 88 is empty.
 
 Index 89 is empty.
 
 Index 90 is empty.
 
 Index 91 is empty.
 
 Index 92 is empty.
 
 Index 93 is empty.
 
 Restaurant(s) in Index: 94
 - Curry House
 10350 S De Anza Blvd
 Japanese
 
 Index 95 is empty.
 
 Index 96 is empty.
 
 Restaurant(s) in Index: 97
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Index 98 is empty.
 
 Index 99 is empty.
 
 Index 100 is empty.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 50 restaurant(s) total.
 
 
 Restaurant 1 of 50
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 2 of 50
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 3 of 50
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 4 of 50
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 5 of 50
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 6 of 50
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 7 of 50
 - Curry House
 10350 S De Anza Blvd
 Japanese
 
 Restaurant 8 of 50
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant 9 of 50
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 10 of 50
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 50
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 12 of 50
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 13 of 50
 - SmokeEaters
 10650 S De Anza Blvd
 Chicken wings
 
 Restaurant 14 of 50
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 15 of 50
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 16 of 50
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 17 of 50
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 18 of 50
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 19 of 50
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 20 of 50
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 21 of 50
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 22 of 50
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 23 of 50
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 24 of 50
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 25 of 50
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 26 of 50
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 27 of 50
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 28 of 50
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 29 of 50
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 30 of 50
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant 31 of 50
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 32 of 50
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 33 of 50
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 34 of 50
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 35 of 50
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 36 of 50
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 37 of 50
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 38 of 50
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 39 of 50
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 40 of 50
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 41 of 50
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 42 of 50
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 43 of 50
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 44 of 50
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 45 of 50
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 46 of 50
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 47 of 50
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 48 of 50
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 49 of 50
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 50 of 50
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): d
 
 ===================================================================
 
 
 
 ========================= D - D E L E T E =========================
 
 Enter N to delete by number or S to delete by restaurant name: n
 
 Enter the number of the restaurant to delete: 10650
 
 'SmokeEaters' with address number 10650 has been deleted.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 49 restaurant(s) total.
 
 
 Restaurant 1 of 49
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 2 of 49
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 3 of 49
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 4 of 49
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 5 of 49
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 6 of 49
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 7 of 49
 - Curry House
 10350 S De Anza Blvd
 Japanese
 
 Restaurant 8 of 49
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant 9 of 49
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 10 of 49
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 49
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 12 of 49
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 13 of 49
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 14 of 49
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 15 of 49
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 16 of 49
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 17 of 49
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 18 of 49
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 19 of 49
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 20 of 49
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 21 of 49
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 22 of 49
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 23 of 49
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 24 of 49
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 25 of 49
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 26 of 49
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 27 of 49
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 28 of 49
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 29 of 49
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant 30 of 49
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 31 of 49
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 32 of 49
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 33 of 49
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 34 of 49
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 35 of 49
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 36 of 49
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 37 of 49
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 38 of 49
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 39 of 49
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 40 of 49
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 41 of 49
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 42 of 49
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 43 of 49
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 44 of 49
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 45 of 49
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 46 of 49
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 47 of 49
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 48 of 49
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 49 of 49
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): d
 
 ===================================================================
 
 
 
 ========================= D - D E L E T E =========================
 
 Enter N to delete by number or S to delete by restaurant name: n
 
 Enter the number of the restaurant to delete: 2b329
 
 You have entered an invalid street number.
 A valid street number contains only digits, is greater than 0,
 and has at least three digits and at most 5 digits.
 
 Enter street number: 10350
 
 'Curry House' with address number 10350 has been deleted.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 48 restaurant(s) total.
 
 
 Restaurant 1 of 48
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 2 of 48
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 3 of 48
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 4 of 48
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 5 of 48
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 6 of 48
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 7 of 48
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant 8 of 48
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 9 of 48
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 10 of 48
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 48
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 12 of 48
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 13 of 48
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 14 of 48
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 15 of 48
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 16 of 48
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 17 of 48
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 18 of 48
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 19 of 48
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 20 of 48
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 21 of 48
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 22 of 48
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 23 of 48
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 24 of 48
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 25 of 48
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 26 of 48
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 27 of 48
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 28 of 48
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant 29 of 48
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 30 of 48
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 31 of 48
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 32 of 48
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 33 of 48
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 34 of 48
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 35 of 48
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 36 of 48
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 37 of 48
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 38 of 48
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 39 of 48
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 40 of 48
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 41 of 48
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 42 of 48
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 43 of 48
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 44 of 48
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 45 of 48
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 46 of 48
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 47 of 48
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 48 of 48
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): p
 
 ===================================================================
 
 
 
 ========================== P - S E A R C H ========================
 =================== ( S T R E E T   N U M B E R ) =================
 
 Enter street number: 1111
 
 There are no restaurants with street number 1111
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): p
 
 ===================================================================
 
 
 
 ========================== P - S E A R C H ========================
 =================== ( S T R E E T   N U M B E R ) =================
 
 Enter street number: -94.
 
 You have entered an invalid street number.
 A valid street number contains only digits, is greater than 0,
 and has at least three digits and at most 5 digits.
 
 Enter street number: 10123
 
 Restaurant with street number 10123:
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): p
 
 ===================================================================
 
 
 
 ========================== P - S E A R C H ========================
 =================== ( S T R E E T   N U M B E R ) =================
 
 Enter street number: 21000
 
 Restaurant with street number 21000:
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): p
 
 ===================================================================
 
 
 
 ========================== P - S E A R C H ========================
 =================== ( S T R E E T   N U M B E R ) =================
 
 Enter street number: 1361
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): i
 
 ===================================================================
 
 
 
 ========================= I - I N S E R T =========================
 
 Enter restaurant name: ABC
 
 Enter street number: -4828
 
 You have entered an invalid street number.
 A valid street number contains only digits, is greater than 0,
 and has at least three digits and at most 5 digits.
 
 Enter street number: 1289
 
 Enter street name: Hi
 
 Enter type: Yum
 
 Restaurant with address number 1289 has been added.
 ABC has been added successully!
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): i
 
 ===================================================================
 
 
 
 ========================= I - I N S E R T =========================
 
 Enter restaurant name: Paris Baguette
 
 Enter street number: 20735
 
 Enter street name: Stevens Creek Blvd
 
 Enter type: Bakery
 
 Restaurant with address number 20735 has been added.
 Paris Baguette has been added successully!
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): i
 
 ===================================================================
 
 
 
 ========================= I - I N S E R T =========================
 
 Enter restaurant name: Paris Baguette
 
 Enter street number: 20735
 
 Enter street name: Stevens Creek Blvd
 
 Enter type: Bakery
 
 A restaurant with address number 20735 already exists.
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 50 restaurant(s) total.
 
 
 Restaurant 1 of 50
 - ABC
 1289 Hi
 Yum
 
 Restaurant 2 of 50
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 3 of 50
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 4 of 50
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 5 of 50
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 6 of 50
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 7 of 50
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 8 of 50
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant 9 of 50
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 10 of 50
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 50
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 12 of 50
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 13 of 50
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 14 of 50
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 15 of 50
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 16 of 50
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 17 of 50
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 18 of 50
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 19 of 50
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 20 of 50
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 21 of 50
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 22 of 50
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 23 of 50
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 24 of 50
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 25 of 50
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 26 of 50
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 27 of 50
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 28 of 50
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 29 of 50
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant 30 of 50
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 31 of 50
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 32 of 50
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 33 of 50
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 34 of 50
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 35 of 50
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 36 of 50
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 37 of 50
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 38 of 50
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 39 of 50
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 40 of 50
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 
 Restaurant 41 of 50
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 42 of 50
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 43 of 50
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 44 of 50
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 45 of 50
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 46 of 50
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 47 of 50
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 48 of 50
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 49 of 50
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 50 of 50
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): w
 
 You have entered an invalid letter.
 Please enter a letter: a
 
 ===================================================================
 
 Saving File...
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): s
 
 ===================================================================
 
 
 
 ================== H A S H   S T A T I S T I C S ==================
 
 Load factor (50/101): 49.5%
 Longest linked-list: 6
 Average number of nodes stored in linked-list: 2
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): h
 
 ===================================================================
 
 
 
 =========================== H - L I S T ===========================
 ========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========
 
 
 Index 0 is empty.
 
 Index 1 is empty.
 
 Index 2 is empty.
 
 Index 3 is empty.
 
 Index 4 is empty.
 
 Index 5 is empty.
 
 Restaurant(s) in Index: 6
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant(s) in Index: 7
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 8
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant(s) in Index: 9
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 10
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 Restaurant(s) in Index: 11
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant(s) in Index: 12
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant(s) in Index: 13
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 
 Restaurant(s) in Index: 14
 - Aijito
 7335 Bollinger Rd
 Japanese
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 - ABC
 1289 Hi
 Yum
 
 Restaurant(s) in Index: 15
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant(s) in Index: 16
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant(s) in Index: 17
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant(s) in Index: 18
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant(s) in Index: 19
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Index 20 is empty.
 
 Restaurant(s) in Index: 21
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Index 22 is empty.
 
 Restaurant(s) in Index: 23
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Index 24 is empty.
 
 Index 25 is empty.
 
 Index 26 is empty.
 
 Index 27 is empty.
 
 Index 28 is empty.
 
 Index 29 is empty.
 
 Index 30 is empty.
 
 Index 31 is empty.
 
 Restaurant(s) in Index: 32
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Index 33 is empty.
 
 Index 34 is empty.
 
 Index 35 is empty.
 
 Index 36 is empty.
 
 Index 37 is empty.
 
 Index 38 is empty.
 
 Index 39 is empty.
 
 Index 40 is empty.
 
 Index 41 is empty.
 
 Index 42 is empty.
 
 Index 43 is empty.
 
 Index 44 is empty.
 
 Index 45 is empty.
 
 Index 46 is empty.
 
 Index 47 is empty.
 
 Index 48 is empty.
 
 Index 49 is empty.
 
 Index 50 is empty.
 
 Index 51 is empty.
 
 Index 52 is empty.
 
 Index 53 is empty.
 
 Index 54 is empty.
 
 Index 55 is empty.
 
 Index 56 is empty.
 
 Index 57 is empty.
 
 Index 58 is empty.
 
 Index 59 is empty.
 
 Index 60 is empty.
 
 Index 61 is empty.
 
 Restaurant(s) in Index: 62
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Index 63 is empty.
 
 Index 64 is empty.
 
 Index 65 is empty.
 
 Index 66 is empty.
 
 Index 67 is empty.
 
 Index 68 is empty.
 
 Index 69 is empty.
 
 Index 70 is empty.
 
 Index 71 is empty.
 
 Restaurant(s) in Index: 72
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Index 73 is empty.
 
 Restaurant(s) in Index: 74
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Index 75 is empty.
 
 Index 76 is empty.
 
 Index 77 is empty.
 
 Index 78 is empty.
 
 Index 79 is empty.
 
 Index 80 is empty.
 
 Index 81 is empty.
 
 Restaurant(s) in Index: 82
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Index 83 is empty.
 
 Index 84 is empty.
 
 Index 85 is empty.
 
 Index 86 is empty.
 
 Index 87 is empty.
 
 Index 88 is empty.
 
 Index 89 is empty.
 
 Index 90 is empty.
 
 Index 91 is empty.
 
 Index 92 is empty.
 
 Index 93 is empty.
 
 Index 94 is empty.
 
 Index 95 is empty.
 
 Index 96 is empty.
 
 Restaurant(s) in Index: 97
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Index 98 is empty.
 
 Index 99 is empty.
 
 Index 100 is empty.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): m
 
 ===================================================================
 
 
 
 ============================= M E N U =============================
 =  I - Insert new data                                            =
 =  D - Delete data                                                =
 =  P - Search using street number                                 =
 =  N - Search using restaurant name                               =
 =  K - List data in street number sequence                        =
 =  H - List data in hash table sequence                           =
 =  T - Print indented tree                                        =
 =  S - Print hash statistics                                      =
 =  A - Save to output                                             =
 =  M - Display menu                                               =
 =  Q - Quit                                                       =
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): i
 
 ===================================================================
 
 
 
 ========================= I - I N S E R T =========================
 
 Enter restaurant name: Demonstrate Collision Resolution
 
 Enter street number: 70235
 
 Enter street name: AAA
 
 Enter type: A
 
 Restaurant with address number 70235 has been added.
 Demonstrate Collision Resolution has been added successully!
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 51 restaurant(s) total.
 
 
 Restaurant 1 of 51
 - ABC
 1289 Hi
 Yum
 
 Restaurant 2 of 51
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 3 of 51
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 4 of 51
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 5 of 51
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 6 of 51
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 7 of 51
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 8 of 51
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant 9 of 51
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 10 of 51
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 51
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 12 of 51
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 13 of 51
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 14 of 51
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 15 of 51
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 16 of 51
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 17 of 51
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 18 of 51
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 19 of 51
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 20 of 51
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 21 of 51
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 22 of 51
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 23 of 51
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 24 of 51
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 25 of 51
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 26 of 51
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 27 of 51
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 28 of 51
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 29 of 51
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant 30 of 51
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 31 of 51
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 32 of 51
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 33 of 51
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 34 of 51
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 35 of 51
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 36 of 51
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 37 of 51
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 38 of 51
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 39 of 51
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 40 of 51
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 
 Restaurant 41 of 51
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 42 of 51
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 43 of 51
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 44 of 51
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 45 of 51
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 46 of 51
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 47 of 51
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 48 of 51
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 49 of 51
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 50 of 51
 - Demonstrate Collision Resolution
 70235 AAA
 A
 
 Restaurant 51 of 51
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): h
 
 ===================================================================
 
 
 
 =========================== H - L I S T ===========================
 ========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========
 
 
 Index 0 is empty.
 
 Index 1 is empty.
 
 Index 2 is empty.
 
 Index 3 is empty.
 
 Index 4 is empty.
 
 Index 5 is empty.
 
 Restaurant(s) in Index: 6
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant(s) in Index: 7
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 8
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant(s) in Index: 9
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 - Starbucks
 10355 N De Anza Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 10
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 - Starbucks
 82012 S De Anza Rd
 Coffee
 
 Restaurant(s) in Index: 11
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant(s) in Index: 12
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant(s) in Index: 13
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 - Demonstrate Collision Resolution
 70235 AAA
 A
 
 Restaurant(s) in Index: 14
 - Aijito
 7335 Bollinger Rd
 Japanese
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 - ABC
 1289 Hi
 Yum
 
 Restaurant(s) in Index: 15
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 - Starbucks
 19831 Stevenson Blvd
 Coffee
 
 Restaurant(s) in Index: 16
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant(s) in Index: 17
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant(s) in Index: 18
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant(s) in Index: 19
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Index 20 is empty.
 
 Restaurant(s) in Index: 21
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Index 22 is empty.
 
 Restaurant(s) in Index: 23
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Index 24 is empty.
 
 Index 25 is empty.
 
 Index 26 is empty.
 
 Index 27 is empty.
 
 Index 28 is empty.
 
 Index 29 is empty.
 
 Index 30 is empty.
 
 Index 31 is empty.
 
 Restaurant(s) in Index: 32
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Index 33 is empty.
 
 Index 34 is empty.
 
 Index 35 is empty.
 
 Index 36 is empty.
 
 Index 37 is empty.
 
 Index 38 is empty.
 
 Index 39 is empty.
 
 Index 40 is empty.
 
 Index 41 is empty.
 
 Index 42 is empty.
 
 Index 43 is empty.
 
 Index 44 is empty.
 
 Index 45 is empty.
 
 Index 46 is empty.
 
 Index 47 is empty.
 
 Index 48 is empty.
 
 Index 49 is empty.
 
 Index 50 is empty.
 
 Index 51 is empty.
 
 Index 52 is empty.
 
 Index 53 is empty.
 
 Index 54 is empty.
 
 Index 55 is empty.
 
 Index 56 is empty.
 
 Index 57 is empty.
 
 Index 58 is empty.
 
 Index 59 is empty.
 
 Index 60 is empty.
 
 Index 61 is empty.
 
 Restaurant(s) in Index: 62
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Index 63 is empty.
 
 Index 64 is empty.
 
 Index 65 is empty.
 
 Index 66 is empty.
 
 Index 67 is empty.
 
 Index 68 is empty.
 
 Index 69 is empty.
 
 Index 70 is empty.
 
 Index 71 is empty.
 
 Restaurant(s) in Index: 72
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Index 73 is empty.
 
 Restaurant(s) in Index: 74
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Index 75 is empty.
 
 Index 76 is empty.
 
 Index 77 is empty.
 
 Index 78 is empty.
 
 Index 79 is empty.
 
 Index 80 is empty.
 
 Index 81 is empty.
 
 Restaurant(s) in Index: 82
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Index 83 is empty.
 
 Index 84 is empty.
 
 Index 85 is empty.
 
 Index 86 is empty.
 
 Index 87 is empty.
 
 Index 88 is empty.
 
 Index 89 is empty.
 
 Index 90 is empty.
 
 Index 91 is empty.
 
 Index 92 is empty.
 
 Index 93 is empty.
 
 Index 94 is empty.
 
 Index 95 is empty.
 
 Index 96 is empty.
 
 Restaurant(s) in Index: 97
 - Starbucks
 20520 Stevens Creek Blvd
 Coffee & Tea
 
 Index 98 is empty.
 
 Index 99 is empty.
 
 Index 100 is empty.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): t
 
 ===================================================================
 
 1. Fantasia Coffee & Tea   10933
 2. Philz Coffee   20686
 3. Thai Square Restaurant   21467
 4. Yiassoo   10660
 5. Yogurtland   19700
 5. Wingstop   19620
 6. Venus Cafe   20956
 7. Vua Kho Bo   10919
 7. Tpumps   19959
 4. Spring Rice & Crawfish   10123
 5. Ten Ren Tea   10881
 6. Starbucks   20520
 7. Starbucks   10355
 8. Starbucks   82012
 9. Starbucks   19831
 5. Rio Adobe Southwest Cafe   10525
 6. Roasted Coffee Bean   19110
 7. Sheng Kee Bakery   11122
 6. Quickly   21269
 3. Gochi Japanese Fusion Tapas   19980
 4. One Pot Shabu Shabu   19648
 5. Peet's Coffee & Tea   22350
 6. Peet's Coffee & Tea   20807
 6. Orange Tree   21267
 7. Paris Baguette   20735
 5. Ike's Lair   21000
 6. La Terra Bakery & Cafe   19960
 7. Noah's Bagels   20525
 8. Marina Food   10122
 9. Moo Moo Tea House   20916
 7. Kee Wah Bakery   10370
 8. La Patisserie   19758
 6. Grain D'or Bakery   10126
 2. Bitter+Sweet   20560
 3. Chipotle Mexican Grill   10385
 4. Coffee Society   21265
 5. Cold Stone Creamery   11123
 6. Demonstrate Collision Resolution   70235
 5. Cinnabon   19123
 6. Coffee Bean Cafe   10631
 4. Bobbie's Cafe   1361
 5. Boudin SF   20682
 5. Black Tie Fine Catering and Desserts   20450
 3. 212 New York Pizza   19998
 4. Aijito   7335
 5. Beard Papa's   19748
 6. Beija Flor Cafe   19622
 6. Alexander's Steakhouse   10330
 7. BAMBU Desserts & Drinks   10963
 8. BJ's Restaurant and Brewhouse   10690
 5. ABC   1289
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): d
 
 ===================================================================
 
 
 
 ========================= D - D E L E T E =========================
 
 Enter N to delete by number or S to delete by restaurant name: s
 
 Enter the name of the restaurant to delete: Starbucks
 
 'Starbucks' with address number 20520 has been deleted.
 'Starbucks' with address number 10355 has been deleted.
 'Starbucks' with address number 82012 has been deleted.
 'Starbucks' with address number 19831 has been deleted.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): t
 
 ===================================================================
 
 1. Fantasia Coffee & Tea   10933
 2. Philz Coffee   20686
 3. Thai Square Restaurant   21467
 4. Yiassoo   10660
 5. Yogurtland   19700
 5. Wingstop   19620
 6. Venus Cafe   20956
 7. Vua Kho Bo   10919
 7. Tpumps   19959
 4. Spring Rice & Crawfish   10123
 5. Ten Ren Tea   10881
 5. Rio Adobe Southwest Cafe   10525
 6. Roasted Coffee Bean   19110
 7. Sheng Kee Bakery   11122
 6. Quickly   21269
 3. Gochi Japanese Fusion Tapas   19980
 4. One Pot Shabu Shabu   19648
 5. Peet's Coffee & Tea   22350
 6. Peet's Coffee & Tea   20807
 6. Orange Tree   21267
 7. Paris Baguette   20735
 5. Ike's Lair   21000
 6. La Terra Bakery & Cafe   19960
 7. Noah's Bagels   20525
 8. Marina Food   10122
 9. Moo Moo Tea House   20916
 7. Kee Wah Bakery   10370
 8. La Patisserie   19758
 6. Grain D'or Bakery   10126
 2. Bitter+Sweet   20560
 3. Chipotle Mexican Grill   10385
 4. Coffee Society   21265
 5. Cold Stone Creamery   11123
 6. Demonstrate Collision Resolution   70235
 5. Cinnabon   19123
 6. Coffee Bean Cafe   10631
 4. Bobbie's Cafe   1361
 5. Boudin SF   20682
 5. Black Tie Fine Catering and Desserts   20450
 3. 212 New York Pizza   19998
 4. Aijito   7335
 5. Beard Papa's   19748
 6. Beija Flor Cafe   19622
 6. Alexander's Steakhouse   10330
 7. BAMBU Desserts & Drinks   10963
 8. BJ's Restaurant and Brewhouse   10690
 5. ABC   1289
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): D
 
 ===================================================================
 
 
 
 ========================= D - D E L E T E =========================
 
 Enter N to delete by number or S to delete by restaurant name: S
 
 Enter the name of the restaurant to delete: Safeway
 
 There are no restaurants with name Safeway
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): n
 
 ===================================================================
 
 
 ========================== N - S E A R C H ========================
 ================ ( R E S T A U R A N T   N A M E ) ================
 
 Please enter the Restaurant Name: 212 New York Pizza
 
 Restaurant(s) with the name 212 New York Pizza :
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): n
 
 ===================================================================
 
 
 ========================== N - S E A R C H ========================
 ================ ( R E S T A U R A N T   N A M E ) ================
 
 Please enter the Restaurant Name: Chipotle Mexican Grill
 
 Restaurant(s) with the name Chipotle Mexican Grill :
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): n
 
 ===================================================================
 
 
 ========================== N - S E A R C H ========================
 ================ ( R E S T A U R A N T   N A M E ) ================
 
 Please enter the Restaurant Name: Chezz
 Chezz is not found
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): t
 
 ===================================================================
 
 1. Fantasia Coffee & Tea   10933
 2. Philz Coffee   20686
 3. Thai Square Restaurant   21467
 4. Yiassoo   10660
 5. Yogurtland   19700
 5. Wingstop   19620
 6. Venus Cafe   20956
 7. Vua Kho Bo   10919
 7. Tpumps   19959
 4. Spring Rice & Crawfish   10123
 5. Ten Ren Tea   10881
 5. Rio Adobe Southwest Cafe   10525
 6. Roasted Coffee Bean   19110
 7. Sheng Kee Bakery   11122
 6. Quickly   21269
 3. Gochi Japanese Fusion Tapas   19980
 4. One Pot Shabu Shabu   19648
 5. Peet's Coffee & Tea   22350
 6. Peet's Coffee & Tea   20807
 6. Orange Tree   21267
 7. Paris Baguette   20735
 5. Ike's Lair   21000
 6. La Terra Bakery & Cafe   19960
 7. Noah's Bagels   20525
 8. Marina Food   10122
 9. Moo Moo Tea House   20916
 7. Kee Wah Bakery   10370
 8. La Patisserie   19758
 6. Grain D'or Bakery   10126
 2. Bitter+Sweet   20560
 3. Chipotle Mexican Grill   10385
 4. Coffee Society   21265
 5. Cold Stone Creamery   11123
 6. Demonstrate Collision Resolution   70235
 5. Cinnabon   19123
 6. Coffee Bean Cafe   10631
 4. Bobbie's Cafe   1361
 5. Boudin SF   20682
 5. Black Tie Fine Catering and Desserts   20450
 3. 212 New York Pizza   19998
 4. Aijito   7335
 5. Beard Papa's   19748
 6. Beija Flor Cafe   19622
 6. Alexander's Steakhouse   10330
 7. BAMBU Desserts & Drinks   10963
 8. BJ's Restaurant and Brewhouse   10690
 5. ABC   1289
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): a
 
 ===================================================================
 
 Saving File...
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): k
 
 ===================================================================
 
 
 
 =========================== K - L I S T ===========================
 ======== ( I N   K E Y   S E Q U E N C E  -  S O R T E D ) ========
 
 
 There are 47 restaurant(s) total.
 
 
 Restaurant 1 of 47
 - ABC
 1289 Hi
 Yum
 
 Restaurant 2 of 47
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 
 Restaurant 3 of 47
 - Aijito
 7335 Bollinger Rd
 Japanese
 
 Restaurant 4 of 47
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Restaurant 5 of 47
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 
 Restaurant 6 of 47
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant 7 of 47
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Restaurant 8 of 47
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 
 Restaurant 9 of 47
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 
 Restaurant 10 of 47
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 
 Restaurant 11 of 47
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant 12 of 47
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 
 Restaurant 13 of 47
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant 14 of 47
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 
 Restaurant 15 of 47
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant 16 of 47
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 
 Restaurant 17 of 47
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 
 Restaurant 18 of 47
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Restaurant 19 of 47
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Restaurant 20 of 47
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 21 of 47
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 
 Restaurant 22 of 47
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 
 Restaurant 23 of 47
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 
 Restaurant 24 of 47
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 
 Restaurant 25 of 47
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 26 of 47
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 
 Restaurant 27 of 47
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Restaurant 28 of 47
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 29 of 47
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant 30 of 47
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant 31 of 47
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Restaurant 32 of 47
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 
 Restaurant 33 of 47
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant 34 of 47
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 
 Restaurant 35 of 47
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 
 Restaurant 36 of 47
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 
 Restaurant 37 of 47
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 
 Restaurant 38 of 47
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 39 of 47
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 
 Restaurant 40 of 47
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant 41 of 47
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Restaurant 42 of 47
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant 43 of 47
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant 44 of 47
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 
 Restaurant 45 of 47
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 
 Restaurant 46 of 47
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant 47 of 47
 - Demonstrate Collision Resolution
 70235 AAA
 A
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): h
 
 ===================================================================
 
 
 
 =========================== H - L I S T ===========================
 ========== ( I N  H A S H   T A B L E   S E Q U E N C E) ==========
 
 
 Index 0 is empty.
 
 Index 1 is empty.
 
 Index 2 is empty.
 
 Index 3 is empty.
 
 Index 4 is empty.
 
 Index 5 is empty.
 
 Restaurant(s) in Index: 6
 - Grain D'or Bakery
 10126 N Wolfe Rd
 Bakeries
 
 Restaurant(s) in Index: 7
 - Kee Wah Bakery
 10370 S De Anza Blvd
 Bakeries
 - Roasted Coffee Bean
 19110 Stevens Creek Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 8
 - Black Tie Fine Catering and Desserts
 20450 Stevens Creek Blvd
 Dessert
 - Peet's Coffee & Tea
 22350 Homestead Rd
 Coffee & Tea
 
 Restaurant(s) in Index: 9
 - Rio Adobe Southwest Cafe
 10525 S De Anza Blvd
 Mexican
 - Bobbie's Cafe
 1361 S De Anza Blvd
 Breakfast
 - Cinnabon
 19123 N Wolfe Rd
 Bakeries
 - Coffee Bean Cafe
 10631 S Foothill Blvd
 Coffee & Tea
 
 Restaurant(s) in Index: 10
 - Yiassoo
 10660 S De Anza Blvd
 Greek
 - Bitter+Sweet
 20560 Town Center Ln
 Coffee
 - Chipotle Mexican Grill
 10385 S De Anza Blvd
 Mexican
 - Coffee Society
 21265 Stevens Creek Blvd
 Coffee & Tea
 - Noah's Bagels
 20525 Stevens Creek Blvd
 Bagels
 
 Restaurant(s) in Index: 11
 - Orange Tree
 21267 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 - BJ's Restaurant and Brewhouse
 10690 N De Anza Blvd
 American
 
 Restaurant(s) in Index: 12
 - Wingstop
 19620 Stevens Creek Blvd
 Chicken wings
 - Quickly
 21269 Stevens Creek Blvd
 Asian Fusion
 - Yogurtland
 19700 Stevens Creek Blvd
 Ice Cream & Frozen Yogurt
 
 Restaurant(s) in Index: 13
 - Thai Square Restaurant
 21467 Stevens Creek Blvd
 Thai
 - Fantasia Coffee & Tea
 10933 N Wolfe Rd
 Coffee
 - Ten Ren Tea
 10881 N Wolfe Rd
 Coffee and Tea
 - Beija Flor Cafe
 19622 Stevens Creek Blvd
 Dessert
 - Boudin SF
 20682 Stevens Creek Blvd
 American
 - Peet's Coffee & Tea
 20807 Stevens Creek Blvd
 Coffee & Tea
 - Paris Baguette
 20735 Stevens Creek Blvd
 Bakery
 - Demonstrate Collision Resolution
 70235 AAA
 A
 
 Restaurant(s) in Index: 14
 - Aijito
 7335 Bollinger Rd
 Japanese
 - BAMBU Desserts & Drinks
 10963 N Wolfe Rd
 Dessert
 - Moo Moo Tea House
 20916 Homestead Rd
 Coffee & Tea
 - ABC
 1289 Hi
 Yum
 
 Restaurant(s) in Index: 15
 - Philz Coffee
 20686 Stevens Creek Blvd
 Coffee
 - Vua Kho Bo
 10919 N Wolfe Rd
 Candy Store
 
 Restaurant(s) in Index: 16
 - Venus Cafe
 20956 W Homestead Rd
 Chinese
 
 Restaurant(s) in Index: 17
 - One Pot Shabu Shabu
 19648 Stevens Creek Blvd
 Japanese
 - La Terra Bakery & Cafe
 19960 Homestead Rd
 Bakeries
 
 Restaurant(s) in Index: 18
 - Beard Papa's
 19748 Stevens Creek Blvd
 Desserts
 - Gochi Japanese Fusion Tapas
 19980 E Homestead Rd
 Japanese
 
 Restaurant(s) in Index: 19
 - La Patisserie
 19758 Stevens Creek Blvd
 Bakeries
 
 Index 20 is empty.
 
 Restaurant(s) in Index: 21
 - Tpumps
 19959 Stevens Creek Blvd
 Coffee & Tea
 
 Index 22 is empty.
 
 Restaurant(s) in Index: 23
 - 212 New York Pizza
 19998 Homestead Rd
 Pizza
 
 Index 24 is empty.
 
 Index 25 is empty.
 
 Index 26 is empty.
 
 Index 27 is empty.
 
 Index 28 is empty.
 
 Index 29 is empty.
 
 Index 30 is empty.
 
 Index 31 is empty.
 
 Restaurant(s) in Index: 32
 - Ike's Lair
 21000 Stevens Creek Blvd
 Sandwiches
 
 Index 33 is empty.
 
 Index 34 is empty.
 
 Index 35 is empty.
 
 Index 36 is empty.
 
 Index 37 is empty.
 
 Index 38 is empty.
 
 Index 39 is empty.
 
 Index 40 is empty.
 
 Index 41 is empty.
 
 Index 42 is empty.
 
 Index 43 is empty.
 
 Index 44 is empty.
 
 Index 45 is empty.
 
 Index 46 is empty.
 
 Index 47 is empty.
 
 Index 48 is empty.
 
 Index 49 is empty.
 
 Index 50 is empty.
 
 Index 51 is empty.
 
 Index 52 is empty.
 
 Index 53 is empty.
 
 Index 54 is empty.
 
 Index 55 is empty.
 
 Index 56 is empty.
 
 Index 57 is empty.
 
 Index 58 is empty.
 
 Index 59 is empty.
 
 Index 60 is empty.
 
 Index 61 is empty.
 
 Restaurant(s) in Index: 62
 - Marina Food
 10122 Bandley Dr
 Ethnic Food
 
 Index 63 is empty.
 
 Index 64 is empty.
 
 Index 65 is empty.
 
 Index 66 is empty.
 
 Index 67 is empty.
 
 Index 68 is empty.
 
 Index 69 is empty.
 
 Index 70 is empty.
 
 Index 71 is empty.
 
 Restaurant(s) in Index: 72
 - Spring Rice & Crawfish
 10123 N Wolfe Rd
 Seafood
 - Sheng Kee Bakery
 11122 Bradley Drive
 Bakeries
 
 Index 73 is empty.
 
 Restaurant(s) in Index: 74
 - Alexander's Steakhouse
 10330 N Wolfe Rd
 Steakhouses
 
 Index 75 is empty.
 
 Index 76 is empty.
 
 Index 77 is empty.
 
 Index 78 is empty.
 
 Index 79 is empty.
 
 Index 80 is empty.
 
 Index 81 is empty.
 
 Restaurant(s) in Index: 82
 - Cold Stone Creamery
 11123 N Wolfe Rd
 Ice Cream & Frozen Yogurt
 
 Index 83 is empty.
 
 Index 84 is empty.
 
 Index 85 is empty.
 
 Index 86 is empty.
 
 Index 87 is empty.
 
 Index 88 is empty.
 
 Index 89 is empty.
 
 Index 90 is empty.
 
 Index 91 is empty.
 
 Index 92 is empty.
 
 Index 93 is empty.
 
 Index 94 is empty.
 
 Index 95 is empty.
 
 Index 96 is empty.
 
 Index 97 is empty.
 
 Index 98 is empty.
 
 Index 99 is empty.
 
 Index 100 is empty.
 
 ===================================================================
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): t
 
 ===================================================================
 
 1. Fantasia Coffee & Tea   10933
 2. Philz Coffee   20686
 3. Thai Square Restaurant   21467
 4. Yiassoo   10660
 5. Yogurtland   19700
 5. Wingstop   19620
 6. Venus Cafe   20956
 7. Vua Kho Bo   10919
 7. Tpumps   19959
 4. Spring Rice & Crawfish   10123
 5. Ten Ren Tea   10881
 5. Rio Adobe Southwest Cafe   10525
 6. Roasted Coffee Bean   19110
 7. Sheng Kee Bakery   11122
 6. Quickly   21269
 3. Gochi Japanese Fusion Tapas   19980
 4. One Pot Shabu Shabu   19648
 5. Peet's Coffee & Tea   22350
 6. Peet's Coffee & Tea   20807
 6. Orange Tree   21267
 7. Paris Baguette   20735
 5. Ike's Lair   21000
 6. La Terra Bakery & Cafe   19960
 7. Noah's Bagels   20525
 8. Marina Food   10122
 9. Moo Moo Tea House   20916
 7. Kee Wah Bakery   10370
 8. La Patisserie   19758
 6. Grain D'or Bakery   10126
 2. Bitter+Sweet   20560
 3. Chipotle Mexican Grill   10385
 4. Coffee Society   21265
 5. Cold Stone Creamery   11123
 6. Demonstrate Collision Resolution   70235
 5. Cinnabon   19123
 6. Coffee Bean Cafe   10631
 4. Bobbie's Cafe   1361
 5. Boudin SF   20682
 5. Black Tie Fine Catering and Desserts   20450
 3. 212 New York Pizza   19998
 4. Aijito   7335
 5. Beard Papa's   19748
 6. Beija Flor Cafe   19622
 6. Alexander's Steakhouse   10330
 7. BAMBU Desserts & Drinks   10963
 8. BJ's Restaurant and Brewhouse   10690
 5. ABC   1289
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): a
 
 ===================================================================
 
 Saving File...
 
 
 ======================== U S E R  I N P U T =======================
 
 Enter a letter (to display menu, enter the letter 'm'): q
 
 ===================================================================
 
 Saving File...
 
 ======================== T H A N K  Y O U =========================
 */
