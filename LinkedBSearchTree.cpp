/*
Methods used to implement the LinkedBSearchTree class.

By Soleil Vivero
11/20/22
*/

#include "LinkedBSearchTree.h"

/* 
-- PROTECTED CLASSES -- 
*/
// Adds a node to the tree in accordance to whether its value is
// greater than or smaller than the root value. Uses recursion.
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::placeNode(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;
    else if (subTreePtr->getItem() > newNodePtr->getItem())  // New node less than root
        subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
    else if (subTreePtr->getItem() < newNodePtr->getItem())  // New node greater than root
        subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));

    return subTreePtr;
}

// Implements the logic required to remove the desired value from the
// tree using recursion, but it uses ahelper function to get rid of
// the actual node in the tree.
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful) 
{   
    if (subTreePtr != nullptr)
    {
        if (subTreePtr->getItem() == target)
        {
            subTreePtr = removeNode(subTreePtr);
            isSuccessful = true;
        }
        else if (subTreePtr->getItem() > target)
        {
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
        } 
        else
        {
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
        }
    }

    return subTreePtr;
}

// Deletes the node from the tree called from the removeValue method
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeNode(LinkedBTreeNode<ItemType>* nodePtr)
{   
    bool targetIsLeaf = nodePtr->isLeaf();
    bool targetHasChild = (nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr) ||
                          (nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr);

    if (targetIsLeaf)
    {
        delete nodePtr;
        nodePtr = nullptr;

        return nodePtr;
    }
    else if (targetHasChild)
    {
        LinkedBTreeNode<ItemType>* newNodePtr;

        if (nodePtr->getLeftChildPtr() != nullptr)  // Node has a left child, not a right one
            newNodePtr = nodePtr->getLeftChildPtr();
        else
            newNodePtr = nodePtr->getRightChildPtr();
    
        delete nodePtr;
        nodePtr = nullptr;

        return newNodePtr;
    }
    else  // Target has children
    {
        ItemType newNodeValue;
        LinkedBTreeNode<ItemType>* tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);

        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(newNodeValue);

        return nodePtr;
    }
}

// Called in the removeNode method to help remove nodes with two 
// children
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeLeftmostNode(LinkedBTreeNode <ItemType>* nodePtr, ItemType& inorderSuccessor)
{
    if (nodePtr->getLeftChildPtr() == nullptr)  // If node is a leaf
    {
        inorderSuccessor = nodePtr->getItem();
        return removeNode(nodePtr);  // Returns nullptr
    }
    else 
    {
        // Keep calling the function until you find a leaf
        // Return updated tree
        LinkedBTreeNode<ItemType>* tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
        nodePtr->setLeftChildPtr(tempPtr);
        return nodePtr;
    } 
}

// Finds the node containing the value the user wants and returns it. 
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::findNode(LinkedBTreeNode<ItemType>* treePtr, const ItemType& target) const
{
    LinkedBTreeNode<ItemType>* targetPtr;

    if (treePtr != nullptr)
    {
        if (treePtr->getItem() == target) 
        {
            return treePtr;
        }
        else
        {
            if (treePtr->getItem() > target)  // Target is smaller than root
                targetPtr = findNode(treePtr->getLeftChildPtr(), target);
            else
                targetPtr = findNode(treePtr->getRightChildPtr(), target);
            
            return targetPtr;
        }
    }

    return nullptr;
}


/* 
-- PUBLIC CLASSES -- 
*/
template<class ItemType>
LinkedBSearchTree<ItemType>::LinkedBSearchTree() : rootPtr(nullptr) {}

template<class ItemType>
bool LinkedBSearchTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template<class ItemType>
int LinkedBSearchTree<ItemType>::getHeight() const
{
    return LinkedBTree<ItemType>::getHeightHelper(rootPtr);
}

template<class ItemType>
int LinkedBSearchTree<ItemType>::getNumberOfNodes() const
{
    return LinkedBTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType LinkedBSearchTree<ItemType>::getRootData() const
{
    try 
    {
        if (rootPtr == nullptr)
            throw std::out_of_range("Root is empty.");
        else
            return rootPtr->getItem();
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}

template<class ItemType>
bool LinkedBSearchTree<ItemType>::add(const ItemType& newData)
{
    LinkedBTreeNode<ItemType>* newSubTreePtr = new LinkedBTreeNode<ItemType>(newData, nullptr, nullptr);

    rootPtr = placeNode(rootPtr, newSubTreePtr);

    return true;
}

template<class ItemType>
bool LinkedBSearchTree<ItemType>::remove(const ItemType& data)
{
    bool removed = false;

    std::cout << "Node to remove: " << data << std::endl;
    rootPtr = removeValue(rootPtr, data, removed);
    
    return removed;
}

template<class ItemType>
void LinkedBSearchTree<ItemType>::clear()
{
    LinkedBTree<ItemType>::destroyTree(rootPtr);
}

template<class ItemType>
ItemType LinkedBSearchTree<ItemType>::getEntry(const ItemType& anEntry) const
{
    LinkedBTreeNode<ItemType>* entry = findNode(rootPtr, anEntry);

    try
    {
        if (entry != nullptr)
            return entry->getItem();
        else
            throw std::invalid_argument("Item not found.");
    } 
    catch (const std::invalid_argument& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}

template<class ItemType>
bool LinkedBSearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    return findNode(rootPtr, anEntry) != nullptr;  // False if nullptr
}

template<class ItemType>
void LinkedBSearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    LinkedBTree<ItemType>::preorder(visit, rootPtr);
}

template<class ItemType>
void LinkedBSearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    LinkedBTree<ItemType>::inorder(visit, rootPtr);
}

template<class ItemType>
void LinkedBSearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    LinkedBTree<ItemType>::postorder(visit, rootPtr);
}

template<class ItemType>
LinkedBSearchTree<ItemType>::~LinkedBSearchTree()
{
    clear();
}
