#pragma once

#include "cuboid.hh"
#include <iostream>
#include <vector>

class Scene{

  private:

    Cuboid LocalCoords;

    std::string FileNameGlobalCoords;
    
    Vector3D Translation;

    Vector3D Angles;

  public:

    Scene(double coords[8][SIZE], const std::string global);

    bool CalcGlobalCoords();

    void ChangeAngles(const Vector3D angle_diff);

    void ChangeTranslation(const Vector3D new_transl);

    void CompareSides() {LocalCoords.CompareSides(); };

    void PrintGlobalCoords();

};