#ifndef LINKED_BTREE 
#define LINKED_BTREE
#include "TreeInterface.h"
#include "LinkedBTreeNode.h"

template<class ItemType> 
class LinkedBTree: public TreeInterface<ItemType> { 
private: 
    LinkedBTreeNode<ItemType>* rootPtr;

protected:
    int getHeightHelper(LinkedBTreeNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(LinkedBTreeNode<ItemType>* subTreePtr) const;
    LinkedBTreeNode<ItemType>* balancedAdd(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr);  // Used to be auto
    LinkedBTreeNode<ItemType>* removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
    LinkedBTreeNode<ItemType>* moveValuesUpTree(LinkedBTreeNode<ItemType>* subTreePtr);
    LinkedBTreeNode<ItemType>* findNode(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const;
    void destroyTree(LinkedBTreeNode<ItemType>* subTreePtr);
    void preorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;

public:
    LinkedBTree();
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    ItemType getRootData() const;
    bool add(const ItemType& newData); 
    bool remove(const ItemType& data); 
    void clear();
    ItemType getEntry(const ItemType& anEntry) const;
    bool contains(const ItemType& anEntry) const; 
    
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;

    ~LinkedBTree();
};

#include "LinkedBTree.cpp"
#endif