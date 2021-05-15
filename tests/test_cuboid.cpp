#include "../tests/doctest/doctest.h"
#include "../inc/cuboid.hh"
#include <iostream>
#include <sstream>
#include <string>


TEST_CASE("Konstruktor bezparametryczny i parametryczny - tablica"){

  Cuboid x;
  double Ty[8][SIZE] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},};
  Cuboid y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor parametryczny - cuboid"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);
  Cuboid y(x);

  CHECK(x == y);
}

TEST_CASE("Operator ()"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);

  CHECK(x(2,0) == 1);
}

TEST_CASE("Operator () - wiersz poza zasięgiem na plus"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);

  WARN_THROWS(x(8,0));
}

TEST_CASE("Operator () - wiersz poza zasięgiem na minus"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);

  WARN_THROWS(x(-1,0));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na plus"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);

  WARN_THROWS(x(2,3));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na minus"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  Cuboid x(Tx);

  WARN_THROWS(x(2,-1));
}

TEST_CASE("Porownanie - minimalnie nierowne"){

  double Tx[8][SIZE] = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}};
  double Ty[8][SIZE] = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1.01}};

  Cuboid x(Tx), y(Ty);

  CHECK(!(x == y));                                                 
}

TEST_CASE("Porownanie - minimalnie rowne"){

  double Tx[8][SIZE] = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}};
  double Ty[8][SIZE] = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1.009}};

  Cuboid x(Tx), y(Ty);

  CHECK(x == y);
}

TEST_CASE("Przesunięcie"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  double Ty[8][SIZE] = {{2,1,2}, {3,4,3}, {2,1,3}, {3,4,2}, {3,4,3}, {2,1,2}, {3,4,3}, {3,4,2}};
  double Tv[SIZE] = {1,1,1};

  Cuboid x(Tx), y(Ty);
  Vector3D v(Tv);

  x.Move(v);

  CHECK(x == y);
}

TEST_CASE("Przesunięcie o zero"){

  double Tx[8][SIZE] = {{1,0,1}, {2,3,2}, {1,0,2}, {2,3,1}, {2,3,2}, {1,0,1}, {2,3,2}, {2,3,1}};
  
  Cuboid x(Tx), y(Tx);
  Vector3D v;

  x.Move(v);

  CHECK(x == y);
}
