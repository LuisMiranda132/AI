#include "patternGenerator2.h"
#include <algorithm>

using namespace std;

/**
 *Clase PDB5: Clase que implementa la base 5-5-5 de 15-Puzzle
 *@param first: Primera base disjunta
 *@param second: Segunda base disjunta
 *@param third: Tercera base disjunta
**/
template<class T> class PDB5{

public:

   PatternGenerator2<T> first;
   PatternGenerator2<T> second;
   PatternGenerator2<T> third;

   /**
    *Constructor de PDB5 que genera las bases
   **/
   PDB5(){
     first.generate();
     second.generate();
     third.generate();
   }

   /**
    *Calcula la heuristica de un estado del tablero
    *@param state: Estado del cual se quiere saber la heuristica
    *@return suma de los costos del estado en cada base
   **/
   signed char heuristic(T state){
     array<signed char,16> f1 = state.boardState;
     array<signed char,16> f2 = state.boardState;
     array<signed char,16> f3 = state.boardState;

     for(int i=0;i<16;++i){
       if(f1[i] == 3 or f1[i] == 6 or f1[i] == 7 or f1[i] > 8) f1[i] = -1;
       if(f2[i] == 1 or f2[i] == 2 or f2[i] == 4 or f2[i] == 5 or f2[i] == 8 or f2[i] == 9 or f2[i] > 11) f2[i] = -1;
       if((f3[i] < 9 and f3[i] > 0) or f3[i] == 10 or f3[i] == 11) f3[i] = -1;
     }
       
     return (first.closed[f1] + second.closed[f2] + third.closed[f3])/2.2;
   }
};
