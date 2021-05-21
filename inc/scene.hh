#pragma once

/*!
* \file Deklaracja klasy Scene
*
* Plik zawiera deklarację klasy prostopadłościanu oraz jej metod
*/ 
#include "cuboid.hh"
#include <iostream>
#include <vector>

/*!
* \brief Modeluje pojęcie sceny (danych potrzebnych do opisu globalnych współrzędnych prostopadłościanu na podstawie lokalnych współrzędnych)
*/
class Scene{

  private:

    /*!
    * \brief Lokalne współrzędne prostopadłościanu
    */
    Cuboid LocalCoords;
    
    /*!
    * \brief Wektor przesunięcia środka prostopadłościanu względem środka globalnych osi współrzędnych
    */
    Vector3D Translation;

    /*!
    * \brief Macierz obrotu osi lokalnych współrzędnych prostopadłościanu względem osi globalnych współrzędnych
    */
    Matrix3x3 MatRot;

  public:

    /*!
    * \brief Konstruktor parametryczny sceny
    */
    Scene(const Cuboid local);

    /*!
    * \brief Obliczanie globalnych współrzędnych
    */
    bool CalcGlobalCoords(std::string global);

    /*!
    * \brief Obracanie położenia lokalnych wspólrzędnych
    */
    void ChangeAngles(Matrix3x3 new_MatRot, unsigned int iterations);

    /*!
    * \brief Zmienianie położenia lokalnych współrzędnych
    */
    void ChangeTranslation(const Vector3D new_transl);

    /*!
    * \brief Wyświetlanie porównania długości boków prostopadłościanu
    */
    void CompareSides() {LocalCoords.CompareSides(); };

};