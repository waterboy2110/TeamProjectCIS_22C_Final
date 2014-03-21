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
//*************************************************************************************************************
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

///***********************************************************************************************************
// Definition of function addNode
// The funciton addNode has the argument RestaurantInfoPtr which is a pointer
// to restaurantInfo.
// In the function, dynamicaly allocate memeroy for newNode
// If newNode doesn't exist, return false; otherwise, return true and insert
// newnode in the BST in name order
//***********************************************************************************************************
bool BinarySearchTree:: addNode(restaurantInfo* RestaurantInfoPtr)
{
    BinaryNode* newNode = new BinaryNode(RestaurantInfoPtr); //dynamicaly allocate memeroy
    BinaryNode* parent = NULL;
    
    if(!newNode) // if no newNode
    {
        return false;
    }
    
    if(!getroot())   // if there is no any node on the tree, make root points to newNode
    {
        RootPtr= newNode;    // root is newNodePtr
    }
    else
    {
        
        BinaryNode* current = RootPtr;
        
        while(current!=nullptr) // find the right place for newNode to insert
        {
            parent= current;
            
            if( newNode->getrestaurantInfo()->getName() < current->getrestaurantInfo()->getName() )
            {
                current = current->getLeftChildPtr();
            }
            else
            {
                current = current->getRightChildPtr();
                
            }
        }
        
        if (parent->getrestaurantInfo()->getName()  > newNode->getrestaurantInfo()->getName())
            // parent's child pointer points to new node
        {
            
            parent->setLeftChildPtr(newNode);
        }
        else
        {
            parent->setRightChildPtr(newNode);
            
            
        }
        
        
    }
    
    return true;
    
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
        cout <<i<<". ";                 // print the level number
        cout << root->getrestaurantInfo()->getName() << "   " << root->getrestaurantInfo()->getNumber() <<endl;// print data
        
        // If right child exists
        if(root->getRightChildPtr())
        {
            for(int g=i; g>0;g--)
                cout << "     ";              // print the space
            printIndentedList(root->getRightChildPtr(),i);
            
        }
        // If left child exists
        if(root->getLeftChildPtr())
        {
            for(int g=i; g>0;g--)          // print the space
                cout << "     ";
            printIndentedList(root->getLeftChildPtr(),i);
            
        }
    }
}

//***********************************************************************************************************
// Definition of function SearchName
// The function SearchName searches for a matching name from argument passed in by the caller and returns
// a pointer to a BinaryNode. The function performs the search in a pre-order traversal using recursion.
// Pre - A pointer to the root of the three (or subtree) and the name of the restaurant.
// Post - A pointer to the matching node in the tree.
//*****************************************************************************************************************************
BinaryNode* BinarySearchTree::SearchName(BinaryNode* root, string name)const
{
    if(!root)// if no any node exists, return
    {
        return nullptr; //return nullptr
        
    }
    else// otherwise...
    {   // Find the mathcing name by comapring the string
        if(name < (root->getrestaurantInfo()->getName()))
        {
            // Recursively call with left child pointer
            return SearchName(root->getLeftChildPtr(), name);
        }
        else
        {
            
            if(name > (root->getrestaurantInfo()->getName()))
            {
                // Recursively call with right child pointer
                return SearchName(root->getRightChildPtr(), name);
            }
            else
            {
                return root; // return root if found
                
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
    // If there are no no more restauants to remove, return nullptr
    if (subTreePtr == nullptr)
    {
        // Not found here
        success = false;
        return nullptr;
    }
    
    // If item is in the root of some subtree (If found target in tree)
    if (subTreePtr->getrestaurantInfo()->getName() == DeName)
    {
        subTreePtr = removeNode(subTreePtr);    // Remove target
        success = true;
        return subTreePtr;
    }
    else
    {
        // If the name of the subtree is less than the name to delete 
        if (subTreePtr->getrestaurantInfo()->getName() > DeName)
        {
            // Search left of tree for target (recursively) to delete
            subTreePtr->setLeftChildPtr(removeRestaurant(DeName, subTreePtr->getLeftChildPtr(), success));
        }
        
        else
        {   // Otherwise, the name is greater than or equal to
            // Search right subtree
            subTreePtr->setRightChildPtr(removeRestaurant(DeName, subTreePtr->getRightChildPtr(),  success));
        }
        
        return subTreePtr;
    }  // end if
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
        root->SetRestaurantInfo(nullptr);
        
        delete root;
        root = nullptr;
        
        return  nullptr;
    }
    else if (root->getLeftChildPtr() == nullptr)  // Has rightChild only
    {
        BinaryNode* nodeToConnectPtr = root->getRightChildPtr();
        root->SetRestaurantInfo(nullptr);
        delete root;
        root = nullptr;
        
        return nodeToConnectPtr;
    }
    else if(root->getRightChildPtr() == nullptr) // Has left child only
    {
        BinaryNode* nodeToConnectPtr = root->getLeftChildPtr();
 
        // set pointer to restaurant Info to nullptr
        root->SetRestaurantInfo(nullptr);
        
        delete root;
        root = nullptr;
        
        return nodeToConnectPtr;
    }
    else  // Has two children
    {
        // Traditional way to remove a value in a node with two children
        restaurantInfo* newrestaurant = nullptr;
        BinaryNode* deNode = removeLeftmostNode(root->getRightChildPtr(), newrestaurant);
        
        root->setRightChildPtr(deNode);
        root->SetRestaurantInfo(newrestaurant);
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
    
    if (root->getLeftChildPtr() == nullptr)
    {
        // Assign restaurant object to be referened by reference
        Arestaurant = root->getrestaurantInfo();
        
        // Remove the node
        return removeNode(root);
    }
    else
    {
        root->setLeftChildPtr(removeLeftmostNode(root->getLeftChildPtr(), Arestaurant));
        return root;
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
bool BinarySearchTree::saveToFile(BinaryNode *binaryNodePtr)const
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

//***********************************************************************************************************
// Definition of destroyTree
//
// This function recursively calls itself to delete every node in the search tree until there are no more nodes
// to delete.
//***********************************************************************************************************
void BinarySearchTree:: DestroyTree(BinaryNode *root)
{
    if(root)
    {
        DestroyTree(root-> getRightChildPtr());
        DestroyTree(root -> getLeftChildPtr());
        delete root;        // delete node pointed by root which is BinaryNode pointer
        RootPtr= nullptr;   // make rootptr point to nullptr
    }
    
}



