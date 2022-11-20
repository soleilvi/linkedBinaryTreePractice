#include "LinkedBTree.h"
#include <algorithm>
#include <stdexcept>

/* 
-- PROTECTED CLASSES -- 
*/
// Gets height through recursion
template<class ItemType>
int LinkedBTree<ItemType>::getHeightHelper(LinkedBTreeNode<ItemType>* subTreePtr) const 
{
    if (subTreePtr == nullptr) 
        return 0;
    else 
        return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                            getHeightHelper(subTreePtr->getRightChildPtr()));
}

// Gets the number of nodes through recursion
template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodesHelper(LinkedBTreeNode<ItemType>* subTreePtr) const 
{
    if (subTreePtr == nullptr) 
        return 0;

    int leftCount = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    int rightCount = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());

    return leftCount + rightCount + 1;  // +1 for node
}

// Adds values to the binary tree while making sure it stays balanced
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::balancedAdd(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr)
{
    if (subTreePtr == nullptr) 
    {
        return newNodePtr;
    } 
    else 
    {
        int leftChildHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
        int rightChildHeight = getHeightHelper(subTreePtr->getRightChildPtr());
        bool subTreeHeightsAreEqual = (leftChildHeight - rightChildHeight) == 0;
        
        if (subTreeHeightsAreEqual) 
            subTreePtr->setLeftChildPtr(balancedAdd(subTreePtr->getLeftChildPtr(), newNodePtr));
        else 
            subTreePtr->setRightChildPtr(balancedAdd(subTreePtr->getRightChildPtr(), newNodePtr));
    }

    return subTreePtr;
}

// Removes nodes through recursion. It calls moveValuesUpTree() to 
// remove the actual node; this helps return the modified root tree.
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
{ 
    LinkedBTreeNode<ItemType>* nodeToRemovePtr;

    if (subTreePtr != nullptr)
    {
        if (subTreePtr->getItem() == target)
        {
            subTreePtr = moveValuesUpTree(subTreePtr);
            isSuccessful = true;
        }
        else
        {
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
        }
    }

    return subTreePtr;
}

// Helper for the removeValue function. It takes in the subtree of the
// node the user wants to remove and moves up the items of the nodes 
// below it so that it only has to delete a leaf node.
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::moveValuesUpTree(LinkedBTreeNode<ItemType>* subTreePtr)
{
    LinkedBTreeNode<ItemType>* nodeToRemovePtr;

    if (subTreePtr != nullptr)
    {
        if (subTreePtr->isLeaf())
        {
            delete subTreePtr;
            return nullptr;
        }
        else
        {
            int leftChildHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
            int rightChildHeight = getHeightHelper(subTreePtr->getRightChildPtr());
            bool subTreeHeightsAreEqual = (leftChildHeight - rightChildHeight) == 0;

            if (subTreeHeightsAreEqual)
            {
                subTreePtr->setItem(subTreePtr->getRightChildPtr()->getItem());   // Set the current item to its right child's item
                subTreePtr->setRightChildPtr(moveValuesUpTree(subTreePtr->getRightChildPtr()));
            }
            else
            {
                subTreePtr->setItem(subTreePtr->getLeftChildPtr()->getItem());    // Set the current item to its left child's item
                subTreePtr->setLeftChildPtr(moveValuesUpTree(subTreePtr->getLeftChildPtr()));
            }
        }
    }

    return subTreePtr;
}

// Finds a node through its item data using recursion
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::findNode(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const 
{
    LinkedBTreeNode<ItemType>* foundPtr;
    
    if (subTreePtr != nullptr) 
    {
        if (subTreePtr->getItem() == target)
        {
            isSuccessful = true;
            return subTreePtr;
        }
        else
        {
            foundPtr = findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);

            // Ensure that we have checked all leftmost nodes before going to their right children
            if (foundPtr == nullptr)
                foundPtr = findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
            
            return foundPtr;  // If not null, it's our item
        }
    }

    return nullptr;  // We will only have gotten this return statement through leaves
}

// Deletes the entire tree through recursion
template<class ItemType>
void LinkedBTree<ItemType>::destroyTree(LinkedBTreeNode<ItemType>* subTreePtr) 
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());

        // std::cout << subTreePtr->getItem() << std::endl;
        if (subTreePtr == rootPtr) 
        {
            rootPtr = nullptr;
            delete subTreePtr;
        } 
        else 
        {
            delete subTreePtr;
        }
    }
}

// Goes through nodes in a pre-order fashion using recursion
template<class ItemType>
void LinkedBTree<ItemType>::preorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const 
{
    if (treePtr != nullptr) 
    {
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

// Goes through nodes in an in-order fashion using recursion
template<class ItemType>
void LinkedBTree<ItemType>::inorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const
{
    if (treePtr != nullptr)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

// Goes through nodes in a post-order fashion using recursion
template<class ItemType>
void LinkedBTree<ItemType>::postorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const 
{
    if (treePtr != nullptr) 
    {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}


/* 
-- PUBLIC CLASSES -- 
*/
// Constructor
template<class ItemType>
LinkedBTree<ItemType>::LinkedBTree() : rootPtr(nullptr) {}

// Returns a bool indicating whether the tree is empty or not
template<class ItemType>
bool LinkedBTree<ItemType>::isEmpty() const 
{
    return rootPtr == nullptr;
}

// Returns the height of the tree
template<class ItemType>
int LinkedBTree<ItemType>::getHeight() const 
{
    return getHeightHelper(rootPtr);  // rootPtr used to be just "root"?
}

// Returns how many nodes there are in the tree
template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodes() const 
{
    return getNumberOfNodesHelper(rootPtr);
}

// Returns the item of the root if it's not empty. If it's empty, it
// throws an error.
template<class ItemType>
ItemType LinkedBTree<ItemType>::getRootData() const 
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
        return 1;   // Since main.cpp returns a 1 when there's an error...lol
    }
}

// Calls balancedAdd to add a new node into the tree and returns 
// whether it was successful or not
template<class ItemType>
bool LinkedBTree<ItemType>::add(const ItemType& newData) 
{
    LinkedBTreeNode<ItemType>* newNodePtr = new LinkedBTreeNode<ItemType>(newData, nullptr, nullptr);

    rootPtr = balancedAdd(rootPtr, newNodePtr);

    return true;
}

// Calls the removeValue method to remove a value defined by the user
// and returns whether it was successful or not
template<class ItemType>
bool LinkedBTree<ItemType>::remove(const ItemType& anEntry) 
{
    bool removed = false;  // Changed in removeValue() if the value could be removed

    rootPtr = removeValue(rootPtr, anEntry, removed);
    
    return removed;
}

// Calls destroyTree to clear it
template<class ItemType>void LinkedBTree<ItemType>::clear() 
{ 
    destroyTree(rootPtr);
}

// Returns the value that the user wants; it throws an error if it's
// not in the tree
template<class ItemType>
ItemType LinkedBTree<ItemType>::getEntry(const ItemType& anEntry) const 
{
    bool found = false;
    LinkedBTreeNode<ItemType>* entry = findNode(rootPtr, anEntry, found);

    try
    {
        if (found)
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

// Returns whether or not the value the user wants is in the tree
template<class ItemType>
bool LinkedBTree<ItemType>::contains(const ItemType& anEntry) const 
{
    bool found = false;

    findNode(rootPtr, anEntry, found);

    return found;
}

// Calls the preorder method to traverse through the tree in that 
// fashion
template<class ItemType>
void LinkedBTree<ItemType>::preorderTraverse(void visit(ItemType&)) const 
{
    preorder(visit, rootPtr);
}

// Calls the inorder method to traverse through the tree in that 
// fashion
template<class ItemType>
void LinkedBTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
    inorder(visit, rootPtr);
}

// Calls the postorder method to traverse through the tree in that 
// fashion
template<class ItemType>
void LinkedBTree<ItemType>::postorderTraverse(void visit(ItemType&)) const {
    postorder(visit, rootPtr);
}

// Destructor
template<class ItemType>LinkedBTree<ItemType>::~LinkedBTree() {
    clear();
}