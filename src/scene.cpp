#include "../inc/scene.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 

Scene::Scene(double coords[8][SIZE], const std::string global){

  LocalCoords = Cuboid(coords);
  FileNameGlobalCoords = global;
/*   FileNameLocalCoords = local; */
  Translation = Vector3D();
  Angles = Vector3D();
}

bool Scene::CalcGlobalCoords(){

  std::ofstream out(FileNameGlobalCoords);
  Matrix3x3 RotMat;
  Cuboid GlobalCoords(LocalCoords);

  if(!out.is_open()) return false;

  RotMat.RotationMatrix(Angles);
  GlobalCoords.Rotate(RotMat);
  GlobalCoords.Move(Translation);

  out << GlobalCoords;
  return !out.fail();
}

void Scene::ChangeAngles(const Vector3D angle_diff){

  Angles = Angles + angle_diff;
}

void Scene::ChangeTranslation(const Vector3D new_transl){

  Translation = Translation + new_transl;
}

void Scene::PrintGlobalCoords(){

  Matrix3x3 RotMat;
  Cuboid GlobalCoords(LocalCoords);  

  RotMat.RotationMatrix(Angles);
  GlobalCoords.Rotate(RotMat);
  GlobalCoords.Move(Translation);
  std::cout << GlobalCoords << std::endl;
}