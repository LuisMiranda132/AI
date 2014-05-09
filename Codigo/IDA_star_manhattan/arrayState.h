/** Clase ArrayState
* Clase que implementa un estado de 15-puzzle usando un vector de enteros
* @param boardState: Estado del tablero
* @param currentZero: Posicion de la ficha vacia
* @param action: Caracter que indica la accion que llevo a este estado. I
*                representa el estado inicial
**/

#include <stdlib.h>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

class ArrayState{

  public:
    array<signed char,16> boardState;
    char currentZero = 0;
    char action;

    /**
     * Constructor de estado (init())
     * @param state: Estado del tablero
     * @param act: Accion del estado
     * @return estado construido
    **/
    ArrayState(array<signed char,16>& state, char act) : boardState(state),action(act){
      while(boardState[currentZero] != 0){
        ++currentZero;
      }
    }

    /**
     *Constructor de estado con la posicion del cero pasada como argumento
     *@param state: Estado del tablero
     *@param act: Accion del estado
     *@param zero: Posicion del cero
    **/

    ArrayState(array<signed char,16>& state, char act, char zero) : boardState(state),action(act),currentZero(zero){}

    /**
     * Verifica si el estado es un estado goal
     * @return true si es goal, false si no
    **/
    bool is_goal(){
      int goalArray[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
      for(int i=0;i<16;++i){
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

     if(currentZero > 3 and action != 'D'){
       swap(boardState[currentZero-4],boardState[currentZero]);
       ArrayState u(boardState,'U',currentZero-4);
       swap(boardState[currentZero-4],boardState[currentZero]);
       res.push_back(u);
     }
 
     if(currentZero < 12 and action != 'U'){
       swap(boardState[currentZero+4],boardState[currentZero]);
       ArrayState d(boardState,'D',currentZero+4);
       swap(boardState[currentZero+4],boardState[currentZero]);
       res.push_back(d);
     }

     if(currentZero != 0 and currentZero != 4 and currentZero != 8 and
       currentZero != 12 and action != 'R'){
       swap(boardState[currentZero-1],boardState[currentZero]);
       ArrayState l(boardState,'L',currentZero-1);
       swap(boardState[currentZero-1],boardState[currentZero]);
       res.push_back(l);
     }

     if(currentZero != 3 and currentZero != 7 and currentZero != 11 and 
        currentZero != 15 and action != 'L'){
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

   /**
    * Imprime el estado del tablero
   **/
   void print(){
     for(int i=0;i<16;++i){
       printf("%hhd ",boardState[i]);
     }
   }
};
