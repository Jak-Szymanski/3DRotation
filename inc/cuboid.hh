#pragma once

#include "matrix3x3.hh"
#include <iostream>

#define MIN_DIFF  0.01

class Cuboid{

  private:
    Vector3D Points[8];

  public:

    Cuboid();

    Cuboid(const Cuboid &cub);

    Cuboid(double tmp[8][SIZE]);

    double &operator () (unsigned int row, unsigned int column);

    const double &operator () (unsigned int row, unsigned int column) const;

    bool operator == (const Cuboid &cub) const;

    Cuboid Rotate(Matrix3x3 rotation, int iterations);

    void CompareSides();
    
    Cuboid Move(const Vector3D v);
};

std::ostream &operator<<(std::ostream &out, Cuboid const &cub);

bool SaveCubToFile(const char *FileName, Cuboid &cub);

void PrintComparison(double Largest[4], double Middle[4], double Smallest[4]);

bool CompareArray(double Array[4]);

