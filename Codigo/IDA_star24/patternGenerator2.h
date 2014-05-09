#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include <unordered_map>
#include <map>

using namespace std;

typedef array<signed char,25> board;

struct board_hash{

  size_t operator()(board b) const{
    size_t init = 0;

    for(int i=1;i<25;++i){
      if(b[i] != -1){
        init += i * b[i] + i;
      }
    }

    return init;
  }
};


class PatternGenerator2{
public:
    map<board, signed char> closed;
    
    void generate(){
	signed char cost = 0;
	board pattern;
	signed char temp;
	for(int i = 0; i<25; ++i){
	    scanf("%hhd",&temp);
	    pattern[i] = temp;
	}
	
	closed[pattern] = cost;
	++cost;


	//Ciclo general de procesamiento de patron
	vector<board> l;
	l.push_back(pattern);

	while(!l.empty()){
	  vector<board> ltemp;
	  for(int k = 0; k < l.size(); ++k){
	    vector<board> succs = nuevos(l[k]);

	    for(int i = 0; i<succs.size();++i){
	      if(!closed.count(succs[i])){
	        closed[succs[i]] = cost;
	        ltemp.push_back(succs[i]);
	      }
            }
	  }
	  ++cost;
	  l = ltemp;
	}
    }

    vector<board> nuevos(board& padre) {
      vector<board> res;
      for (int i = 0; i < 25; ++i ){
        if(padre[i] != 0){
          //si puede moverse hacia arriba
          if (i>4 and padre[i-4] == 0) {
            swap(padre[i],padre[i-4]);
            res.push_back(padre);
            swap(padre[i],padre[i-4]);
          }

          //si puede moverse a la izquierda
          if (i!=0 and i!=5 and i!=10 and i!=15 and i!=20 and padre[i-1] == 0) {
            swap(padre[i],padre[i-1]);
            res.push_back(padre);
            swap(padre[i],padre[i-1]);
          }

          //si puede moverse hacia abajo
          if (i<20 and padre[i+4] == 0) {
            swap(padre[i],padre[i+4]);
            res.push_back(padre);
            swap(padre[i],padre[i+4]);
          }

          //si puede moverse a la derecha
          if (i!=4 and i!=9 and i!=14 and i!=19 and i!=24 and padre[i+1] == 0) {
            swap(padre[i],padre[i+1]);
            res.push_back(padre);
            swap(padre[i],padre[i+1]);
          }
        }
      }
      return res;
    }
    
};
