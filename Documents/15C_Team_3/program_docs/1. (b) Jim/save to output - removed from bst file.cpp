// Removed from BST class/header file


bool saveToFile(BinaryNode* rootPtr) const;  // Save to output file


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

