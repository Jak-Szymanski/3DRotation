#include "../inc/scene.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

/*!
* \file
* \brief Definicje metod klasy Scene
*/

/*!
* Inicjalizuje zmienną typu Scene, w której lokalne współrzędne wierzchołków prostopadłościanu są pobrane z argumentów,
* a wszystkie wartości zapisane w macierzy obrotu i wektorze translacji wynoszą 0
*/
Scene::Scene(const Cuboid local){

  LocalCoords = local;
  Translation = Vector3D();
  MatRot.IdentityMatrix();
}

/*!
* Oblicza globalne współrzędne danego prostopadłościanu na podstawie jego współrzędnych lokalnych, macierzy obrotu i wektora translacji
* oraz zapisuje do pliku podanego w argumencie
* \param[in] this - scena danego prostopadłościanu
* \param[in] global - plik do którego współrzędne globalne powinny być zapisane
*
* \return 1 jeżeli zapis pójdzie bez problemu, 0 jeżeli nie
*/ 
bool Scene::CalcGlobalCoords(std::string global){

  std::ofstream out(global);
  Cuboid GlobalCoords(LocalCoords);

  if(!out.is_open()) return false;

  GlobalCoords.Rotate(MatRot);
  GlobalCoords.Move(Translation);

  out << GlobalCoords;
  return !out.fail();
}

/*!
* Obracanie położenia lokalnych współrzędnych prostopadłościanu (obrót wokół środka)
* \param[in] this - scena danego prostopadłościanu
* \param[in] new_MatRot - macierz obrotu, który powinien zostać wykonany
* \param[in] iterations - ile razy obrót ten powinien zostać wykonany
*/
void Scene::ChangeAngles(Matrix3x3 new_MatRot, unsigned int iterations){

  for(; iterations > 0; --iterations){
    MatRot = new_MatRot * MatRot;
  }
  
}

/*! 
* Zmiana położenia lokalnych współrzędnych prostopadłościanu (przesuwanie go)
* \param[in] this - scena danego prostopadłościanu
* \param[in] new_transl - wektor o który prostopadłościan powinien zostać przesunięty
*/
void Scene::ChangeTranslation(const Vector3D new_transl){

  Translation = Translation + new_transl;
}