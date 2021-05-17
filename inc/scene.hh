#pragma once

#include "cuboid.hh"
#include <iostream>
#include <vector>

class Scene{

  private:

    std::string FileNameGlobalCoords;

    std::string FileNameLocalCoords;

    Vector3D Translation;

    Vector3D Angles;

  public:

    Scene(const std::string global, const std::string local);

    bool CalcGlobalCoords();

    void ChangeAngles(const Vector3D angle_diff);

    void ChangeTranslation(const Vector3D new_transl);
};