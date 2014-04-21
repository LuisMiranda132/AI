/** Clase Node
* Clase que implementa el nodo de un arbol de busqueda
* @param state: Estado que contiene el nodo
* @param parent: Apuntador al padre del nodo
* @param action: Accion que genero este nodo a partir del estado de su padre
* @param costFromRoot: Coste desde la raiz (g(n))
**/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

template<class T> class Node{

  public:
    T state;
    Node* parent;
    string action;
    int costFromRoot;
    int heuristic;
    bool nullPlan;
    int costSum;
    
    /**
     * Constructor de Nodo raiz (make-root-node)
     * @param s: Estado inicial
     * @return Nodo raiz construido
    **/
Node(T s, int h) : state(s), parent(), action(), costFromRoot(0), heuristic(h){}

Node(T s, int c, int h) : state(s), parent(), action(), costFromRoot(c), heuristic(h){}
    /**
     *Constructor de Nodo intermedio u hoja (make-node)
     *@param n: Apuntador al padre del nodo
     *@param a: Accion que genero este nodo a partir del estado de su padre
     *@param s: Estado contenido en el nodo
     *@return Nodo construido. Notese que la clase T debe saber calcular sus
     *costes
    **/
    /* Node(Node* n,string a,T s) : state(s), parent(n), action(a){ */
    /*   costFromRoot = n->costFromRoot + T::actionCost(s,a); */
    /* } */
    Node(Node* n,T s) : state(s), parent(n), action(){
	costFromRoot = n->costFromRoot + T::actionCost(s, this);
    }


    /**
     *Extrae la secuencia de acciones que llevan a la solucion
     *@return vector con la secuencia de acciones
    **/
    /* vector<string> extract_solution(){ */
    /*   vector<string> path; */
    /*   Node* n = this; */
    /*   while(n->parent != NULL){ */
    /*     path.insert(path.begin,n->action); */
    /*     n = n->parent; */
    /*   } */
    /*   return path; */
    /* } */
    vector<T> extract_solution(){
      vector<T> path;
      Node* n = this;
      while(n->parent != NULL){
	  /* path.push_back(n->action); */
	  path.push_back(n->state);
	  n = n->parent;
      }
      return path;
    }
};

