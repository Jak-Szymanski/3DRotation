#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

/*!
* \file
* \brief Definicja funkcji main programu i funkcji wyświetlania menu
*/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>


#include "scene.hh"
#include "exampleConfig.h"
#include "example.h"


#include "../inc/lacze_do_gnuplota.hh"

#define FILE_GLOBAL "../datasets/globalcoords.dat"
#define FILE_LOCAL "../datasets/localcoords.dat"

/*!
* \brief Wyświetlanie opcji menu programu
*/
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

/*!
* \brief Główna funkcja programu
* Funkcja zawiera opis interfejsu użytkownika programu i wywołuje wszystkie funkcje wykonywane przez program
*/
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
  Lacze.DodajNazwePliku(FILE_GLOBAL,PzG::RR_Ciagly,2);
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

  char choice;    // wybór opcji przez użytkownika
  std::ifstream file_local(FILE_LOCAL);   //plik zawierający współrzędne lokalne prostopadłościanu
  std::ifstream file_global(FILE_GLOBAL);   //plik do którego są wpisywane współrzędne globalne prostopadłościanu
  Matrix3x3 MatRot;   //macierz obrotu
  unsigned int iterations;    //ile razy powinien zostać wykonany obrót prostopadłościanu

  Cuboid cub;   //prostopadłościan
  file_local >> cub;    //zapisanie do prostopadłościanu zmiennych lokalnych  
  Scene Scene(cub);     //inicjacja sceny prostopadłościanu

  if(!Scene.CalcGlobalCoords(FILE_GLOBAL)) return 1;
  PrintMenu();
  Lacze.Rysuj();

  while(choice!='k'){
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> choice;
      switch(choice){
        
        case 'o':{        //obrót prostopadłościanu
          char axis;
          double degrees;
          MatRot.IdentityMatrix();
          std::cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach" << std::endl;
          std::cin >> axis;
          while(axis != '.'){
            std::cin >> degrees;
              if(axis != 'x' && axis != 'y' && axis != 'z'){
                std::cout << ":( Bledne oznaczenie osi. Dopuszczalne znaki to: x y z ." << std::endl;
                std::cout << ":( Sprobuj jeszcze raz." << std::endl;
              } else {
                MatRot.RotationMatrix(degrees, axis);
              }
            std::cin >> axis;
          }
          std::cout << std::endl << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
          std::cin >> iterations;
          Scene.ChangeAngles(MatRot, iterations);
          if(!Scene.CalcGlobalCoords(FILE_GLOBAL)) return 1;
          Lacze.Rysuj();
        break;
        }

        case 't':     //powtórzenie ostatniego obrotu
          std::cout << "Powtorzono ostatni obrot" << std::endl << std::endl;
          Scene.ChangeAngles(MatRot, iterations);
          if(!Scene.CalcGlobalCoords(FILE_GLOBAL)) return 1;
          Lacze.Rysuj();          
        break;

        case 'r':{    //wyświetlenie ostatniej macierzy rotacji
          std::cout << "Macierz ostatniej rotacji: " << std::endl << MatRot << std::endl;
        break;
        }

        case 'p':{    //przesunięcie prostopadłościanu o wektor
          double x, y, z;
          std::cout <<  "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb" << std::endl;       
          std::cout << "tzn. wspolrzednej x, wspolrzednej y oraz wspolrzednej z" << std::endl;
          std::cin >> x >> y >> z;
          std::cout << std::endl;
          double T_Vector[SIZE] = {x, y, z};
          Vector3D Vector(T_Vector);
          Scene.ChangeTranslation(Vector);
          if(!Scene.CalcGlobalCoords(FILE_GLOBAL)) return 1;  
          Lacze.Rysuj();
        break;
        }

        case 'w':   //wyświetlenie współrzędnych prostopadłościanu
          std::cout << "Wspolrzedne wierzcholkow: " << std::endl << std::endl << std::endl;
          file_global >> cub;
          std::cout << cub;
        break;

        case 's':   //porównanie długości boków prostopadłościanu
          file_global >> cub;
          cub.CompareSides();          
        break;


        case 'm':   //wyświetlenie menu
          PrintMenu();
        break;

        case 'k':   //koniec działania programu
        std::cout << "Koniec działania programu." << std::endl;
        break;

        default:
        std::cout << "Nieprawidlowy wybor opcji" << std::endl;
        break;
        }
      }  
  return 0;
}
