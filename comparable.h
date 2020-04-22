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

#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <iostream>
#include <string>

using namespace std;

class Comparable{

    friend ostream& operator<<(ostream& output, const Comparable& a);

    friend istream& operator>>(istream& input, Comparable& a);

public:
    bool operator==(const Comparable& right) const;

    bool operator!=(const Comparable& right) const;

    bool operator<(const Comparable& right) const;

    bool operator>(const Comparable& right) const;

private:
    char data;
};

#endif //COMPARABLE_H
