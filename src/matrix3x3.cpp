#include <cmath>

#include "../inc/matrix3x3.hh"

#define PI 3.14159265358979323846

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                         |
 */

std::istream &operator>>(std::istream &in, Matrix3x3 &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */

std::ostream &operator<<(std::ostream &out, const Matrix3x3 &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}


template<>
Matrix3x3 Matrix3x3::RotationMatrix(double degrees, char axis) {
    double radians = degrees * (PI/180);

    switch(axis){
        case 'x':{
            value[0][1]=value[0][2]=value[1][0]=value[2][0]=0;
            value[0][0]=1;
            value[1][1]=value[2][2]=cos(radians);
            value[1][2]=-sin(radians);
            value[2][1]=sin(radians);
        }
        break;

        case 'y':{
            value[0][1]=value[1][0]=value[1][2]=value[2][1]=0;
            value[1][1]=1;
            value[0][0]=value[2][2]=cos(radians); 
            value[0][2]=sin(radians);
            value[2][0]=-sin(radians);    
        }
        break;

        case 'z':{
            value[2][0]=value[2][1]=value[0][2]=value[1][2]=0;
            value[2][2]=1;
            value[0][0]=value[1][1]=cos(radians);
            value[1][0]=sin(radians);
            value[0][1]=-sin(radians);
        }
        break;

        default:
        throw std::runtime_error("Error: Niepoprawna oś obrotu \n");
        break;
    }
    return *this;
}