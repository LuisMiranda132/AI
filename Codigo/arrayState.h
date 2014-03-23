/** Clase ArrayState
* Clase que implementa un estado de 15-puzzle usando un vector de enteros
* @param boardState: Estado del tablero
**/

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class ArrayState{

  public:
    vector<int> boardState;

    /**
     * Constructor de estado (init())
     * @param state: Estado inicial
     * @return estado construido
    **/
    ArrayState(vector<int> state) : boardState(state){}

    /**
     * Verifica si el estado es un estado goal
     * @return true si es goal, false si no
    **/
    bool is_goal(){
      int goalArray[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
      vector<int> compar(goalArray, goalArray + sizeof(goalArray)/sizeof(int));

      return boardState == compar;
    }

   /**
    * Obtiene todos los sucesores del estado
    * @return vector con los sucesores
   **/
   vector<ArrayState> succ(){
     vector<ArrayState> res;
     int currentZero = 0;

     while(boardState[currentZero] != 0){
        ++currentZero;
     }

     if(currentZero > 3){
       vector<int> up(boardState);
       int temp = up[currentZero-4];
       up[currentZero-4] = 0;
       up[currentZero] = temp;
       ArrayState upRes(up);
       res.push_back(upRes);
     }
 
     if(currentZero < 12){
       vector<int> down(boardState);
       int temp = down[currentZero+4];  
       down[currentZero+4] = 0;
       down[currentZero] = temp;
       ArrayState downRes(down);
       res.push_back(downRes);
     }

     if(currentZero != 0 and currentZero != 4 and currentZero != 8 and
        currentZero != 12){
       vector<int> left(boardState);
       int temp = left[currentZero-1];
       left[currentZero-1] = 0;
       left[currentZero] = temp;
       ArrayState leftRes(left);
       res.push_back(leftRes);
     }

     if(currentZero != 3 and currentZero != 7 and currentZero != 11 and 
        currentZero != 15){
       vector<int> right(boardState);
       int temp = right[currentZero+1];
       right[currentZero+1] = 0;
       right[currentZero] = temp;
       ArrayState rightRes(right);
       res.push_back(rightRes);
     }

     return res;
   }

   /**
    * Retorna el costo de todo movimiento
    * @return 1, el costo en 15-puzzle
   **/
   static int actionCost(ArrayState s, string a){
     return 1;
   }
}; 
