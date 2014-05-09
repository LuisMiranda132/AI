/** Class 15puzzle
* Clase que implementa los estados del problema 15puzzle
* @param half_up: Entero que representa la parte de arriba del tablero
* @param half_down: Entero que representa la parte de abajo del tablero
* @param zero: Posicion del 0 en este momento
**/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <array>
#include <map>
#include "IDA_starPDB.h"
#include "arrayState.h"

using namespace std;

int main( int argc, char *argv[] ){
    array<signed char,25> dummy;
    signed char init;
    int numCase = 1;

    PDB5 generator;

    while(scanf("%hhd",&init) != EOF){
      dummy[0] = init;

      for(int i=1;i<25;++i){
        scanf("%hhd",&init);
        dummy[i] = init;
      }

      ArrayState derp(dummy,'I');
      IDA_starPDB<ArrayState> news;
      printf("Caso #%d -- ",numCase);
      ++numCase;
      signed char prueba = news.search(derp,generator);
      printf("\n");
    }
}
