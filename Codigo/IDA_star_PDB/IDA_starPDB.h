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
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include <set>
#include <complex>
#include <list>
#include <unordered_set>
#include "node.h"
#include "pdb5.h"
#define MAX 120

int getTimestamp(){
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (int)now.tv_sec * 1000000;
}

template<class T> class IDA_starPDB{

public:

    unsigned int nodos_generados = 0;
    signed char threshold;
    vector<T> resVec;

    /**
     *bounded_DFS: Implementacion de bounded_DFS en c++
     *@param n: Nodo inicial
     *@param t: Valor inicial de heuristica
     *return par <plan,t> resultante
    **/
    signed char bounded_DFS(Node<T> n, signed char t, signed char g, PDB5<T>& generator){

      //Si el f(n) es mayor a la heuristica inicial, no vale la pena seguir buscando
      //mas profundamente
      if(g + n.heuristic > t){
        return g + n.heuristic;
      }

      //Si el estado actual es goal, retornar la solucion de ese estado
      if(n.state.is_goal()){
        resVec = n.extract_solution();
        return n.costFromRoot;
      }

      //Se consiguen los sucesores y se marca el movimiento de retorno
      signed char newT = MAX;
      signed char temp;
      vector<T> succs(n.state.succ());

      //Por cada sucesor que no sea el de retorno, se hace bounded_DFS
      for(int i=0;i<succs.size();++i){
        Node<T> m(&n, succs[i], generator.heuristic(succs[i]));
        ++nodos_generados;
        temp = bounded_DFS(m,t,g+1,generator);
        if(resVec.size() != 0){ 
          return temp;
        }
        if(temp < newT) newT = temp;
      } 

      return newT;
    }

    /**
     *IDA_star: Implementacion de ida* en c++
     *@param initial: estado inicial
     *return par <plan,t> final
    **/
    signed char search(T sta, PDB5<T>& generator){

      int startTime = getTimestamp();

      //Nodo inicial y su heuristica
      Node<T> result(sta,generator.heuristic(sta));
      ++nodos_generados;

      threshold = result.heuristic;

      //Hacer bounded_DFS hasta encontrar la solucion o llegar a un callejon sin
      //salida
      while(threshold < MAX && resVec.size() == 0){
        threshold = bounded_DFS(result,threshold,0,generator);
      }

      int endTime = getTimestamp();
      double secs = (endTime - startTime) / 1000000.0L;
      printf("Respuesta: %hhd -- ",threshold);
      printf("Tiempo: %f segundos -- ",secs);
      printf("Nodos generados: %d -- ",nodos_generados);
      printf("Nodos por segundo: %f",nodos_generados/secs);
      return threshold;
    }
};
