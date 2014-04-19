/** Manhattan: Libreria de funciones que implementan la heuristica manhattan 
*/
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
#include <array>
#include <set>
#include <complex>
#include <list>

using namespace std;

array<int,16> dist0 = {0,1,2,3,1,2,3,4,2,3,4,5,3,4,5,6};
array<int,16> dist1 = {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5};
array<int,16> dist2 = {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4};
array<int,16> dist3 = {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3};
array<int,16> dist4 = {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5};
array<int,16> dist5 = {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4};
array<int,16> dist6 = {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3};
array<int,16> dist7 = {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2};
array<int,16> dist8 = {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4};
array<int,16> dist9 = {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3};
array<int,16> dist10 = {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2};
array<int,16> dist11 = {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1};
array<int,16> dist12 = {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3};
array<int,16> dist13 = {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2};
array<int,16> dist14 = {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1};
array<int,16> dist15 = {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0};
array< array<int,16>,16> dists = {dist0,dist1,dist2,dist3,dist4,dist5,dist6,dist7,dist8,dist9,dist10,dist11,dist12,dist13,dist14,dist15};

/**Calcula la heuristica manhattan dado un estado del tablero
 *@param pat: Vector de enteros que representa un estado del tablero
 *@return: Valor de la heuristica
**/
int manhattan(vector<int> pat){
  int res = 0;
  int curTarget = 0;
  for(int x = 0;x<16;++x){
    res += (dists[x])[pat[x]];
  } 
  return res;
}
