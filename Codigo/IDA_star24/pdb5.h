#include "patternGenerator2.h"
#include <algorithm>

using namespace std;

class PDB5{

public:

   PatternGenerator2 first;
   PatternGenerator2 second;
   PatternGenerator2 third;
   PatternGenerator2 fourth;

   PDB5(){
     first.generate();
     second.generate();
     third.generate();
     fourth.generate();
   }

   signed char heuristic(board state){
     array<signed char,25> f1 = state;
     array<signed char,25> f2 = state;
     array<signed char,25> f3 = state;
     array<signed char,25> f4 = state;

     for(int i=0;i<25;++i){
       if(f1[i] == 3 or f1[i] == 4 or f1[i] == 8 or f1[i] == 9 or f1[i] == 10 or f1[i] == 11 or f1[i] > 12) f1[i] = 0;
       if(f2[i] == 1 or f2[i] == 2 or f2[i] == 4 or f2[i] == 5 or f2[i] == 8 or f2[i] == 9 or f2[i] > 11) f2[i] = 0;
       if(f3[i] < 10 or f3[i] == 12 or f3[i] == 13 or f3[i] == 14 or (f3[i] >= 15 and f3[i] <= 17) or f3[i] > 19) f3[i] = 0;
       if(f4[i] < 17 or f4[i] == 20 or f4[i] == 21) f4[i] = 0;
     }
       
     return (first.closed[f1] + second.closed[f2] + third.closed[f3] + fourth.closed[f4]);
   }
};
