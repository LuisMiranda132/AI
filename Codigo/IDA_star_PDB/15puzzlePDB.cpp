/** Class 15puzzlePDB
* Clase que implementa la solucion de 15puzzle usando PDB
* @param argc: Cantidad de argumentos 
* @param argv: Arreglo de argumentos
**/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <array>
#include "IDA_starPDB.h"
#include "arrayState.h"

using namespace std;

int main( int argc, char *argv[] ){
    //Se crea el estado inicial 
    array<signed char,16> dummy;
    signed char init;
    int numCase = 1;

    //Se genera la base de datos de patrones
    PDB5<ArrayState> generator;

    //Se leen casos hasta que ya no hayan mas
    while(scanf("%hhd",&init) != EOF){
      dummy[0] = init;

      for(int i=1;i<16;++i){
        scanf("%hhd",&init);
        dummy[i] = init;
      }

      ArrayState derp(dummy,'I');
      IDA_starPDB<ArrayState> news;
      printf("Caso #%d -- ",numCase++);
      signed char prueba = news.search(derp,generator);
      printf("\n");
    }
}
