/**
 *Programa que resuelve el 15-Puzzle con la heuristica manhattan y usando IDA*
**/
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
#include "node.h"
#include "arrayState.h"
#include "manhattan.h"
#define MAX 200000000

using namespace std;

int numNodes = 0;

/**
 *bounded_DFS: Implementacion de bounded_DFS en c++
 *@param n: Nodo inicial
 *@param t: Valor inicial de heuristica
 *return par <plan,t> resultante
**/
pair< vector<string>, int> bounded_DFS(Node<ArrayState> n, int t){
  int temp = n.costFromRoot + manhattan(n.state.boardState);
  vector<string> null_vec;
  pair < vector<string>, int> res1(null_vec, temp);

  //Si el f(n) es mayor a la heuristica inicial, no vale la pena seguir buscando
  //mas profundamente
  if(temp > t){
    return res1;
  }

  //Si el estado actual es goal, retornar la solucion de ese estado
  if(n.state.is_goal()){
    pair< vector<string>, int> res2(n.extract_solution(),n.costFromRoot);
    return res2;
  }

  //Se consiguen los sucesores y se marca el movimiento de retorno
  int newT = MAX;
  vector<ArrayState> succs(n.state.succ());
  string mirrorAction("INIT");
  if(n.action == "UP"){
    mirrorAction = "DOWN";
  }else if(n.action == "DOWN"){
    mirrorAction = "UP";
  }else if(n.action == "LEFT"){
    mirrorAction = "RIGHT";
  }else if(n.action == "RIGHT"){
    mirrorAction = "LEFT";
  }

  //Por cada sucesor que no sea el de retorno, se hace bounded_DFS
  for(int i=0;i<succs.size();++i){
    if(succs[i].action != mirrorAction){
      Node<ArrayState> n2(&n,succs[i].action,succs[i]);
      ++numNodes;
      pair< vector<string>, int> res3(bounded_DFS(n2,t));
      if(res3.first.size() != 0){
        return res3;
      }
      newT = min(newT,res3.second);
    }
  } 

  //Si no se consigue una solucion, se retorna <null,newT>
  pair< vector<string>, int> res4(null_vec,newT);
  return res4;
}

/**
 *IDA_star: Implementacion de ida* en c++
 *@param initial: estado inicial
 *return par <plan,t> final
**/
pair< vector<string>, int> IDA_star(vector<int> initial){
  //Nodo inicial y su heuristica
  ArrayState init(initial,"INIT");
  Node<ArrayState> n(init);
  ++numNodes;
  int t = manhattan(n.state.boardState);

  //Par <plan,t> a regresar
  pair< vector<string>, int> cur; 
  vector<string> res;
  cur.first = res;
  
  //Hacer bounded_DFS hasta encontrar la solucion o llegar a un callejon sin
  //salida
  while(t < MAX && cur.first.size() == 0){
    cur = bounded_DFS(n,t);
    if(cur.first.size() != 0) return cur;
    t = cur.second;
  }
  return cur;
} 

/**
 *Programa Principal: Lee las instancias de stdin e imprime los resultados
**/
int main(){
  int init;
  int caseNo = 1;
  while(scanf("%d",&init) != EOF){
    vector<int> board;
    board.push_back(init);

    for(int i=0;i<15;++i){
      scanf("%d",&init);
      board.push_back(init);
    }

    pair< vector<string>,int> resp(IDA_star(board));

    printf("Case #%d: ",caseNo);
    printf("%d\nSteps: ",resp.second);
    for(int i=0;i<resp.first.size();++i){
      printf("%s ",resp.first[i].c_str());
    }
    printf("\nNumber of nodes generated: %d\n",numNodes);
    numNodes = 0;
    ++caseNo;
  }
  return 0;
}
