/*
This program was meant to give us practice implementing linked binary
trees and linked binary search trees. We were provided with the code
for a few methods, but for the most part, we had to implement them all
ourselves.

The program adds 100 randomized nodes to a binary search tree and out-
puts the height, preorder, inorder, and postorder values of the tree 
to the terminal and a text file.

By Soleil Vivero
11/20/22
*/

#include <iostream>
#include <algorithm>

#include "functions.cpp"
#include "LinkedBSearchTree.h"

#define NUMBER_OF_NODES 100
#define FILE_NAME "BinarySearchTreeData.txt"

int main () 
{
    LinkedBSearchTree<int> tree;
    
    generateRandomTree(NUMBER_OF_NODES, tree);
    printTreeData(tree);
    generateTreeDataFile(tree, FILE_NAME);
}
