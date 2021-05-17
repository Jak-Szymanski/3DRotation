#pragma once

#include "matrix4x4.hh"
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

    void Rotate(Matrix3x3 rotation, int iterations);

    void CompareSides();
    
    void Move(const Vector3D v);
};

std::ostream &operator<<(std::ostream &out, Cuboid const &cub);

bool SaveCubToFile(const char *FileName, Cuboid &cub);

void PrintComparison(double Largest[4], double Medium[4], double Smallest[4]);

bool CompareArray(double Array[4]);

void PrintLengths(double Array[4]);