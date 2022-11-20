#include "LinkedBSearchTree.h"

// PROTECTED
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::placeNode(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr){
    if (subTreePtr == nullptr){
        return newNodePtr;
    }
    else if(subTreePtr->getItem() > newNodePtr->getItem()){
        LinkedBTreeNode<ItemType>* tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else if(subTreePtr->getItem() < newNodePtr->getItem()){
        LinkedBTreeNode<ItemType>* tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    } 
    return subTreePtr;
}

// FIX
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful) { 
    LinkedBTreeNode<ItemType>* newSubTreePtr;
    
    bool targetIsLeaf = subTreePtr->isLeaf() && subTreePtr->getItem() == target;
    bool targetHasLeftChild = (subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() == nullptr) &&
                              subTreePtr->getItem() == target;
    bool targetHasRightChild = (subTreePtr->getLeftChildPtr() == nullptr && subTreePtr->getRightChildPtr() != nullptr) &&
                               subTreePtr->getItem() == target;
    bool targetHasChildren = (subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() != nullptr) && 
                             subTreePtr->getItem() == target;

    std::cout << subTreePtr->getItem() << std::endl;

    if(targetIsLeaf) {              // Functional
        isSuccessful = true;
        delete subTreePtr;

        std::cout << "Leaf target found.\n";

        return nullptr;  // nullptr
    }
    else if(targetHasLeftChild) {   // Functional
        isSuccessful = true;
        newSubTreePtr = subTreePtr->getLeftChildPtr();
        delete subTreePtr;

        std::cout << "Target with left child found.\n";

        return newSubTreePtr;
    }
    else if(targetHasRightChild) {  // Functional
        isSuccessful = true;
        newSubTreePtr = subTreePtr->getRightChildPtr();
        delete subTreePtr;

        std::cout << "Target with right child found.\n";

        return newSubTreePtr;
    }
    else if(targetHasChildren) {    // Fix :(
        isSuccessful = true;
        LinkedBTreeNode<ItemType>* temp = subTreePtr->getLeftChildPtr();

        std::cout << "Target with children found.\n";

        // Find leftmost node
        while(temp != nullptr) {
            newSubTreePtr = temp;
            temp = temp->getLeftChildPtr();
        }

        // Delete the leftmost node
        temp = newSubTreePtr;
        delete temp;

        return newSubTreePtr;  // Replace the old root with the leftmost node

    }
    else {
        // If the current node was not the target, go into its subtrees until you find it
        if(subTreePtr->getLeftChildPtr() != nullptr) {
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
        }
        if(subTreePtr->getRightChildPtr() != nullptr) {
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
        }
    }

    std::cout << "Back: " << subTreePtr->getItem() << std::endl;

    return subTreePtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeLeftmostNode(LinkedBTreeNode <ItemType>* nodePtr, ItemType& inorderSuccessor){
    if(nodePtr->getLeftChildPtr() == nullptr){
        inorderSuccessor = nodePtr->getItem();
        return removeNode(nodePtr);
    }
    else { 
        LinkedBTreeNode<ItemType>* tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
        nodePtr->setLeftChildPtr(tempPtr);
        return nodePtr;
    } 
}
