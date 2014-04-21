/** Clase ArrayState
* Clase que implementa un estado de 15-puzzle usando un vector de enteros
* @param boardState: Estado del tablero
**/

#include <stdlib.h>
#include <vector>
#include <string>
#include <array>

using namespace std;

class ArrayState{

  public:
    array<int,16> boardState;
    string action;

    /**
     * Constructor de estado (init())
     * @param state: Estado inicial
     * @return estado construido
    **/
    ArrayState(array<int,16>* state, string act) : boardState(*state),action(act){}

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
   vector<ArrayState*> succ(){
     vector<ArrayState*> res;
     int currentZero = 0;
     int currentIndex = 0;

     while(boardState[currentZero] != 0){
        ++currentZero;
     }

     if(currentZero > 3){
       array<int,16> up;
       for(int i=0;i<16;++i) up[i] = boardState[i];
       int temp = up[currentZero-4];
       up[currentZero-4] = 0;
       up[currentZero] = temp;
       res.push_back(new ArrayState(&up,"UP"));
     }
 
     if(currentZero < 12){
       array<int,16> down;
       for(int i=0;i<16;++i) down[i] = boardState[i];
       int temp = down[currentZero+4];  
       down[currentZero+4] = 0;
       down[currentZero] = temp;
       res.push_back(new ArrayState(&down,"DOWN"));
     }

     if(currentZero != 0 and currentZero != 4 and currentZero != 8 and
       currentZero != 12){
       array<int,16> left;
       for(int i=0;i<16;++i) left[i] = boardState[i];
       int temp = left[currentZero-1];
       left[currentZero-1] = 0;
       left[currentZero] = temp;
       res.push_back(new ArrayState(&left,"LEFT"));
     }

     if(currentZero != 3 and currentZero != 7 and currentZero != 11 and 
        currentZero != 15){
       array<int,16> right;
       for(int i=0;i<16;++i) right[i] = boardState[i];
       int temp = right[currentZero+1];
       right[currentZero+1] = 0;
       right[currentZero] = temp;
       res.push_back(new ArrayState(&right,"RIGHT"));
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
};
