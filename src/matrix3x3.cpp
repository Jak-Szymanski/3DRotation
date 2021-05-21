#include <cmath>
#include <iomanip>

/*!
* \file 
* \brief Metody zdefiniowane dla Macierzy3x3
*/

#include "../inc/matrix3x3.hh"

#define PI 3.14159265358979323846

/*!
* \brief Przeciążenie operatora >> dla Macierzy3x3
* 
* \param[in] in - adres strumienia wejściowego
* \param[in] mat - macierz
*/
std::istream &operator>>(std::istream &in, Matrix3x3 &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}


/*!
* \brief Przeciążenie operatora << dla Macierzy3x3
* 
* \param[in] out - adres strumienia wyjściowego
* \param[in] mat - macierz
*/
std::ostream &operator<<(std::ostream &out, const Matrix3x3 &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << std::fixed << std::setprecision(10) <<"| " << mat(i, j) << " | ";
        }
        out << std::endl;
    }
    return out;
}

/*!
* Uzyskanie trójwymiarowej macierzy rotacji dla danego kąta w danej osi. 
* Funkcja przemnoży obliczoną macierz obrotu przez macierz podaną jako argument. 
* \param[in] this - macierz
* \param[in] degrees - kąt w stopniach
* \param[in] axis - oś obrotu (zapisana jako 'x' / 'y' / 'z')
*/
template<>
void Matrix3x3::RotationMatrix(double degrees, char axis) {

    double radians = degrees * (PI/180);
    Matrix3x3 tmp;
    switch(axis){
        case 'x':
            tmp.value[0][1]=tmp.value[0][2]=tmp.value[1][0]=tmp.value[2][0]=0;
            tmp.value[0][0]=1;
            tmp.value[1][1]=tmp.value[2][2]=cos(radians);
            tmp.value[1][2]=-sin(radians);
            tmp.value[2][1]=sin(radians);
            *this = tmp * *this;
        break;
        
        case 'y':
            tmp.value[0][1]=tmp.value[1][0]=tmp.value[1][2]=tmp.value[2][1]=0;
            tmp.value[1][1]=1;
            tmp.value[0][0]=tmp.value[2][2]=cos(radians); 
            tmp.value[0][2]=sin(radians);
            tmp.value[2][0]=-sin(radians);    
            *this = tmp * *this;
        break;

        case 'z':
            tmp.value[2][0]=tmp.value[2][1]=tmp.value[0][2]=tmp.value[1][2]=0;
            tmp.value[2][2]=1;
            tmp.value[0][0]=tmp.value[1][1]=cos(radians);
            tmp.value[1][0]=sin(radians);
            tmp.value[0][1]=-sin(radians);
            *this = tmp * *this;
        break;
    }
}