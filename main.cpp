#include "SearchTree.h"
#include "comparable.h"

#include <fstream>
#include <string>
//#include <sstream>
#include <iostream>

using namespace std;

int main() {
    cout << "Testing Comparable Class" << endl;
    Comparable a,b,c;
    cout << "Type in desired char for a & c: " << endl;
    cin >> a >> c;
    cout << " a = " << a << " c = " << c << endl;
    cout << "Type in desired char for b: " << endl;
    cin >> b;
    bool test = a > b;
    cout << "Result of a > b: " << test << endl;
    test = a == c;
    cout << "Result of a == c: " << test << endl;
    Comparable* ptrA = &a;
    Comparable* ptrB = &b; //copies the address of a
    Comparable* ptrC = &c;
    cout << "Ptr to Comparable A: " << *ptrA << endl;
    cout << "Ptr to Comparable B: " << *ptrB << endl;
    cout << "Ptr to Comparable C: " << *ptrC << endl;

    cout << "************************" << endl;
    cout << "Testing SearchTree Class" << endl;

    SearchTree tree;
    cout << "Tree 1 " << endl;
    tree.insert(ptrA);
    tree.insert(ptrA);
    tree.insert(ptrB);
    tree.insert(ptrC);
    cout << tree;

    SearchTree tree2;
    cout << "Tree 2 " << endl;
    tree2.insert(ptrA);
    tree2.insert(ptrA);
    tree2.insert(ptrB);
    tree2.insert(ptrC);
    tree2.insert(ptrC);
    cout << tree2;

    cout << "Tree 3 " << endl;
    SearchTree tree3 = tree;
    cout << tree3;

    bool equal = tree == tree2;
    cout << " Tree == tree2 (0): "<< equal << endl;
    equal = tree3 != tree;
    cout << " Tree3 != tree (0): "<< equal << endl;
    equal = tree3 == tree;
    cout << " Tree3 == tree (1): "<< equal << endl;
    equal = tree3 == tree2;
    cout << " Tree3 == tree2(0): "<< equal << endl;

    cout << "Tree 1 after removal of one A:" << endl;
    tree.remove(a);
    cout << tree;

    cout << "Tree 1 after removal of one c:" << endl;
    tree.remove(c);
    cout << tree;

    cout << "Height of a in tree: " << tree.height(a) << endl;
    cout << "Height of b in tree: " << tree.height(b) << endl;
    if(tree.height(c) == -1){
        cout << "Here" << endl;
        cout << "Height of C in tree: -1" << endl;
    }



    cout << "a in tree2: " << *tree2.retrieve(a) << endl;
    cout << "b in tree2: " << *tree2.retrieve(b) << endl;

    return 0;
}
