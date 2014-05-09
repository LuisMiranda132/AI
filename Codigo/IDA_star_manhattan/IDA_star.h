#include <cstring>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include "node.h"
#define MAX 120

/**
 *Obtiene el tiempo transcurrido desde el inicio del programa
 *@return: Tiempo transcurrido en microsegundos
**/
int getTimestamp(){
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (int)now.tv_sec * 1000000;
}

/**
 *Clase IDA_star: Clase que implementa IDA* usando manhattan
 *@param nodos_generados: Cantidad de nodos generados
 *@param threshold: Limite de profundidad actual
 *@param resVec: Vector de resultados
**/
template<class T> class IDA_star{

public:

    unsigned int nodos_generados = 0;
    signed char threshold;
    vector<T> resVec;

    /**
     *bounded_DFS: Implementacion de bounded_DFS en c++
     *@param n: Nodo inicial
     *@param t: Valor del limite de profundidad
     *@param g: Valor del costo desde la raiz
     *@paran h: Funcion heuristica que acepta un estado
     *return costo de la solucion o nuevo limite de profundidad
    **/
    signed char bounded_DFS(Node<T> n, signed char t, signed char g, signed char (*h)(T input)){

      //Si el estado actual es goal, retornar la solucion de ese estado
      if(n.heuristic == 0){
        resVec = n.extract_solution();
        return n.costFromRoot;
      }

      //Si el f(n) es mayor al limite de profundidad, no vale la pena seguir buscando
      //mas profundamente
      if(g + n.heuristic > t){
        return g + n.heuristic;
      }

      //Se consiguen los sucesores
      signed char newT = MAX;
      signed char temp;
      vector<T> succs(n.state.succ());

      //Por cada sucesor, se hace bounded_DFS. ArrayState se encarga de eliminar
      //el estado de retorno
      for(int i=0;i<succs.size();++i){
        Node<T> m(&n, succs[i], (*h)(succs[i]));
        ++nodos_generados;
        temp = bounded_DFS(m,t,g+1,h);
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
    signed char search(T sta, signed char (*h)(T input)){

      int startTime = getTimestamp();

      //Nodo inicial y su heuristica
      Node<T> result(sta,(*h)(sta));
      ++nodos_generados;

      threshold = result.heuristic;

      //Hacer bounded_DFS hasta encontrar la solucion o llegar a un callejon sin
      //salida
      while(threshold < MAX && resVec.size() == 0){
        threshold = bounded_DFS(result,threshold,0,h);
      }

      //Calculo de tiempo e impresion de resultados
      int endTime = getTimestamp();
      double secs = (endTime - startTime) / 1000000.0L;
      printf("Tamaño del camino: %hhd -- ",threshold);
      printf("Tiempo: %f segundos -- ",secs);
      printf("nodos generados: %d -- ",nodos_generados);
      printf("nodos por segundo: %f",nodos_generados/secs);

      return threshold;
    }
};
