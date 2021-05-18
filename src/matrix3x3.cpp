#include <cmath>
#include <iomanip>

#include "../inc/matrix3x3.hh"

#define PI 3.14159265358979323846

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                        |
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
            out << std::fixed << std::setprecision(10) <<"| " << mat(i, j) << " | ";
        }
        out << std::endl;
    }
    return out;
}


template<>
void Matrix3x3::RotationMatrix(Vector3D degrees) {

    Vector3D radians;
    radians = degrees * (PI/180);
    Matrix3x3 tmp;
    tmp.IdentityMatrix();
    *this = tmp;

        if(radians[0] != 0){
            tmp.value[0][1]=tmp.value[0][2]=tmp.value[1][0]=tmp.value[2][0]=0;
            tmp.value[0][0]=1;
            tmp.value[1][1]=tmp.value[2][2]=cos(radians[0]);
            tmp.value[1][2]=-sin(radians[0]);
            tmp.value[2][1]=sin(radians[0]);
            *this = tmp * *this;
        }
        
        if(radians[1] != 0){
            tmp.value[0][1]=tmp.value[1][0]=tmp.value[1][2]=tmp.value[2][1]=0;
            tmp.value[1][1]=1;
            tmp.value[0][0]=tmp.value[2][2]=cos(radians[1]); 
            tmp.value[0][2]=sin(radians[1]);
            tmp.value[2][0]=-sin(radians[1]);    
            *this = tmp * *this;
            }

        if(radians[2] != 0){
            tmp.value[2][0]=tmp.value[2][1]=tmp.value[0][2]=tmp.value[1][2]=0;
            tmp.value[2][2]=1;
            tmp.value[0][0]=tmp.value[1][1]=cos(radians[2]);
            tmp.value[1][0]=sin(radians[2]);
            tmp.value[0][1]=-sin(radians[2]);
            *this = tmp * *this;
        }

}