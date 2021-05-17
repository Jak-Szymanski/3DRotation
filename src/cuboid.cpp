
#include "../inc/cuboid.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

#define MIN_DIFF  0.01

Cuboid::Cuboid(){
  Points.reserve(8);
  for(int i = 0; i < 8; ++i){
    Points.push_back(Vector3D());
  }
}


Cuboid::Cuboid(const Cuboid &cub){
  Points.reserve(8);
  for(int i=0; i<8; i++){
      Points.push_back(cub.Points[i]);
  }
}


Cuboid::Cuboid(double tmp[8][SIZE]){

  Points.reserve(8);
  for (int i = 0; i < 8; ++i) {
    Vector3D v(tmp[i]);
    Points.push_back(v);
  }
}


double &Cuboid::operator () (unsigned int row, unsigned int column){

    if (row >= 8) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}


const double &Cuboid::operator () (unsigned int row, unsigned int column) const {

    if (row >= 8) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}


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

void Cuboid::Rotate(Matrix3x3 rotation, int iterations){

  for(; iterations > 0; iterations--){
    for(int i=0; i<8; i++){
      Points[i] = rotation * Points[i];
    }
  }
}

void Cuboid::Move(const Vector3D v){
  
  for(int i=0; i<8; i++){
    Points[i] = Points[i] + v;
  } 
}


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

bool SaveCubToFile(const char *FileName, Cuboid &cub){
       std::ofstream file;

       file.open(FileName);
       if (!file.is_open())  {
              std::cerr << ":(  Operacja otwarcia do zapisu \"" << FileName << "\"" << std::endl
	        << ":(  nie powiodla sie." << std::endl;
       return false;
  }

  file << cub;
  file.close();
  return !file.fail();
}

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

void PrintLengths(double Array[4]){

  std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << Array[0] << std::endl;
  std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << Array[1] << std::endl;
  std::cout << "Dlugosc trzecieego boku: " << std::fixed << std::setprecision(10) << Array[2] << std::endl;
  std::cout << "Dlugosc czwartego boku: " << std::fixed << std::setprecision(10) << Array[3] << std::endl << std::endl;
}