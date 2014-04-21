#include <cstring>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <vector>

#include "node.h"

template<class T> class astar
{
public:
    class CompareNode
    {
    public:
	bool operator()(const Node<T>* left, const Node<T>* right) const{
	    return left->heuristic == right->heuristic ?
		left->costFromRoot >= left->costFromRoot
		: left->heuristic >= right->heuristic;
	}
    };

    T goal;
    priority_queue<Node<T>*, vector<Node<T>*>, CompareNode> queue;
    unordered_set<long long int> close;
    unordered_map<long long int, Node<T>*> open;
    vector<T> succ;
    unsigned int nodos_expandidos = 0;
    
    Node<T>* search (T sta, T end, int (*h)(T input))
    {
	goal = end;
	Node<T>* inicio = new Node<T>(sta, (*h)(sta));
	
	queue.push(inicio);
	open[inicio->state.zip()] = inicio;
	
	while(!queue.empty()){
	    
	    Node<T>* node = queue.top();
	    
//	    cout << *node;
	    
	    queue.pop();
	    open.erase(node->state.zip());
	    close.insert(node->state.zip());
	    
	    if (node->parent == NULL && node->costFromRoot != 0){
		delete node;
		continue;
	    }

	    nodos_expandidos++;

	    if(node->state==end){
		cout<<"Nodos expandidos: "<<nodos_expandidos<<", Pasos para la solucion: "<<node->costFromRoot<<"\n";
		return node;
	    }

	    succ = node->state.getSucc();
	    	    
	    for(int i=0;i!=succ.size();i++){
	    	long long int ind = succ[i].zip();
		
		if(close.count(ind)>0) continue;
		
		unsigned int cost = node->costFromRoot+1;
		
		Node<T>* son;
		
		if(open.count(ind)>0){
		    son = open[ind];
		    if(cost<=son->costFromRoot){
			son->parent = NULL;
			
			Node<T>* sdson = new Node<T>(succ[i],cost,cost+(*h)(succ[i]));
			sdson->parent = node;

			open[ind] = sdson;
			queue.push(sdson);
		    };
		} else {
		    son = new Node<T>(succ[i],cost,cost+(*h)(succ[i]));
		    son->parent = node;
		
		    open[ind] = son;
		    queue.push(son);
		};
	    };
	    	    
	};
	return NULL;
    };
    
};
