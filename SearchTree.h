//
// Created by Melanie Palomino on 4/14/20.
//

#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include "comparable.h"

#include <iostream>
#include <cassert>
#include <string> //for now

using namespace std;

class SearchTree{
    //output the frequency table in sorted order.
    // This should be an inorder traversal of your tree. Your output should look similar to:. 1
    //a 3
    //e 1
    //f 1
    //h 7
    //...
    friend ostream& operator<<(ostream& output, const SearchTree& st);

public:
    //***************** Constructors & Destructors **********************
    SearchTree();
    SearchTree(const SearchTree& st);
    ~SearchTree();
    //*******************************************************************

    //***************** Overloaded Operators ****************************
    const SearchTree& operator=(const SearchTree& right);

    //two trees are equal only if they have the same data, the same structure,
    // and the same number of occurrences for each comparable
    bool operator==(const SearchTree& right) const;

    //checks if Trees are not equal
    bool operator!=(const SearchTree& right) const;
    //*******************************************************************

    //******************* Mutator Functions *****************************

    //inserts a Comparable into the tree or increments the count if it is already in the tree.
    // This method should return false if the Comparable is found (and, thus, not inserted).
    // Ownership of the memory is transferred to the tree only if the object is not found in
    // the tree (in which case it must later be deallocated by the tree).
    bool insert(Comparable* newItem);

    //removes one occurrence of a Comparable from the tree. If it is the last occurrence,
    // remove the node. Return false if the Comparable is not found.
    bool remove(const Comparable& comp);

    //removes and deallocates all of the data from the tree.
    void makeEmpty();
    //*******************************************************************

    //******************* Mutator Functions *****************************

    //Finds a Comparable in the tree using a key stored in the parameter.
    // This is useful for cases where the Comparable stores more than the sorting key.
    // Return nullptr if not found.
    const Comparable* retrieve(const Comparable& item) const;

    // returns the height of the node storing the Comparable in the tree.
    // A leaf has height 0. Return -1 if the Comparable is not found.
    int height(const Comparable& comp) const;


    void print2D();

    //*******************************************************************

private:
    struct Node{
        //kind of like int data or char data
        Comparable* dataPtr; //pointer to comparible
        Node* rightPtr; //right child
        Node* leftPtr; //left child
        int frequency; //keep track of nodes
    };

    Node* root; //pointer to root

    int Nodenums; //helps keep track of nodes

    //private method to help deep copy
    static void copyHelper(Node* otherRoot, Node* &thisRoot);

    //compare helper
    bool comparingHelper(Node* otherRoot, Node* thisRoot) const;

    const Comparable* retrieveHelper(Node* curr, const Comparable& item) const;

    //display helper
    static void displayHelper(ostream& output,Node* curr);

    bool isEmpty() const;

    static void clear(Node* curr);

    int heightAddition(Node* curr) const;

    void positionFinder(Node*& newPtr, Node* curr, const Comparable& item) const;

    void deleteNode(Node*& curr);

    bool removeRecursive(Node*& curr, const Comparable& item);

    Comparable* replaceWithSmallest(Node*& curr);

    bool insertHelper(Node* curr, Comparable* newItem);

    static ostream& displaying(ostream& output, Node* curr);


    static void print2DUtil(Node *root, int space);
};

#endif //SEARCHTREE_H
