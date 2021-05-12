#pragma once

#include "size.hh"
#include <iostream>

template <typename Type, int Size>
class Vector {

private:

    Type size[Size];     //Tablica wektora

public:

    Vector();

    Vector(Type [Size]);

    Vector operator + (const Vector<Type, Size> &v);

    Vector operator - (const Vector<Type, Size> &v);

    Vector operator * (const Type &tmp);

    Vector operator / (const Type &tmp);

    const Type &operator [] (int index) const;

    Type &operator [] (int index);

};

std::ostream &operator << (std::ostream &out, Vector<double, SIZE> const &tmp);

std::istream &operator >> (std::istream &in, Vector<double, SIZE> &tmp);


