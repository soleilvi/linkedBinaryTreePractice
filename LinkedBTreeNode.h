/*
Nodes used for binary trees. They can hold an item and two pointers 
for their children.

By Soleil Vivero
11/20/22
*/

#ifndef LINKED_BTREE_NODE 
#define LINKED_BTREE_NODE

template<class ItemType> 
class LinkedBTreeNode
{ 
private: 
    ItemType item;  
    LinkedBTreeNode<ItemType>* leftChildPtr;  
    LinkedBTreeNode<ItemType>* rightChildPtr;

public: 
    LinkedBTreeNode();
    LinkedBTreeNode(const ItemType& newData, 
                    LinkedBTreeNode<ItemType>* left, 
                    LinkedBTreeNode<ItemType>* right);
    bool isLeaf() const;
    void setItem(const ItemType& newData);
    void setLeftChildPtr(LinkedBTreeNode<ItemType>* newLeftChildPtr);
    void setRightChildPtr(LinkedBTreeNode<ItemType>* newRightChildPtr);
    ItemType getItem() const;
    LinkedBTreeNode<ItemType>* getLeftChildPtr() const;
    LinkedBTreeNode<ItemType>* getRightChildPtr() const;
};

#include "LinkedBTreeNode.cpp"
#endif