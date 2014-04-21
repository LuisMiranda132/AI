#include <cstring>
#include <string.h>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <complex>
#include <list>
#include <unordered_set>
#define MAX 200000000

template<class T> class IDA_star
{

typedef pair<vector<T*>, int> pairPlan;

public:

    unsigned int nodos_generados = 0;

    /**
     *bounded_DFS: Implementacion de bounded_DFS en c++
     *@param n: Nodo inicial
     *@param t: Valor inicial de heuristica
     *return par <plan,t> resultante
    **/
    pairPlan* bounded_DFS(Node<T>* n, int t){
      //Si el f(n) es mayor a la heuristica inicial, no vale la pena seguir buscando
      //mas profundamente
      if(n->costFromRoot + n->heuristic > t){
        return new pairPlan(*(new vector<T*>),n->costFromRoot + n->heuristic);
      }

      //Si el estado actual es goal, retornar la solucion de ese estado
      if(n->state->is_goal()){
        return new pairPlan(n->extract_solution(),n->costFromRoot);
      }

      //Se consiguen los sucesores y se marca el movimiento de retorno
      int newT = MAX;
      vector<T*> succs(n->state->succ());

      //Por cada sucesor que no sea el de retorno, se hace bounded_DFS
      for(int i=0;i<succs.size();++i){
        Node<T>* m = new Node<T>(n, succs[i]);
        ++nodos_generados;
        pairPlan* temp = bounded_DFS(m,t);
        if(temp->first.size() != 0) return temp;
        delete(m);
        newT = min(newT,temp->second);
      } 

      return new pairPlan(*(new vector<T*>),newT);
    }

    /**
     *IDA_star: Implementacion de ida* en c++
     *@param initial: estado inicial
     *return par <plan,t> final
    **/
    pairPlan* search(T* sta, int (*h)(T* input)){
      //Nodo inicial y su heuristica
      Node<T>* inicio = new Node<T>(sta,(*h)(sta));
      ++nodos_generados;
      
      pairPlan* planCota = new pairPlan(*(new vector<T*>),inicio->heuristic);

      //Hacer bounded_DFS hasta encontrar la solucion o llegar a un callejon sin
      //salida
      while(planCota->second < MAX && planCota->first.size() == 0){
        planCota = bounded_DFS(inicio,planCota->second);
      }
      return planCota;
    }
};
