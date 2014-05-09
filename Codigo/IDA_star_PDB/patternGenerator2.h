#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <array>
#include <map>

using namespace std;

//Nuebo tipo para hacer mas leible el codigo
typedef array<signed char,16> board;

/**
 *Clase PatternGenerator2: Clase que genera patrones de bases de datos
 *@param closed: Diccionario que se usa para accesar a la base
**/
template<class T> class PatternGenerator2{
public:
    map<board, signed char> closed;
   
    /**
     *Genera la base de datos al popular el mapa closed
    **/ 
    void generate(){
        //Se lee el patron objetivo
	signed char cost = 0;
	array<signed char,16> pattern;
	signed char temp;
	for(int i = 0; i<16; ++i){
	    scanf("%hhd",&temp);
	    pattern[i] = temp;;
	}

	T smallPattern(pattern,'I');
	
	closed[smallPattern.boardState] = cost;
	++cost;

	//Ciclo general de procesamiento de patron
	vector<T> l;
	l.push_back(smallPattern);

	while(!l.empty()){
	  vector<T> ltemp;
	  for(int k = 0; k < l.size(); ++k){
	    vector<T> succs = l[k].succ();

	    for(int i = 0; i<succs.size();++i){
	      if(!closed.count(succs[i].boardState)){
	        closed[succs[i].boardState] = cost;
	        ltemp.push_back(succs[i]);
	      }
            }
	  }
	  ++cost;
	  l = ltemp;
	}
    }
    
};

    
