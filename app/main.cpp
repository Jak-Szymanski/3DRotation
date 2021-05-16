// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>


#include<unistd.h>                       /*  usun to  */

#include "cuboid.hh"
#include "exampleConfig.h"
#include "example.h"


#include "../inc/lacze_do_gnuplota.hh"

void PrintMenu(){

  std::cout << std::endl << "o - obrot bryly o zadana sekwencje katow" << std::endl;
  std::cout << "t - powtorzenie poprzedniego obrotu" << std::endl;
  std::cout << "r - wyswietlenie macierzy rotacji" << std::endl;
  std::cout << "p - przesuniecie bryly o zadany wektor" << std::endl;
  std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
  std::cout << "s - sprawdzenie dlugosci przeciwleglych bokow" << std::endl;
  std::cout << "m - wyswietl menu" << std::endl;
  std::cout << "k - koniec dzialania programu" << std::endl << std::endl;
}

int main() {
  std::cout << "Project Rotation 3D based on C++ Boiler Plate v"
            << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
            << "."
            << PROJECT_VERSION_MINOR /* istotne zmiany */
            << "."
            << PROJECT_VERSION_PATCH /* naprawianie bugów */
            << "."
            << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
            << std::endl;

    PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("../datasets/prostopadloscian.dat",PzG::RR_Ciagly,2);
   //
   //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
   //      których połowa długości boku wynosi 2.
   //
/*   Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Punktowy,2); */
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  Lacze.ZmienTrybRys(PzG::TR_3D);

  char choice;
  int iterations;
  Matrix3x3 MatRot;
  std::cout << std::endl << "Prostopadłościan:" << std::endl;
  double T_Cub[8][SIZE] = {{200,100,50}, {100,100,50}, {200,300,50}, {100,300,50}, {200,300,100}, {100,300,100}, {200,100,100}, {100,100,100}};
  Cuboid Cub(T_Cub);
  std::cout << Cub << std::endl << std::endl;
  Cub.CompareSides();
  PrintMenu();

  if(!SaveCubToFile("../datasets/prostopadloscian.dat", Cub)) return 1;
  Lacze.Rysuj();

  while(choice!='k'){
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> choice;
      switch(choice){
        
        case 'o':{
          char axis;
          double degrees;
          MatRot.IdentityMatrix();
          std::cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach" << std::endl;
          std::cin >> axis;
          while(axis != '.'){
            std::cin >> degrees;
            if(axis == 'x' || axis == 'y' || axis == 'z'){
              MatRot.RotationMatrix(degrees, axis);
            } else {
              std::cout << ":( Bledne oznaczenie osi. Dopuszczalne znaki to: x y z ." << std::endl;
              std::cout << ":( Sprobuj jeszcze raz." << std::endl;
            }
            std::cin >> axis;
          }
          std::cout << std::endl << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
          std::cin >> iterations;
          Cub.Rotate(MatRot, iterations);
          Cub.CompareSides();
          if(!SaveCubToFile("../datasets/prostopadloscian.dat", Cub)) return 1;
          Lacze.Rysuj();
        break;
        }

        case 't':
          std::cout << "Powtorzono ostatni obrot" << std::endl << std::endl;
          Cub.Rotate(MatRot, iterations);
          Cub.CompareSides();
          if(!SaveCubToFile("../datasets/prostopadloscian.dat", Cub)) return 1;
          Lacze.Rysuj();          
        break;

        case 'r':
          std::cout << "Macierz ostatniej rotacji: " << std::endl << MatRot << std::endl;
        break;

        case 'p':{
          double x, y, z;
          std::cout <<  "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb" << std::endl;       
          std::cout << "tzn. wspolrzednej x, wspolrzednej y oraz wspolrzednej z" << std::endl;
          std::cin >> x >> y >> z;
          std::cout << std::endl;
          double T_Vector[SIZE] = {x, y, z};
          Vector3D Vector(T_Vector);

          Cub.Move(Vector);
          Cub.CompareSides();
          if(!SaveCubToFile("../datasets/prostopadloscian.dat", Cub)) return 1;
          Lacze.Rysuj();
        break;
        }

        case 'w':
          std::cout << "Wspolrzedne wierzcholkow: " << std::endl << std::endl << Cub << std::endl;
        break;

        case 's':
          Cub.CompareSides();
        break;

        case 'm':
          PrintMenu();
        break;

        case 'k':
        std::cout << "Koniec działania programu." << std::endl;
        break;

        default:
        std::cout << "Nieprawidlowy wybor opcji" << std::endl;
        break;
        }
      }  
  return 0;
}
