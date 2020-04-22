//
// Created by Melanie Palomino on 4/14/20.
//

#include "SearchTree.h"

#include <string>
#include <iostream>

using namespace std;

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

//removes one occurrence of a Comparable from the tree. If it is the last occurrence,
// remove the node. Return false if the Comparable is not found.
bool SearchTree::remove(const Comparable& item){
    if(this->root == nullptr){
        return false;
    }
   return deleteNode(this->root, item);
}

bool SearchTree::deleteNode(Node*& curr, const Comparable &item) {
    //base case
    if(*curr->dataPtr == item){
        if(curr->frequency == 1){
            curr->dataPtr = nullptr;
            if(curr->leftPtr == nullptr || curr->rightPtr == nullptr){
                Node* temp = curr;
                curr = curr->leftPtr == nullptr? curr->rightPtr : curr->leftPtr;
                delete temp;
                Nodenums--;
                return true;
            }
            else{
                curr->dataPtr = deleteLeft(curr);
                return true;
            }
        } else if(curr->frequency > 1){
            curr->frequency--;
            return true;
        }
    }
    if(*this->root->dataPtr < item){
        return deleteNode(curr->rightPtr,item);
    }
    if(*this->root->dataPtr < item){
        return deleteNode(curr->rightPtr,item);
    }
    return false;
}

Comparable* SearchTree::deleteLeft(Node *&curr) {
    if(curr->leftPtr == nullptr){
        Comparable* item = curr->dataPtr;
        Node* temp = curr;
        curr = curr->rightPtr;
        delete temp;
        temp = nullptr;
        Nodenums--;
        return item;
    }
    else{
        return deleteLeft(curr->leftPtr);
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
            curr->dataPtr = nullptr;
            //delete curr->dataPtr; //is this necessary since it is not in the heap
            delete curr;
        }
}
//*****************************************************************************

//******************* Mutator Functions ****************************************

//inds a Comparable in the tree using a key stored in the parameter.
// This is useful for cases where the Comparable stores more than the sorting key.
// Return nullptr if not found.
const Comparable* SearchTree::retrieve(const Comparable& item) const{
    if(isEmpty()){
        return nullptr;
    }
    return retrieveHelper(this->root, item);
}

// returns the height of the node storing the Comparable in the tree.
// A leaf has height 0. Return -1 if the Comparable is not found.
int SearchTree::height(const Comparable& item) const{
    //check if empty
    if(this->root == nullptr){
        return -1;
    }
    if(*this->root->dataPtr == item){
       return heightRecursiveHelper(this->root);
    }
    else {
        Node* curr = positionFinder(this->root,item);
        cout << "Here after positionFinder" << endl;
        if(curr == nullptr){
            cout << "Here in nullptr" << endl;
            return -1;
        }
        cout << "Here after checking nullptr" << endl;
        return heightRecursiveHelper(curr);
    }
}

SearchTree::Node* SearchTree::positionFinder(Node* curr, const Comparable &item) const {
    if(*curr->dataPtr == item){
        return curr;
    }
    if(*curr->dataPtr > item){
        return positionFinder(curr->leftPtr,item);
    }
    if(*curr->dataPtr < item) {
        return positionFinder(curr->rightPtr, item);
    }
    else{
        return nullptr;
    }

}

int SearchTree::heightRecursiveHelper(Node* curr) const{
    //if it's a leaf
    if(curr == nullptr){
        return 0;
    }
    int l = heightRecursiveHelper(curr->leftPtr);
    int r = heightRecursiveHelper(curr->rightPtr);
    return 1 + max(l,r);
}

//******************************************************************************

//***************** Private Helper methods*************************************

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
         //   cout << "Here in insert leftnullptr" << endl;
            return true;
        }
      //  cout << "Here in insert less than" << endl;
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

//check if tree is empty
bool SearchTree::isEmpty() const {
    return this->root == nullptr;
}

//copies other tree from root to leaf Preorder traversal
void SearchTree::copyHelper(Node* otherRoot, Node* &thisRoot){
    //check if other tree's root is  null
    if(otherRoot == nullptr){
        thisRoot = nullptr;
    }
    else{
        //Preorder copying
        thisRoot = new Node(); //initialize root
        thisRoot->dataPtr = new Comparable;
        *thisRoot->dataPtr = *otherRoot->dataPtr; //copies values of data
        thisRoot->frequency = otherRoot->frequency;
        copyHelper(otherRoot->leftPtr, thisRoot->leftPtr);
        copyHelper(otherRoot->rightPtr, thisRoot->rightPtr);
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

//helper retrieve Comprable pointer
const Comparable* SearchTree::retrieveHelper(Node *curr, const Comparable &item) const{
    if(curr != nullptr){
        //base case
        if(*curr->dataPtr == item){
            return curr->dataPtr;
        }
        if(*curr->dataPtr > item){
            curr = curr->rightPtr;
            return retrieveHelper(curr, item);
        }
        if(*curr->dataPtr < item){
            curr = curr->leftPtr;
            return retrieveHelper(curr, item);
        }
    }
    return nullptr;
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

    return output;
}