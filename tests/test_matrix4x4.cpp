#include "../tests/doctest/doctest.h"
#include "../inc/matrix4x4.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Test macierzy obrotu"){
  
  double Ty[4][4] = {{0,-1,0,1}, {0,0,-1,2}, {1,0,0,3}, {0,0,0,1}};
  Matrix4x4 x, y(Ty);
  double Tv[SIZE] = {1,2,3};
  Vector3D v(Tv);
  x.RotationMatrix4x4(90, -90, 0, v);

  CHECK(x == y);
}