/** Clase ArrayState
* Clase que implementa un estado de 15-puzzle usando un vector de enteros
* @param boardState: Estado del tablero
**/

#include <stdlib.h>
#include <vector>
#include <array>
#include <algorithm>
#define XORSWAP(a, b)	((a)^=(b),(b)^=(a),(a)^=(b))

using namespace std;

class ArrayState{

  public:
    array<signed char,25> boardState;
    char currentZero = 0;
    char action;

    /**
     * Constructor de estado (init())
     * @param state: Estado inicial
     * @return estado construido
    **/
    ArrayState(array<signed char,25>& state, char act) : boardState(state),action(act){
      while(boardState[currentZero] != 0){
        ++currentZero;
      }
    }

    ArrayState(array<signed char,25>& state, char act, char zero) : boardState(state),action(act),currentZero(zero){}

    /**
     * Verifica si el estado es un estado goal
     * @return true si es goal, false si no
    **/
    bool is_goal(){
      int goalArray[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
      for(int i=0;i<25;++i){
        if(goalArray[i] != boardState[i]) return false;
      }
      return true;
    }

   /**
    * Obtiene todos los sucesores del estado
    * @return vector con los sucesores
   **/
   vector<ArrayState> succ(){
     vector<ArrayState> res;

     if(currentZero > 4 and action != 'D'){
       swap(boardState[currentZero-4],boardState[currentZero]);
       ArrayState u(boardState,'U',currentZero-4);
       swap(boardState[currentZero-4],boardState[currentZero]);
       res.push_back(u);
     }
 
     if(currentZero < 20 and action != 'U'){
       swap(boardState[currentZero+4],boardState[currentZero]);
       ArrayState d(boardState,'D',currentZero+4);
       swap(boardState[currentZero+4],boardState[currentZero]);
       res.push_back(d);
     }

     if(currentZero != 0 and currentZero != 5 and currentZero != 10 and
       currentZero != 15 and currentZero != 20 and action != 'R'){
       swap(boardState[currentZero-1],boardState[currentZero]);
       ArrayState l(boardState,'L',currentZero-1);
       swap(boardState[currentZero-1],boardState[currentZero]);
       res.push_back(l);
     }

     if(currentZero != 4 and currentZero != 9 and currentZero != 14 and 
        currentZero != 19 and currentZero != 24 and action != 'L'){
       swap(boardState[currentZero+1],boardState[currentZero]);
       ArrayState ri(boardState,'R',currentZero+1);
       swap(boardState[currentZero+1],boardState[currentZero]);
       res.push_back(ri);
     }

     return res;
   }

   /**
    * Retorna el costo de todo movimiento
    * @return 1, el costo en 15-puzzle
   **/
   static int actionCost(){
     return 1;
   }

   void print(){
     for(int i=0;i<16;++i){
       printf("%hhd ",boardState[i]);
     }
   }
};
