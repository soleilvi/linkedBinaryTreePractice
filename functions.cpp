#include <random>
#include <chrono>
#include <iostream>
#include "LinkedBSearchTree.h"

#define MAX_NODE_VAL 200

/*bool generateRandomTree(const int& rangeMax, LinkedBTree<int>& bTree) {
    bool addedValues;
    int randNum;
    srand((unsigned) time(NULL));

    for(int i = 0; i < rangeMax; i++) {
        addedValues = false;
        randNum = rand() % (MAX_NODE_VAL + 1); // Random numbers from 1 to MAX_NODE_VAL

        addedValues = bTree.add(randNum);
        std::cout << randNum << std::endl;
    }

    return addedValues;
}*/

// For printing nodes in traversal functions
template<class ItemType>
void print(ItemType& item) {
    std::cout << item << ", ";
}

template<class ItemType>
void minValue(ItemType& item) {
    // Assign the minimum value of the two to the item
    std::cout << item << std::endl;
}