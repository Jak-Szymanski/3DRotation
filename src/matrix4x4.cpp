#include <cmath>
#include <iomanip>

/*!
* \file 
* \brief Metody zdefiniowane dla Macierzy4x4
*/

#include "../inc/matrix4x4.hh"

#define PI 3.14159265358979323846

/*! 
* Uzyskanie czterowymiarowej macierzy obrotu i translacji. 
* \param[in] this - macierz
* \param[in] alpha - kąt w osi x w stopniach
* \param[in] beta - kąt w osi y w stopniach
* \param[in] gamma - kąt w osi z w stopniach
* \param[in] transl - wektor translacji
*/
template<>
void Matrix4x4::RotationMatrix4x4(double alpha, double beta, double gamma, Vector3D transl){

  double sin_a = sin(alpha * PI/180);
  double cos_a = cos(alpha * PI/180);
  double sin_b = sin(beta * PI/180);
  double cos_b = cos(beta * PI/180);
  double sin_y = sin(gamma * PI/180);
  double cos_y = cos(gamma * PI/180) ;

  value[0][0] = cos_a * cos_b;
  value[0][1] = cos_a * sin_b * sin_y - sin_a * cos_y;
  value[0][2] = cos_a * sin_b * cos_y + sin_a * sin_y;
  value[0][3] = transl[0];

  value[1][0] = sin_a * cos_b;
  value[1][1] = sin_a * sin_b * sin_y + cos_a * cos_y;
  value[1][2] = sin_a * sin_b * cos_y - cos_a * sin_y;
  value[1][3] = transl[1];

  value[2][0] = -sin_b;
  value[2][1] = cos_b * sin_y;
  value[2][2] = cos_b * cos_y;
  value[2][3] = transl[2];

  value[3][0] = value[3][1] = value[3][2] = 0;
  value[3][3] = 1;
}

/*!
* \brief Przeciążenie operatora << dla Macierzy4x4
* 
* \param[in] out - adres strumienia wyjściowego
* \param[in] mat - macierz
*/
std::ostream &operator<<(std::ostream &out, const Matrix4x4 &mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << std::fixed << std::setprecision(10) <<"| " << mat(i, j) << " | ";
        }
        out << std::endl;
    }
    return out;
}


/*!
* \brief Przeciążenie operatora >> dla Macierzy4x4
* 
* \param[in] in - adres strumienia wejściowego
* \param[in] mat - macierz
*/
std::istream &operator>>(std::istream &in, Matrix4x4 &mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}