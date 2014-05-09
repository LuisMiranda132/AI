/** Class 15puzzle
* Clase que implementa los estados del problema 15puzzle
* @param argc: Numero de argumentos pasados por linea de comandos
* @param argv: Arreglo con los argumentos de linea de comandos
**/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "IDA_star.h"
#include "manhattan.h"

using namespace std;

int main( int argc, char *argv[] ){
    //Creacion del estado inicial
    array<signed char,16> dummy;
    signed char init;
    int numCase = 1;

    //Lectura de sdtin. Lee hasta que no hayan mas casos
    while(scanf("%hhd",&init) != EOF){
      dummy[0] = init;

      for(int i=1;i<16;++i){
        scanf("%hhd",&init);
        dummy[i] = init;
      }

      //Se crea la representacion inicial y se corre IDA_star con la misma como
      //nodo inicial
      ArrayState derp(dummy,'I');
      IDA_star<ArrayState> news;
    
      printf("Caso #%d -- ",numCase++);
      signed char prueba = news.search(derp,manhattan);
      printf("\n");
    }
}
