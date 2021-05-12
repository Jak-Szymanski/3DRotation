#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <cstdlib>

template <typename Type, int Size>
class Matrix {

private:
    Type value[Size][Size];               // Wartosci macierzy

public:
    Matrix(Type [Size][Size]);            // Konstruktor klasy

    Matrix();                               // Konstruktor klasy

    Vector<Type, Size> operator * (Vector<Type, Size> tmp);           // Operator mnożenia przez wektor

    Matrix operator + (Matrix tmp);

    Type  &operator () (unsigned int row, unsigned int column);
    
    const Type &operator () (unsigned int row, unsigned int column) const;
};

std::istream &operator>>(std::istream &in, Matrix<double, SIZE> &mat);

std::ostream &operator<<(std::ostream &out, Matrix<double, SIZE> const &mat);

