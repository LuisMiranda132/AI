/** Clase Node
* Clase que implementa el nodo de un arbol de busqueda
* @param state: Estado que contiene el nodo
* @param parent: Apuntador al padre del nodo
* @param costFromRoot: Coste desde la raiz (g(n))
* @param heuristic: Valor de la heuristica del nodo
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
    signed char costFromRoot;
    signed char heuristic;
    
    /**
     * Constructor de Nodo raiz (make-root-node)
     * @param s: Estado del nodo
     * @param h: Valor de la heuristica
     * @return Nodo raiz construido
    **/
    Node(T s, signed char h) : state(s), parent(), costFromRoot(0), heuristic(h){}

    //Constructor que incluye el costo desde la raiz
    Node(T s, signed char c, signed char h) : state(s), parent(), costFromRoot(c), heuristic(h){}
  
    //Constructor de nodo en base a un padre
    Node(Node* n,T s) : state(s), parent(n){
	costFromRoot = n->costFromRoot + 1;
    }

    //Constructor de nodo con padre que incluye la heuristica
    Node(Node* n,T s, signed char h) : state(s), parent(n), heuristic(h){
        costFromRoot = n->costFromRoot + 1;
    }

    /**
     *Extrae la secuencia de acciones que llevan a la solucion
     *@return vector con la secuencia de estados
    **/
    vector<T> extract_solution(){
      vector<T> path;
      Node* n = this;
      while(n->parent != NULL){
	  path.push_back(n->state);
	  n = n->parent;
      }
      if(path.size() == 0){
        path.push_back(n->state);
      }
      return path;
    }
};

