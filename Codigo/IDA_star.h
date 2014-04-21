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

public:

    T goal;
    vector<T> succ;
    unsigned int nodos_generados = 0;

    /**
     *bounded_DFS: Implementacion de bounded_DFS en c++
     *@param n: Nodo inicial
     *@param t: Valor inicial de heuristica
     *return par <plan,t> resultante
    **/
    Node<T>* bounded_DFS(Node<T>* n){
      //Si el f(n) es mayor a la heuristica inicial, no vale la pena seguir buscando
      //mas profundamente
      if(n->costSum > n->heuristic){
        return n;
      }

      //Si el estado actual es goal, retornar la solucion de ese estado
      if(n->state == goal){
        n->nullPlan = false;
        n->sumCost = n->costFromRoot;
        return n;
      }

      //Se consiguen los sucesores y se marca el movimiento de retorno
      int newT = MAX;
      succ = n->state.getSucc();

      //Por cada sucesor que no sea el de retorno, se hace bounded_DFS
      for(int i=0;i<succ.size();++i){
        Node<T>* m = new Node<T>(n, succ[i]);
        ++nodos_generados;
        m = bounded_DFS(m);
        if(!m->nullPlan) return m;
        newT = min(newT,m->sumCost);
      } 

      n->sumCost = newT;
      return n;
    }

    /**
     *IDA_star: Implementacion de ida* en c++
     *@param initial: estado inicial
     *return par <plan,t> final
    **/
    Node<T>* search(T sta, T end, int (*h)(T input)){
      //Nodo inicial y su heuristica
      goal = end;
      Node<T>* inicio = new Node<T>(sta,(*h) sta);
      ++nodos_generados;

      Node<T>* res = inicio;
      res->costSum = res->heuristic;
      res->nullPlan = true;

      //Hacer bounded_DFS hasta encontrar la solucion o llegar a un callejon sin
      //salida
      while(res->costSum < MAX && res->nullPlan){
        res = bounded_DFS(res);
      }
      return res;
    }


