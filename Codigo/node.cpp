/** Clase Node
* Clase que implementa el nodo de un arbol de busqueda
* @param state: Estado que contiene el nodo
* @param parent: Apuntador al padre del nodo
* @param action: Accion que genero este nodo a partir del estado de su padre
* @param costFromRoot: Coste desde la raiz (g(n))
**/

#include <stdlib>
#include <Action.cpp>
#include <vector>

using namespace std;

template<class T>

class Node{

  public:
    T state;
    Node* parent;
    Action action;
    int costFromRoot;

    /**
     * Constructor de Nodo raiz (make-root-node)
     * @param s: Estado inicial
     * @return Nodo raiz construido
    **/
    Node(T s) : state(s), parent(NULL), action(NULL), costFromRoot(0){}

    /**
     *Constructor de Nodo intermedio u hoja (make-node)
     *@param n: Apuntador al padre del nodo
     *@param a: Accion que genero este nodo a partir del estado de su padre
     *@param s: Estado contenido en el nodo
     *@return Nodo construido. Notese que la clase T debe saber calcular sus
     *costes
    **/
    Node(Node* n,Action a,T s) : state(s), parent(n), action(a){
      this.costFromRoot = n->costFromRoot + T::actionCost(s,a)
    }

    /**
     *Extrae la secuencia de acciones que llevan a la solucion
     *@return vector con la secuencia de acciones
    **/
    vector<Action> extract-solution(){
      vector<Action> path;
      Node* n = this;
      while(n->parent != NULL){
        path.insert(path.begin,n->action);
        n = n->parent;
      }
      return path;
    }
};
