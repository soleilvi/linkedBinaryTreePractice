/*
Methods used to implement the LinkedBTreeNode class.

By Soleil Vivero
11/20/22
*/

#include "LinkedBTreeNode.h"

// CONSTRUCTORS
template<class ItemType>
LinkedBTreeNode<ItemType>::LinkedBTreeNode() {
    item = 0;
    leftChildPtr = nullptr;
    rightChildPtr = nullptr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>::LinkedBTreeNode(const ItemType& newData, LinkedBTreeNode<ItemType>* left, LinkedBTreeNode<ItemType>* right) {
    item = newData;
    leftChildPtr = left;
    rightChildPtr = right;
}

// IDK BUT THIS IS DIFFERENT
template<class ItemType>
bool LinkedBTreeNode<ItemType>::isLeaf() const {
    return (leftChildPtr == nullptr && rightChildPtr == nullptr);
}

// SETTERS
template<class ItemType>
void LinkedBTreeNode<ItemType>::setItem(const ItemType& newData) {
    item = newData;
}

template<class ItemType>
void LinkedBTreeNode<ItemType>::setLeftChildPtr(LinkedBTreeNode<ItemType>* newLeftChildPtr) {
    leftChildPtr = newLeftChildPtr;
}

template<class ItemType>
void LinkedBTreeNode<ItemType>::setRightChildPtr(LinkedBTreeNode<ItemType>* newRightChildPtr) {
    rightChildPtr = newRightChildPtr;
}

// GETTERS
template<class ItemType>
ItemType LinkedBTreeNode<ItemType>::getItem() const {
    return item;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTreeNode<ItemType>::getLeftChildPtr() const {
    return leftChildPtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTreeNode<ItemType>::getRightChildPtr() const {
    return rightChildPtr;
}