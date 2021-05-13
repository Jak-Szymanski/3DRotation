
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
      if(abs(Points[i][j] - cub(i, j) >= MIN_DIFF)){
        return 0;
      }
    }
  }
  return 1; 
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