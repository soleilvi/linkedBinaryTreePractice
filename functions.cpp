/*
Functions for inserting values into a linked binary search tree and 
outputting its contents.

By Soleil Vivero
11/20/22
*/

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#include "LinkedBSearchTree.h"

#define MAX_NODE_VAL 200

// Inserts random numbers ranging from 1 to MAX_NODE_VAL into a linked
// binary search tree
void generateRandomTree(const int& rangeMax, LinkedBSearchTree<int>& bSearchTree) 
{
    int randNum;
    srand((unsigned) time(NULL));  // Our random seed

    for(int i = 0; i < rangeMax; i++) 
    {
        randNum = rand() % (MAX_NODE_VAL + 1);  // Random numbers from 1 to MAX_NODE_VAL
        bSearchTree.add(randNum);
    }
}

// For printing node values in traversal functions
template<class ItemType>
void print(ItemType& nodeItem) 
{
    std::cout << nodeItem << ", ";
}

// Prints the tree data asked from this assignment: the tree height
// and the outputs from the preorder, inorder, and postorder functions
void printTreeData(LinkedBSearchTree<int>& bSearchTree)
{
    std::cout << "Tree height: " << bSearchTree.getHeight() << std::endl << std::endl;

    std::cout << "Preorder Traverse:\n";
    bSearchTree.preorderTraverse(&print);
    std::cout << std::endl << std::endl;

    std::cout << "Inorder Traverse:\n";
    bSearchTree.inorderTraverse(&print);
    std::cout << std::endl << std::endl;

    std::cout << "Postorder Traverse:\n";
    bSearchTree.postorderTraverse(&print);
    std::cout << std::endl << std::endl;
}

// Makes a text file out of what the printTreeData function outputs
void generateTreeDataFile(LinkedBSearchTree<int>& bSearchTree, const char fileName[])
{
    /*
    I used the sample code from https://cplusplus.com/reference/ios/ios/rdbuf/
    to make cout print to my file.
    */
    std::streambuf *fileBuf, *backup;
    std::ofstream outFile(fileName);

    backup = std::cout.rdbuf();  // back up cout's streambuf

    fileBuf = outFile.rdbuf();   // get file's streambuf
    std::cout.rdbuf(fileBuf);    // assign streambuf to cout

    printTreeData(bSearchTree);

    std::cout.rdbuf(backup);     // restore cout's original streambuf

    outFile.close();
}