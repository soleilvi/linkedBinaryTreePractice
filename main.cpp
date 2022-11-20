#include <iostream>
#include <algorithm>
#include "functions.cpp"
#include "LinkedBTree.h"
#include "LinkedBSearchTree.h"

using namespace std;  // Since Erin said this was okay for now, I'll use it for now

int main() {
    LinkedBTree<int> tree;
    int wantedItem = 30;
    string emptyStatus;

    // cout << "Root data: " << tree.getRootData() << endl;

    // tree.add(60);
    // tree.add(20);
    // tree.add(70);
    // tree.add(10);
    // tree.add(40);
    // tree.add(30);
    // tree.add(50);
    // tree.add(80);
    // tree.add(65);

    cout << (tree.isEmpty() ? "Tree is empty" : "Tree is not empty") << endl;

    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);
    tree.add(6);
    tree.add(7);
    tree.add(8);
    tree.add(9);
    tree.add(10);
    tree.add(11);
    tree.add(12);
    tree.add(13);
    tree.add(14);
    tree.add(15);
    tree.add(16);
    tree.add(17);
    tree.add(18);
    tree.add(19);
    tree.add(20);
    tree.add(21);
    tree.add(22);
    tree.add(23);
    tree.add(24);
    tree.add(25);
    tree.add(26);
    tree.add(27);
    tree.add(28);
    tree.add(29);
    tree.add(30);

    tree.preorderTraverse(&print);
    cout << endl;
    tree.inorderTraverse(&print);
    cout << endl;
    tree.postorderTraverse(&print);
    cout << endl;

    cout << (tree.isEmpty() ? "Tree is empty" : "Tree is not empty") << endl;
    cout << "Height: " << tree.getHeight() << endl;
    cout << "Nodes: " << tree.getNumberOfNodes() << endl;
    cout << "Root data: " << tree.getRootData() << endl;
    cout << "Is the item we want in the tree?: " << (tree.contains(wantedItem) ? "Yes\n" : "No\n");
    cout << "Item we want: " << tree.getEntry(wantedItem) << endl;

    tree.remove(wantedItem);
    cout << "Nodes: " << tree.getNumberOfNodes() << endl;

    tree.clear();
    cout << (tree.isEmpty() ? "Tree is empty" : "Tree is not empty") << endl;
}