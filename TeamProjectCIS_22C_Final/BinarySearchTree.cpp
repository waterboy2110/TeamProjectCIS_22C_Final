//***********************************************************************************************************
// Implementation file for binary search tree class
// Team Project - Restaurants in Cupertino (Group 3)                         3/9/14          Mac OS X - xCode
//
// BinaryTree.cpp class implements the methods that provide access to the root of the tree as well as methods
// for add / remove node, search by name, remove by object (restaurant), print the indented tree and save the
// tree to a file.
//***********************************************************************************************************

#include "BinarySearchTree.h"
#include <fstream>
#include <vector>

//***********************************************************************************************************
// Constructor
// Sets the root pointer to nullptr
//***********************************************************************************************************
BinarySearchTree::BinarySearchTree():RootPtr(nullptr)
{
}

//***********************************************************************************************************
// Definition of getRoot
// Pre none
// Post - Returns a pointer to root of the tree
//***********************************************************************************************************
BinaryNode*  BinarySearchTree::getroot()const
{
    return RootPtr;
}

//***********************************************************************************************************
// Definition of function addNode
// The funciton addNode has the argument RestaurantInfoPtr which is a pointer
// to restaurantInfo.
// In the function, dynamicaly allocate memeroy for newNode
// If newNode doesn't exist, return false; otherwise, return true and insert
// newnode in the BST in name order
//***********************************************************************************************************
bool BinarySearchTree:: addNode(restaurantInfo* RestaurantInfoPtr)
{
    BinaryNode* newNode = new BinaryNode(RestaurantInfoPtr);                                // Dynamicaly allocate memeroy
    BinaryNode* parent=NULL;                                                                // And set the parent to null
    
    if(!newNode)                                                                            // if no newNode return false
    {
        return false;
    }
    
    if(!getroot())                                                                          // if there is no any node on the tree, make root points to newNode
    {
        RootPtr= newNode;                                                                   // root is newNodePtr
    }
    else
    {
        BinaryNode* current = RootPtr;
        while(current!=nullptr)                                                             // Walk the tree and find the right place for newNode to insert
        {                                                                                   // based on the restaurant object name. Determine which side of
            parent= current;                                                                // tree to insert.
            
            if( newNode->getrestaurantInfo()->getName() < current->getrestaurantInfo()->getName() )
            {
                current = current->getLeftChildPtr();
            }
            else
            {
                current = current->getRightChildPtr();
            }
        }
        
        if (parent->getrestaurantInfo()->getName()  > newNode->getrestaurantInfo()->getName())  // parent's child pointer points to new node
        {
            parent->setLeftChildPtr(newNode);
        }
        else
        {
            parent->setRightChildPtr(newNode);
        }
    }
    
    return true;                                                                                // Success in adding a new node
    
}

//***********************************************************************************************************
// Definition of function printIndentedList
// The function printIndentefList prints the list in the form of an indented tree showing the level number.
// The method is recursive and in the recursion a space is passed in to indent the tree.
// Argument i is for level number, and root is for accessing each member of the class BinaryNode.
// Pre - A node to the tree and an int for formating the output showing level numbers
// Post - Tree is printed in a tabbed format with the level of each node displayed for each object.
//***********************************************************************************************************
void BinarySearchTree::printIndentedList(BinaryNode* root, int i)const
{
    if(root)// check if the tree exsits
    {
        i++;
        cout <<i<<". ";                                                                     // Print the level number
        cout << root->getrestaurantInfo()->getName() << "   "                               // Print the restaurent name
             << root->getrestaurantInfo()->getNumber() <<endl;                              // Print the restaurant number (the key)
        
        if(root->getRightChildPtr())                                                        // if a right child exists
        {
            for(int g=i; g>0;g--)
                cout << "     ";                                                            // print the spaces
            printIndentedList(root->getRightChildPtr(),i);                                  // and recursively call this function
            
        }
        if(root->getLeftChildPtr())                                                         // if a left child exists
        {
            for(int g=i; g>0;g--)
                cout << "     ";                                                            // print the spaces
            printIndentedList(root->getLeftChildPtr(),i);                                   // and recursively call this function
        }
    }
}

//***********************************************************************************************************
// Definition of function SearchName
// The function SearchName searches for a matching name from argument passed in by the caller and returns
// a pointer to a BinaryNode. The function performs the search in a pre-order traversal using recursion.
// Pre - A pointer to the root of the three (or subtree) and the name of the restaurant.
// Post - A pointer to the matching node in the tree.
//***********************************************************************************************************
BinaryNode* BinarySearchTree::SearchName(BinaryNode* root, string name)const
{
    if(!root)                                                                                  // if no any node exists we are done, exit.
    {
        return nullptr;
    }
    
    else                                                                                        // Search the tree by name:
    {
        if(name < (root->getrestaurantInfo()->getName()))                                       // If the target name is less than the search name
        {
            return SearchName(root->getLeftChildPtr(), name);                                   // recursively call this funciton with a left child pointer
        }
        else
        {
            if(name > (root->getrestaurantInfo()->getName()))                                   // If the target name is larger than the search name
            {
                return SearchName(root->getRightChildPtr(), name);                              // recursively call this function with the right child pointer
            }
            else
            {
                return root;                                                                      // return root if found (base case)
            }
        }
    }
}

//***********************************************************************************************************
// Definition of function removeRestaurant
// The funciton removeRestaurant recursively searches for the target in the tree. When the target is found
// the left or right pointers are updated by calling setLeftChildPtr / setRightChildPtr from the subTreePtr
// passes into each recursive call. Once the target is located removeResturant is called to delete the object.
// Pre - A string for the target name, a node to represent the tree (or subtree) and success or failure.
// Post - Returns a pointer to a node in the tree.
//***********************************************************************************************************
BinaryNode* BinarySearchTree::removeRestaurant(string DeName, BinaryNode* subTreePtr, bool & success)
{
    if (subTreePtr == nullptr)
    {
        success = false;                                                                            // If pointer is null return nullptr
        return nullptr;
    }
    
    if (subTreePtr->getrestaurantInfo()->getName() == DeName)                                       // If we have found our target in the tree
    {
        subTreePtr = removeNode(subTreePtr);                                                        // remove the target and return the subTree
        success = true;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getrestaurantInfo()->getName() > DeName)                                    // Otherwise look to the left of the tree for the target
        {                                                                                           // and recursively call this function with the left child pointer
            subTreePtr->setLeftChildPtr(removeRestaurant(DeName, subTreePtr->getLeftChildPtr(), success));
        }
        else                                                                                        // Look to the right side of the tree
        {                                                                                           // and call this function with the right child pointer
            subTreePtr->setRightChildPtr(removeRestaurant(DeName, subTreePtr->getRightChildPtr(),  success));
        }
        
    return subTreePtr;                                                                               // return a node pointer to the subtree
    } // end else
}

//***********************************************************************************************************
// Definition of removeNode
// The removeNode function is a helper function to the removeRestaurant method. This funciton determines if a
// node is a leaf, has a right child or has two children. When the target node is found the links to the parent
// and child are updated and the node is deleted. If the node is a leaf (has null left and right pointers) it
// will be deleted. If the node has only a right pointer the links are updated and the node is deleted. If the
// node has both left and right the method removeLeftMostNode is called against the right child and the links
// to the restaurant and node are updated.
// Pre - A pointer to the root of the tree.
// Post - The target node is removed. The links are updated in the case where the target has children and the
//        node is deleted.
// ** Not implemented as of this writing ** The hashTables delete methods are also called so that the tree
//                                          and the table remain in sync.
//***********************************************************************************************************
BinaryNode* BinarySearchTree:: removeNode(BinaryNode* root )
{
    
    string tempName="a";
    
    if (root->isLeaf())
    {
        // addressNum= root->getrestaurantInfo()->getNumber();                                          // **REMOVE IF NOT USED**
        root->SetRestaurantInfo(nullptr);                                                               // set pointer to restaurantInfo to nullptr
        
        // tempName = root->getrestaurantInfo()->getName();                                             // **REMOVE IF NOT USED**
        delete root;                                                                                    // delete the root
        root = nullptr;                                                                                 // and set the pointer to null
        
        // aHashTable->deleteHash(DeAddressNum, tempName);                                              // delete from hash // **REMOVE IF NOT USED**
        
        return  nullptr;                                                                                // return a nullptr - the node was a leaf
    }
    else if (root->getLeftChildPtr() == nullptr)                                                        // Node has rightChild only
    {
        //cout << "\nBST: RIGHT";

        BinaryNode* nodeToConnectPtr = root->getRightChildPtr();                                        // Set the node to connect to the right child
        // addressNum= root->getrestaurantInfo()->getNumber();                                          // **REMOVE IF NOT USED**
        
        root->SetRestaurantInfo(nullptr);                                                               // set pointer to restaurantInfo to nullptr
        delete root;                                                                                    // and delete the parent and set the pointer to null
        root = nullptr;
                                                                                                        // delete from hash
        // aHashTable->deleteHash(DeAddressNum, tempName);                                              // **REMOVE IF NOT USED**
        
        return nodeToConnectPtr;                                                                        // Return the newly connected node
    }
    else if(root->getRightChildPtr() == nullptr)                                                        // Node has left child only
    {
        BinaryNode* nodeToConnectPtr = root->getLeftChildPtr();                                         // set the node to connect to the left child
        
        //   addressNum= root->getrestaurantInfo()->getNumber();                                        // **REMOVE IF NOT USED**
        
        root->SetRestaurantInfo(nullptr);                                                               // set pointer to restaurantInfo to nullptr
        delete root;                                                                                    // and delete the parent and set the pointer to null
        root = nullptr;
       
        //  aHashTable->deleteHash(DeAddressNum, tempName);                                              // delete from hashTable
        
        return nodeToConnectPtr;                                                                         // and return the newly connected pointer
    }
    else                                                                                                 // The node has two children
    {
        //cout << "\nBST: TWO";
                                                                                                         // Traditional way to remove a value in a node with two children
        restaurantInfo* newrestaurant = nullptr;
        BinaryNode* deNode = removeLeftmostNode(root->getRightChildPtr(), newrestaurant);                // Assign a new right child pointer to the roots parent
        //   addressNum= root->getrestaurantInfo()->getNumber();                                         // **REMOVE IF NOT USED**
        
        root->setRightChildPtr(deNode);                                                                  // Set the new node as the parents right child
        root->SetRestaurantInfo(newrestaurant);                                                          // and update the restaurantInfo and return the root
        return root;
    }
}

//***********************************************************************************************************
// Definition of function removeLeftMostNode.
// The function removeLeftMostNode is a recursive function that calls itself until the parents left pointer is
// null.
// Pre - A pointer to the parent node and a pointer to a resturant object
// Post - Returns a pointer to the target parent.
//***********************************************************************************************************
BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* root, restaurantInfo* &Arestaurant)
{
    
    if (root->getLeftChildPtr() == nullptr)                                                             // Base Case
    {
        Arestaurant = root->getrestaurantInfo();                                                        // Assign the parent restaurant object and remove the node
        return removeNode(root);
    }
    else
    {
        root->setLeftChildPtr(removeLeftmostNode(root->getLeftChildPtr(), Arestaurant));                // else - call this function and set the left child pointer
        return root;                                                                                    // return the parent
    }  // end if
}

//***********************************************************************************************************
// Definition of function saveToFile.
// The functon saveToFile save the BST to a file using a vector to queue each element of the tree. For the
// current pointer keep traversing left child and pushing it into the queue. When a null node is reached pop
// an element of the queue (back of queue) set it to current and print it. Then set current to right and repeat
// the process. When the queue is empty you are done processing the tree.
// Pre - A pointer to the root of the BST
// Post - Writes to file from the BST.
//***********************************************************************************************************
bool BinarySearchTree::saveToFile(BinaryNode *binaryNodePtr)
{
    ofstream outFile;
    string fileName ="RestaurantsOutfile.txt";
    bool success = true;
    
    bool done = false;
    vector<BinaryNode> vBST;
    
    
    // Open file to write, if unable, display error and exit with false
    outFile.open(fileName);
    if (!outFile)
    {
        cout << "Error opening " << fileName << "!\n";
        return false;
    }
    cout << "Saving File...\n";
    
    BinaryNode *current = binaryNodePtr;
    while(!done)
    {
        if(current)
        {
            vBST.push_back(*current);
            current = current->getLeftChildPtr();
        }
        else
        {
            if(vBST.empty())
            {
                done = true;
            }
            else
            {
                current = &vBST.back();
                vBST.pop_back();
                outFile << current->getrestaurantInfo()->getName() << endl;
                outFile << to_string(current->getrestaurantInfo()->getNumber()) << endl;
                outFile << current->getrestaurantInfo()->getStreet() << endl;
                outFile << current->getrestaurantInfo()->getType() << endl;
                current = current->getRightChildPtr();
            }
        }
    }
    
    outFile.close();
    
    if (!success)
        return false;
    
    return true;
}



