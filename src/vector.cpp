
#include "../inc/vector.hh"

/******************************************************************************
 |  Konstruktor klasy Vector.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartoscia 0.                                       |
 */
template <typename Type, int Size>
Vector<Type, Size>::Vector() {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
    }
}


/******************************************************************************
 |  Konstruktor klasy Vector.                                                 |
 |  Argumenty:                                                                |
 |      tmp - Jednowymiarowa tablica typu double.                             |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartosciami podanymi w argumencie.                 |
 */
template <typename Type, int Size>
Vector<Type, Size>::Vector(Type tmp[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
}


/******************************************************************************
 |  Realizuje dodawanie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik dodawania,                                   |
 |      v - drugi skladnik dodawania.                                         |
 |  Zwraca:                                                                   |
 |      Sume dwoch skladnikow przekazanych jako wskaznik                      |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator + (const Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
}


/******************************************************************************
 |  Realizuje odejmowanie dwoch wektorow.                                     |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik odejmowania,                                 |
 |      v - drugi skladnik odejmowania.                                       |
 |  Zwraca:                                                                   |
 |      Roznice dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator - (const Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
}


/******************************************************************************
 |  Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.               |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik mnozenia (wektor),                           |
 |      v - drugi skladnik mnozenia (liczba typu double).                     |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator * (const Type &tmp) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
}


/******************************************************************************
 |  Realizuje dzielenie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - licznik dzielenia,                                             |
 |      v - mianownik dzielenia.                                              |
 |  Zwraca:                                                                   |
 |      Iloraz dwoch skladnikow przekazanych jako wskaznik                    |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator / (const Type &tmp) {
    Vector result;

    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] / tmp;
    }

    return result;
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy jako stala.                   |
 */
template <typename Type, int Size>
const Type &Vector<Type, Size>::operator [] (int index) const {
    if (index < 0 || index >= SIZE) {
        std::cerr << "Error: Wektor jest poza zasiegiem!" << std::endl;
    } // lepiej byłoby rzucić wyjątkiem stdexcept
    return size[index];
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy.                              |
 */
template <typename Type, int Size>
Type &Vector<Type, Size>::operator[](int index) {
    return const_cast<Type &>(const_cast<const Vector *>(this)->operator[](index));
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      tmp - wektor.                                                         |
 */
template <typename Type, int Size>
std::ostream &operator << (std::ostream &out, Vector<Type, Size> const &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        out << "[ " << tmp[i] << " ]\n";
    }
    return out;
}


/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      tmp - wektor.                                                         |
 */
template <typename Type, int Size>
std::istream &operator >> (std::istream &in, Vector<Type, Size> &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}