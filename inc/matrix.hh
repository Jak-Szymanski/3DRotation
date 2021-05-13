#pragma once

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



/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
template <typename Type, int Size>
Matrix<Type, Size>::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
template <typename Type, int Size>
Matrix<Type, Size>::Matrix(Type tmp[Size][Size]) {
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}


/******************************************************************************
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */
template <typename Type, int Size>
Vector<Type, Size> Matrix<Type, Size>::operator * (Vector<Type, Size> tmp) {
    Vector<Type, Size> result;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
template <typename Type, int Size>
Type &Matrix<Type, Size>::operator()(unsigned int row, unsigned int column) {

    if (row >= Size) {
        std::cout << "Error: Macierz jest poza zasiegiem"; 
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= Size) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
template <typename Type, int Size>
const Type &Matrix<Type, Size>::operator () (unsigned int row, unsigned int column) const {

    if (row >= Size) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= Size) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/******************************************************************************
 |  Przeciążenie dodawania macierzy                                                          |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik dodawania,                     |
 |      v - wektor, czyli drugi skladnik dodawania.                                               |
 |  Zwraca:                                                                   |
 |      Macierz - iloczyn dwóch podanych macierzy.                  |
 */
template <typename Type, int Size>
Matrix<Type, Size> Matrix<Type, Size>::operator + (Matrix<Type, Size> tmp) {
    Matrix result;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}


