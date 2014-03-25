/**Clase PatternGenerator
 * Clase que implementa el generador de bases de datos de patrones
**/

#define POS 16
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector< vector<int> > succ(const vector<int>& root);

int main(){
  
  map<vector<int>,int> closed;

  //Generar el costo inicial y leer el patron deseado de stdin
  int cost = 0;
  vector<int> pattern;
  int temp;
  for(int i = 0; i<POS; ++i){
    scanf("%d",&temp);
    pattern.push_back(temp);
    printf("%d ",pattern[i]);
  }
  closed[pattern] = cost;
  printf("%d",cost);
  ++cost;
  printf("\n");

  //Ciclo general de procesamiento de patron
  vector< vector<int> > l;
  l.push_back(pattern);

  while(!l.empty()){
    vector< vector<int> > ltemp;
    for(int k = 0; k < l.size(); ++k){
      vector< vector<int> > l2(succ(l[k]));
      for(int i = 0; i<l2.size();++i){
        if(!closed.count(l2[i])){
          closed[l2[i]] = cost;
          ltemp.push_back(l2[i]);
          for(int j = 0; j<POS; ++j){
            printf("%d ",(l2[i])[j]);
          }
          printf("%d\n",cost);
        }
      }
    }
    ++cost;
    l = ltemp;
  }

}

/**
 * Obtiene todos los sucesores del estado
 * @return vector con los sucesores
**/        
vector< vector<int> > succ(const vector<int>& root){
  vector< vector<int> > res;
  int currentZero = 0;

  while(root[currentZero] != 0){
     ++currentZero;
  }

  if(currentZero > 3){
    vector<int> up(root);
    int temp = up[currentZero-4];
    up[currentZero-4] = 0;
    up[currentZero] = temp;
    res.push_back(up);
  }

  if(currentZero < 12){
    vector<int> down(root);
    int temp = down[currentZero+4];
    down[currentZero+4] = 0;
    down[currentZero] = temp;
    res.push_back(down);
  }

  if(currentZero != 0 and currentZero != 4 and currentZero != 8 and
    currentZero != 12){
    vector<int> left(root);
    int temp = left[currentZero-1];
    left[currentZero-1] = 0;
    left[currentZero] = temp;
    res.push_back(left);
  }

  if(currentZero != 3 and currentZero != 7 and currentZero != 11 and
    currentZero != 15){
    vector<int> right(root);
    int temp = right[currentZero+1];
    right[currentZero+1] = 0;
    right[currentZero] = temp;
    res.push_back(right);
  }

  return res;
}


