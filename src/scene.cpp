#include "../inc/scene.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

Scene::Scene(const std::string global, const std::string local){

  FileNameGlobalCoords = global;
  FileNameLocalCoords = local;
  Translation = Vector3D();
  Angles = Vector3D();
}

bool Scene::CalcGlobalCoords(){

  std::ifstream in(FileNameLocalCoords);
  std::ofstream out(FileNameGlobalCoords);
  Vector3D Point;
  Matrix3x3 RotMat;

  if(!in.is_open() || !out.is_open()) return false;

  RotMat.RotationMatrix(Angles);
  for(int i = 0; i < 8; ++i){
    in >> Point;
    out << (RotMat * Point + Translation) << std::endl;
  }
  return !in.fail() && !out.fail();
}

void Scene::ChangeAngles(const Vector3D angle_diff){

  Angles = Angles + angle_diff;
}

