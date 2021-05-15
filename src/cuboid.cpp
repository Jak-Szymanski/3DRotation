
#include "../inc/cuboid.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

#define MIN_DIFF  0.01

Cuboid::Cuboid(){
  for(int i=0; i<8; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = 0;
    }
  }
}


Cuboid::Cuboid(const Cuboid &cub){
  for(int i=0; i<8; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = cub(i, j);
    }
  }
}


Cuboid::Cuboid(double tmp[8][SIZE]){
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      Points[i][j] = tmp[i][j];
    }
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

Cuboid Cuboid::Rotate(Matrix3x3 rotation, int iterations){

  for(; iterations > 0; iterations--){
    for(int i=0; i<8; i++){
      Points[i] = rotation * Points[i];
    }
  }

  return *this;
}

Cuboid Cuboid::Move(const Vector3D v){
  
  for(int i=0; i<8; i++){
    Points[i] = Points[i] + v;
  }
  return *this;  
}


std::ostream &operator<<(std::ostream &out, Cuboid const &cub){
  int i, j;
  for(i=0; i<8; i++){
    for(j=0; j<SIZE; j++){
      out << std::fixed << std::setprecision(10) << cub(i, j) << "\t";
    }
    out << std::endl;
    if(i%2 == 1){
      out << std::endl;
    }
  }
  
  for(i=0; i<2; i++){
    for(j=0; j<SIZE; j++){
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
  
  double a[4] = {Distance(Points[1],Points[3]), Distance(Points[2],Points[4]), Distance(Points[5],Points[7]),Distance(Points[6],Points[8])};
  double b[4] = {Distance(Points[1],Points[7]), Distance(Points[2],Points[8]), Distance(Points[5],Points[3]),Distance(Points[6],Points[4])};
  double c[4] = {Distance(Points[1],Points[2]), Distance(Points[3],Points[4]), Distance(Points[5],Points[6]),Distance(Points[7],Points[8])};
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