//
// Created by Melanie Palomino on 4/14/20.
//operator==, operator!=, operator<, operator>:
// these are straightforward and just reuse the same char operators.
// This will result in the characters being sorted into ASCII order.
//operator<<: this should use char::operator<<
// - make sure to use syntax that allows chaining such as: cout << c1 << " " << c2 << endl;
//operator>>: this should read in a char from an istream.
// It can use char::operator<< or the istream::get() method.
//

#include "comparable.h"

#include <iostream>
#include <string>

using namespace std;

//************* FRIEND OPERATORS ****************************

ostream& operator<<(ostream& output, const Comparable& comp){
    output << comp.data;
    return output;
}

istream& operator>>(istream& input, Comparable& comp){
    input >> comp.data;
    return input;
}

//************************************************************

//**********************  EQUALS *****************************
bool Comparable::operator==(const Comparable &right) const {
    return this->data == right.data;
}
bool Comparable::operator!=(const Comparable &right) const {
    return this->data != right.data;
}
//************************************************************

//***************  GREATER THAN OR LESS **********************
bool Comparable::operator<(const Comparable &right) const {
    return this->data < right.data;
}
bool Comparable::operator>(const Comparable &right) const {
    return this->data > right.data;
}
//************************************************************