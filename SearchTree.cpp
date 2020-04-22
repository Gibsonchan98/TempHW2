//
// Created by Melanie Palomino on 4/14/20.
//

#include "SearchTree.h"



#include <string>
#include <iostream>

using namespace std;
#define COUNT 10
//***************** Constructors & Destructors **********************

//default constructor
SearchTree::SearchTree(){
    this-> root = nullptr;
    this->Nodenums = 0;
}

SearchTree::SearchTree(const SearchTree& st){
    this->Nodenums = st.Nodenums; //same amount of nodes
    //must initialize root
    copyHelper(st.root, this->root);
    //call overload operator to deep copy the tree

}


SearchTree::~SearchTree(){
    makeEmpty();
}
//*********************************************************************

//***************** Overloaded Operators ******************************
const SearchTree& SearchTree::operator=(const SearchTree& right){
    //if they are the same then return this
    if(right != *this) {
        //delete everything on tree
        this->makeEmpty();
        copyHelper(right.root, this->root);
    }
    return *this;
}

//two trees are equal only if they have the same data, the same structure,
// and the same number of occurrences for each comparable
bool SearchTree::operator==(const SearchTree& right) const{
    if(this->Nodenums != right.Nodenums || //these two should be the same
       //compares the height of root
       this->height(*root->dataPtr) != right.height(*right.root->dataPtr)){
        return false;
    }
    return comparingHelper(right.root, this->root);
}

//checks if Trees are not equal
bool SearchTree::operator!=(const SearchTree& right) const{
    if(this->Nodenums != right.Nodenums || //these two should be the same
       //compares the height of root
       this->height(*root->dataPtr) != right.height(*right.root->dataPtr)){
        return true;
    }
    return !comparingHelper(right.root, this->root);
}

//********************************************************************************

//******************* Mutator Functions ****************************************

//inserts a Comparable into the tree or increments the count if it is already in the tree.
// This method should return false if the Comparable is found (and, thus, not inserted).
// Ownership of the memory is transferred to the tree only if the object is not found in
// the tree (in which case it must later be deallocated by the tree).
bool SearchTree::insert(Comparable* newItem){
    if(isEmpty()){
        this->root = new Node;
        this->Nodenums++;
        this->root->dataPtr = newItem; //copy address so it points to same data
        this->root->rightPtr = this->root->leftPtr = nullptr;
        root->frequency = 1;
        return true;
    }
    return insertHelper(this->root, newItem);
}


bool SearchTree::insertHelper(Node *curr, Comparable *newItem) {
    //base case for addition
    if(*curr->dataPtr == *newItem){
        curr->frequency++;
        return false;
    }
    if(*newItem < *curr->dataPtr){
        //base case
        if(curr->leftPtr == nullptr){
            Node *newNode = new Node;
            newNode->dataPtr = newItem;
            curr->leftPtr = newNode;
            curr->leftPtr->frequency++;
            Nodenums++;
            return true;
        }
        return insertHelper(curr->leftPtr,newItem);
    }
    if(*newItem > *curr->dataPtr){
        if(curr->rightPtr == nullptr){
            Node *newNode = new Node;
            newNode->dataPtr = newItem;
            curr->rightPtr = newNode;
            curr->rightPtr->frequency++;
            Nodenums++;
            return true;
        }
        return insertHelper(curr->rightPtr,newItem);
    }
    return false;
}


//removes one occurrence of a Comparable from the tree. If it is the last occurrence,
// remove the node. Return false if the Comparable is not found.
bool SearchTree::remove(const Comparable& item){
    return removeRecursive(this->root, item);
}

bool SearchTree::removeRecursive(Node*& curr, const Comparable& item){
    if(curr != nullptr){
        //base case
        if(item == *curr->dataPtr){
            if(curr->frequency > 1){
                curr->frequency--;
            }
            else{
                deleteNode(curr);
            }
            return true;
        }
        if(item > *curr->dataPtr){
            return removeRecursive(curr->rightPtr,item);
        }
        else if(item < *curr->dataPtr){
            return removeRecursive(curr->leftPtr,item);
        }
    }
    return false;
}

void SearchTree::deleteNode(Node*& curr) {
    delete curr->dataPtr;
    curr->dataPtr = nullptr;
    //if it has no children
    if(curr->leftPtr == nullptr && curr->rightPtr == nullptr){
        delete curr;
        curr = nullptr;
        Nodenums--;
    }
    else if(curr->leftPtr == nullptr || curr->rightPtr == nullptr){
        Node* temp = curr;
        curr = curr->leftPtr == nullptr? curr->rightPtr : curr->leftPtr;
        delete temp;
        //temp = nullptr;
        Nodenums--;
    }
    else{
        curr->dataPtr = replaceWithSmallest(curr);
    }

}

Comparable* SearchTree::replaceWithSmallest(Node *&curr) {
    if(curr->leftPtr == nullptr){
        Comparable* item = curr->dataPtr;
        Node* temp = curr;
        curr = curr->rightPtr;
        delete temp;
        //temp = nullptr;
        Nodenums--;
        return item;
    }
    else{
        return replaceWithSmallest(curr->leftPtr);
    }
}

//removes and deallocates all of the data from the tree.
void SearchTree::makeEmpty() {
    clear(this->root);
}

void SearchTree::clear(Node *curr) {
    if(curr != nullptr){
        clear(curr->leftPtr);
        clear(curr->rightPtr);
        // delete curr->dataPtr;
        curr->dataPtr = nullptr;
        delete curr;
    }
}
//*****************************************************************************

//******************* Mutator Functions ****************************************

//inds a Comparable in the tree using a key stored in the parameter.
// This is useful for cases where the Comparable stores more than the sorting key.
// Return nullptr if not found.
const Comparable* SearchTree::retrieve(const Comparable& item) const{
    if(this->root != nullptr){
        return retrieveHelper(this->root, item);
    }
    return nullptr;
}
//helper retrieve Comprable pointer
const Comparable* SearchTree::retrieveHelper(Node *curr, const Comparable &item) const{
    if(curr == nullptr){
        return nullptr;
    }
    if(*curr->dataPtr == item){
        return curr->dataPtr;
    }
    if(item > *curr->dataPtr){
        return retrieveHelper(curr->rightPtr,item);
    }
    else{
        return retrieveHelper(curr->leftPtr,item);
    }
}

// returns the height of the node storing the Comparable in the tree.
// A leaf has height 0. Return -1 if the Comparable is not found.
int SearchTree::height(const Comparable& item) const{
    //check if in tree first
    if(this->retrieve(item) == nullptr){
        return -1;
    }
    if(this->root != nullptr){
        Node* locatedPtr;
        this->positionFinder(locatedPtr,this->root,item);
        if(locatedPtr != nullptr){
            return heightAddition(locatedPtr) - 1;
        }
        //not neccessary but just in case
        return -1;
    }
    return -1;
}

void SearchTree::positionFinder(Node*& newPtr,Node* curr, const Comparable &item) const {
    if(*curr->dataPtr == item){
        newPtr = curr;
    }
    else if(item < *curr->dataPtr){
        positionFinder(newPtr,curr->leftPtr,item);
    }
    else if(item > *curr->dataPtr) {
        positionFinder(newPtr,curr->rightPtr, item);
    }
    else{
        newPtr = nullptr;
    }

}

int SearchTree::heightAddition(Node* curr) const{
    //if it's a leaf
    if(curr != nullptr){
        int l = heightAddition(curr->leftPtr);
        int r = heightAddition(curr->rightPtr);
        return 1 + max(l,r);
    }
    return 0;
}

//******************************************************************************

//***************** Private Helper methods*************************************


//copies other tree from root to leaf Preorder traversal
void SearchTree::copyHelper(Node* otherRoot, Node* &thisRoot){
    //check if other tree's root is  null
    if(otherRoot != nullptr){
        //Preorder copying
        thisRoot = new Node(); //initialize root
        thisRoot->dataPtr = new Comparable;
        *thisRoot->dataPtr = *otherRoot->dataPtr; //copies values of data
        thisRoot->frequency = otherRoot->frequency;
        copyHelper(otherRoot->leftPtr, thisRoot->leftPtr);
        copyHelper(otherRoot->rightPtr, thisRoot->rightPtr);
    }
    else {
        thisRoot = nullptr;
    }
}

//comparing method helper
bool SearchTree::comparingHelper(Node* otherRoot,Node* thisRoot) const {

    //check if they are empty
    if(otherRoot == nullptr && thisRoot == nullptr){
        return true;
    }
    if (otherRoot == nullptr || thisRoot == nullptr){
        return false;
    }

    //check if data in comparable is the same
    if(*otherRoot->dataPtr != *thisRoot->dataPtr){
        return false;
    }

    if( otherRoot->frequency != thisRoot->frequency){
        return false;
    }

    return comparingHelper(otherRoot->leftPtr, thisRoot->leftPtr) &&
           comparingHelper(otherRoot->rightPtr, thisRoot->rightPtr);

}


//displaying trial
ostream& SearchTree::displaying(ostream &output, Node* curr) {
    if(curr != nullptr){
        displaying(output,curr->leftPtr);
        output << *curr->dataPtr << " "  << curr->frequency << endl;
        displaying(output,curr->rightPtr);
    }
    return output;
}

//display helper
void SearchTree::displayHelper(ostream &output,Node *curr) {
    if(curr != nullptr){
        displayHelper(output,curr->leftPtr);
        output << *curr->dataPtr << " "  << curr->frequency << endl;
        displayHelper(output,curr->rightPtr);
    }
}
//*********************************************************************


ostream& operator<<(ostream& output, const SearchTree& st){
    output << "Number of Nodes: " << st.Nodenums << endl;
    //  st.displayHelper(output,st.root);
    //output << endl;
    //return output;
    return st.displaying(output,st.root);
    // output << *st.root->dataPtr << " " << st.root->frequency << endl;
    //return output;
}

void SearchTree::print2DUtil(Node *root, int space)
{
    // Base case
    if (root == nullptr)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->rightPtr, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<*root->dataPtr<<"\n";

    // Process left child
    print2DUtil(root->leftPtr, space);
}

// Wrapper over print2DUtil()
void SearchTree::print2D()
{
    // Pass initial space count as 0
    print2DUtil(this->root, 0);
}