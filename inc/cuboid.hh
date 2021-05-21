#pragma once

/*! 
* \file
* \brief Deklaracja klasy Cuboid
*
* Plik zawiera deklarację klasy prostopadłościanu oraz jego metod 
*/

#include "matrix4x4.hh"
#include <iostream>
#include <vector>

#define MIN_DIFF  0.01

/*!
* \brief Modeluje pojęcie prostopadłościanu
*/
class Cuboid{

  private:
  
    /*!
    * \brief Kontener zawierający wierzchołki prostopadłościanu zapisane jako wektory3D
    */
    std::vector<Vector3D> Points;

  public:

    /*!
    * \brief Konstruktor bezparametryczny prostopadłościanu
    */
    Cuboid();

    /*!
    * \brief Konstruktor parametryczny prostopadłościanu z prostopadłościanem jako parametr
    */
    Cuboid(const Cuboid &cub);

    /*!
    * \brief Konstruktor parametryczny prostopadłościanu z tablicą jako parametr
    */
    Cuboid(double tmp[8][SIZE]);

    /*! 
    * \brief Przeciążenie operatora wywołania (zwraca zmienną modyfikowalną)
    */ 
    double &operator () (unsigned int row, unsigned int column);

    /*!
    * \brief Przeciążenie operatora wywołania (zwraca zmienną const)
    */
    const double &operator () (unsigned int row, unsigned int column) const;

    /*!
    * \brief Przeciążenie operatora porównania dwóch prostopadłościanów
    */
    bool operator == (const Cuboid &cub) const;

    /*!
    * \brief Przeciążenie operatora przypisania dwóch prostopadłościanów
    */
    Cuboid operator = (const Cuboid &cub);

    /*!
    * \brief Obrót prostopadłościanu o pewną macierz obrotu
    */
    void Rotate(Matrix3x3 rotation);

    /*!
    * \brief Porównanie długości boków prostopadłościanu
    */
    void CompareSides();
    
    /*!
    * \brief Przesunięcie prostopadłościanu o pewien wektor3D
    */ 
    void Move(const Vector3D v);
};

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w lewo dla prostopadłościanu
*/
std::ostream &operator<<(std::ostream &out, Cuboid const &cub);

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w prawo dla prostopadłościanu
*/
std::istream &operator >> (std::istream &in, Cuboid &cub);

/*!
* \brief Wyświetlenie porównania długości poszczególnych boków prostopadłościanu zawartych w trzech tablicach
*/
void PrintComparison(double Largest[4], double Medium[4], double Smallest[4]);

/*!
* \brief Sprawdzenie czy wartości w tablicy są wszystkie sobie równe
*/
bool CompareArray(double Array[4]);

/*!
* \brief Wyświetlenie długości boków prostopadłościanu zawartych w tablicy
*/
void PrintLengths(double Array[4]);