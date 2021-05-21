
#include "../inc/cuboid.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

/*!
* \file
* \brief Definicje metod klasy Cuboid
*/

#define MIN_DIFF  0.01
/*!
* Inicjalizuje zmienną typu Cuboid, wypełnia wszystkie współrzędne wierzchołków zerami
*/
Cuboid::Cuboid(){
  Points.reserve(8);
  for(int i = 0; i < 8; ++i){
    Points.push_back(Vector3D());
  }
}

/*! 
* Inicjalizuje zmienną typu Cuboid, w której współrzędne wierzchołków są takie same jak w prostopadłościanie podanym w argumencie
*/
Cuboid::Cuboid(const Cuboid &cub){
  Points.reserve(8);
  for(int i=0; i<8; i++){
      Points.push_back(cub.Points[i]);
  }
}

/*!
* Inicjalizuje zmienną typu Cuboid, wypełnia wszystkie współrzędne wierzchołków wartościami podanymi w argumencie
*/
Cuboid::Cuboid(double tmp[8][SIZE]){

  Points.reserve(8);
  for (int i = 0; i < 8; ++i) {
    Vector3D v(tmp[i]);
    Points.push_back(v);
  }
}

/*!
* Uzyskiwanie danej współrzędnej prostopadłościanu jako zmienna const
* \param[in] this - prostopadłościan
* \param[in] row - nr szukanego wierzchołka (0-8)
* \param[in] column - nr współrzędnej w danym wierzchołku (0 = x, 1 = y, 2 = z)
*
* \return Wartość współrzędnej w danym wierzchołku w danej osi jako wartość double const
*/ 
double &Cuboid::operator () (unsigned int row, unsigned int column){

    if (row >= 8) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}

/*!
* Uzyskiwanie danej współrzędnej prostopadłościanu jako zmienna modyfikowalna
* \param[in] this - prostopadłościan
* \param[in] row - nr szukanego wierzchołka (0-8)
* \param[in] column - nr współrzędnej w danym wierzchołku (0 = x, 1 = y, 2 = z)
*
* \return Wartość współrzędnej w danym wierzchołku w danej osi jako wartość double modyfikowalna
*/ 
const double &Cuboid::operator () (unsigned int row, unsigned int column) const {

    if (row >= 8) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}

/*!
* Porównanie dwóch prostopadłościanów
* \param[in] this - Pierwszy prostopadłościan
* \param[in] cub - Drugi prostopadłościan
*
* \return 1 jeżeli wszystkie wierzchołki obu prostopadłościanów mają takie same współrzędne, 0 jeżeli nie (przy pewnej tolerancji)
*/
bool Cuboid::operator == (const Cuboid &cub) const{
  for(int i=0; i<8; i++){
    for(int j=0; j<SIZE; j++){
      if(abs(Points[i][j] - cub(i, j)) >= MIN_DIFF){
        return 0;
      }
    }
  }
  return 1; 
}

/*!
* Przypisanie współrzędnych prostopadłościanów
* \param[in] this - Pierwszy prostopadłościan (do którego wartości będą wpisywane)
* \param[in] cub - Drugi prostopadłościan (z którego wartości będą przepisywane)
*
* \return Prostopadłościan po przypisaniu
*/
Cuboid Cuboid::operator = (const Cuboid &cub){
  for(int i=0; i<8; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = cub(i, j);
    }
  }  
  return *this;
}

/*!
* Obrót prostopadłościanu o pewną macierz obrotu
* \param[in] this - Prostopadłościan
* \param[in] rotation - Macierz obrotu 3x3
*
* \return Prostopadłościan po przemnożeniu każdego wierzchołka przez macierz obrotu
*/
void Cuboid::Rotate(Matrix3x3 rotation){

  for(int i=0; i<8; i++){
    Points[i] = rotation * Points[i];
  }
}

/*!
* Przesunięcie prostopadłościanu o pewien wektor
* \param[in] this - Prostopadłościan
* \param[in] v - Wektor przesunięcia 3D
*
*\return Prostopadłościan po przesunięciu każdego wierzchołka przez wektor przesunięcia
*/
void Cuboid::Move(const Vector3D v){
  
  for(int i=0; i<8; i++){
    Points[i] = Points[i] + v;
  } 
}

/*!
* Wpisywanie współrzędnych wierzchołków prostopadłościanu do strumienia wyjściowego w sposób odpowiedni dla GNUplota 
* do wyświetlenia go.
* 
* \param[in] out - adres strumienia wyjściowego
* \param[in] cub - prostopadłościan
*/
std::ostream &operator<<(std::ostream &out, Cuboid const &cub){

  for(int i=0; i<8; i++){
    for(int j=0; j<SIZE; j++){
      out << std::fixed << std::setprecision(10) << cub(i, j) << "\t";
    }
    out << std::endl;
    if(i%2 == 1){
      out << std::endl;
    }
  }
  
  for(int i=0; i<2; i++){
    for(int j=0; j<SIZE; j++){
        out << std::fixed << std::setprecision(10) << cub(i, j) << "\t";
      }
      out << std::endl;
    }
  return out;
}

/*!
* Wczytywanie współrzędnych wierzchołków prostopadłościanu do zmiennej typu Cuboid
* \param[in] in - adres strumienia wejściowego
* \param[in] cub - prostopadłościan
*/
std::istream &operator >> (std::istream &in, Cuboid &cub){

  for(int i = 0; i<8; ++i){
    for(int j = 0; j<SIZE; ++j){
      in >> cub(i,j);
    }
  }
  return in;
}

/*!
* Porównanie długości boków prostopadłościanu
* Funckja wyświetli porównanie wszystkich przeciwległych boków prostopadłościanu (czy są równe z pewną tolerancją i jakie mają długości)
* \param[in] this - prostopadłościan
*/
void Cuboid::CompareSides(){

  double a[4] = {Distance(Points[0],Points[2]), Distance(Points[1],Points[3]), Distance(Points[4],Points[6]),Distance(Points[5],Points[7])};
  double b[4] = {Distance(Points[0],Points[6]), Distance(Points[1],Points[7]), Distance(Points[4],Points[2]),Distance(Points[5],Points[3])};
  double c[4] = {Distance(Points[0],Points[1]), Distance(Points[2],Points[3]), Distance(Points[4],Points[5]),Distance(Points[6],Points[7])};

  if(a[0] > b[0]){
    if(a[0]>c[0]){
      if(b[0]>c[0]){
        PrintComparison(a,b,c);
      } else {
        PrintComparison(a,c,b);
      }
    } else {
      PrintComparison(c,a,b);
    }
  } else {
    if(b[0] > c[0]){
      if(a[0] > c[0]){
        PrintComparison(b,a,c);
      } else {
        PrintComparison(b,c,a);
      }
    } else {
      PrintComparison(c,b,a);
    }
  }
}

/*!
* Wyświetlenie porównania trzech tablic zawierających długości boków prostopadłościanu
* Funckja przyjmuje trzy tablice 4 elementowe w odpowiedniej kolejności zależnej od długości boków zapisanych w nich i wyświetla komunikat
* o tym czy długości zapisane w niej są wszystkie sobie równe z pewną tolerancją
* \param[in] Largest - tablica zawierająca najdłuższe boki prostopadłościanu
* \param[in] Medium - tablica zawierająca średniej długości boki prostopadłościanu
* \param[in] Smallest - tablica zawierająca najkrótsze boki prostopadłościanu
*/
void PrintComparison(double Largest[4], double Medium[4], double Smallest[4]){

  if(CompareArray(Largest)){
    std::cout  << ":)  Dluzsze przeciwlegle boki sa sobie rowne." << std::endl << std::endl;
  } else {
    std::cout << ":O  Dluzsze przeciwlegle boki nie sa sobie rowne!!!" << std::endl << std::endl;
  }
  PrintLengths(Largest);

  if(CompareArray(Smallest)){
    std::cout  << ":)  Krotsze przeciwlegle boki sa sobie rowne." << std::endl << std::endl;
  } else {
    std::cout << ":O  Krotsze przeciwlegle boki nie sa sobie rowne!!!" << std::endl << std::endl;
  }
  PrintLengths(Smallest);

  if(CompareArray(Medium)){
    std::cout  << ":)  Poprzeczne przeciwlegle boki sa sobie rowne." << std::endl << std::endl;
  } else {
    std::cout << ":O  Poprzeczne przeciwlegle boki nie sa sobie rowne!!!" << std::endl << std::endl;
  } 
  PrintLengths(Medium);
}

/*!
* Porównanie wszystkich długości boków prostopadłościanu zapisanych w danej 4 - elementowej tablicy
* \param[in] Array - tablica z długościami przeciwległych boków
*
* \return 1 jeżeli wszystkie boki są sobie równe, 0 jeżeli nie (przy pewnej tolerancji)
*/
bool CompareArray(double Array[4]){
  
  for(int i = 0; i < 3; i++){
    for(int j = i+1; j < 4; j++){
      if(abs(Array[i] - Array[j]) >= MIN_DIFF){
        return 0;
      }
    }
  }
  return 1;
}

/*!
* Wyświetlenie długości każdego boku zapisanego w danej 4 - elementowej tablicy
* \param[in] Array - tablica z długościami przeciwległych boków
*/
void PrintLengths(double Array[4]){

  std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << Array[0] << std::endl;
  std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << Array[1] << std::endl;
  std::cout << "Dlugosc trzecieego boku: " << std::fixed << std::setprecision(10) << Array[2] << std::endl;
  std::cout << "Dlugosc czwartego boku: " << std::fixed << std::setprecision(10) << Array[3] << std::endl << std::endl;
}