//***************************************************************************************
// Christina Sok, Yenni Chu, James Agua                  3/9/14          Mac OS X - xCode
// 
// 
//
//***************************************************************************************

//***********************************************************************************************************
// THINGS TO ADD:
//
// - Check for cost type (valid)
//
//***********************************************************************************************************

#include <iostream>
#include <fstream>
#include "Hash.h"
#include "ListHead.h"

// Function prototypes
bool readFile(Hash *aPtr);
bool insertManager(listHead *aList);
bool deleteManager(listHead *aList);
bool searchHashManager(listHead *aList);
bool searchBSTManager(listHead *aList);
//bool listHashSequenceManager(listHead *aList);
//bool listKeySequenceManager(listHead *aList);
//bool printIndentedTreeManager(listHead *aList);
bool writeFile(listHead *aList);
bool hashStat(listHead *aList);
void displayMenu();
char getUserInput();
void validateUserInput(char &tUserInput);
void operationManager(listHead *aList, char tUserInput);

int main()
{
    cout << "========= R E S T A U R A N T S   I N   C U P E R T I N O =========";
    
    //listHead(15);
        
    Hash *hashPtr;
    hashPtr = new Hash();
    
    readFile(hashPtr);
    
    int t;
    cout << "to delete: ";
    cin >> t;
    
    hashPtr->deleteHash(t);
    
    //hashPtr->displayHash();
    
    //displayMenu();
    
    //getUserInput();
    
    cout << "\n=================== E N D   O F   P R O G R A M ===================";
}

//***************************************************************************************
// Definition readFile
//
//***************************************************************************************
bool readFile(Hash *aPtr)
{
    ifstream inFile;
    string tName;       // Restaurant name
    int tStreetNum;     // Street number
    string tStreetName; // Street name
    string tType;       // Type
    string tCost;       // Cost
    
    int hashNum;
    
    int num = 0;
    
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
            
            hashNum = aPtr->hashFunction(tStreetNum);
            
            //cout << "\nHash Number: " << hashNum;
            
            //    restaurantInfo(string aName, int aNumber, streetList aStreet, typeList aType);
            restaurantInfo *tRestPtr = new restaurantInfo(tName, tStreetNum, tStreetName, tType);
            
            cout << "\nRestaurant name: " << tRestPtr->getName() << " " << hashNum;
            
            aPtr->insertHash(hashNum, tRestPtr);
            
            num++;
            
        }// End while
    }// End if
    
    // Close file
    inFile.close();
    
    return true;
}// End readFile

//***************************************************************************************
// Definition insertManager
//
//***************************************************************************************
bool insertManager (listHead *aList)
{
    string tName;
    int tNumber;
    string tStreet;
    string tType;
    
    cout << endl;
    cout << "\n========================= I - I N S E R T =========================";
    
    cout << "\nEnter restaurant name: ";
    getline(cin, tName);
    
    //getline, check
    cout << "\nEnter street number: ";
    cin >> tNumber;
    
    cout << "\nEnter street name: ";
    getline(cin, tStreet);
    
    cout << "\nEnter type: ";
    getline(cin, tType);
    
    //cout << "\nEnter cost: ";
    //getline(cin, tCost);
    return true;

}

//***************************************************************************************
// Definition displayMenu
//
//***************************************************************************************
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
    cout << "\n=  Q - Quit                                                       =";
    cout << "\n===================================================================\n";

}// End displayMenu

//***************************************************************************************
// Definition getUserInput
//
//***************************************************************************************
char getUserInput()
{
    string userInput;
    
    cout << "\n======================== U S E R  I N P U T =======================";
    cout << "\nEnter a letter: ";
    getline(cin, userInput);
    
    validateUserInput(userInput[0]);
    
    cout << "===================================================================\n";

    return userInput[0];
}// End getUserInput

//***************************************************************************************
// Definition validateUserInput
//
//***************************************************************************************
void validateUserInput(char &tUserInput)
{
    string userInput;
    tUserInput = tolower(tUserInput);
    
    while (tUserInput != 'i' & tUserInput != 'd' & tUserInput != 'p' & tUserInput != 'n'
           & tUserInput != 'k' & tUserInput != 'h' & tUserInput != 't' & tUserInput != 's'
           & tUserInput != 'q')
    {
        cout << "\nYou have entered an invalid letter.";
        cout << "\nPlease enter a letter: ";
        getline(cin, userInput);
        tUserInput = userInput[0];
    }// End while
    
}// End validateUserInput

//***************************************************************************************
// Definition operationManager
//
//***************************************************************************************
void operationManager(listHead *aList, char tUserInput)
{
    if (tUserInput == 'i')
    {
        //aList->getHashPtr->insertHash();
    }
}