#include "patternGenerator1_5.h"
#include <algorithm>

using namespace std;

class PDB{

public:

   PatternGenerator1_5 first;
   PatternGenerator1_5 second;
   PatternGenerator1_5 third;

   PDB(){
     first.generate();
     second.generate();
     third.generate();
   }

   signed char heuristic(board state){
     array<signed char,16> f1 = state;
     array<signed char,16> f2 = state;
     array<signed char,16> f3 = state;

     for(int i=0;i<16;++i){
       if(f1[i] == 3 or f1[i] == 6 or f1[i] == 7 or f1[i] > 8) f1[i] = 0;
       if(f2[i] == 1 or f2[i] == 2 or f2[i] == 4 or f2[i] == 5 or f2[i] == 8 or f2[i] == 9 or f2[i] > 11) f2[i] = 0;
       if(f3[i] < 9 or f3[i] == 10 or f3[i] == 11) f3[i] = 0;
     }
       
     return first.closed[f1] + second.closed[f2] + third.closed[f3];
   }
};
