#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;


template<class T> class PatternGenerator
{
public:
    unordered_map<long long int, int> closed;
    
    void generate(){
	int cost = 0;
	vector<int> pattern;
	int temp;
	for(int i = 0; i<16; ++i){
	    scanf("%d",&temp);
	    pattern.push_back(temp);
	    printf("%d ",pattern[i]);
	}

	T smallPattern(pattern);
	
	closed[smallPattern.zip()] = cost;
	printf("%d",cost);
	++cost;
	printf("\n");


	//Ciclo general de procesamiento de patron
	vector<T> l;
	l.push_back(smallPattern);

	while(!l.empty()){

	    vector<T> ltemp;
	    for(int k = 0; k < l.size(); ++k){

		vector<T> succ = l[k].getSucc();

		for(int i = 0; i<succ.size();++i){

		    if(!closed.count(succ[i].zip())){
			closed[succ[i].zip()] = cost;

			ltemp.push_back(succ[i]);

			cout << succ[i]<<"\n";
			
			printf("%d\n",cost);
		    }
		}
	    }
	    ++cost;
	    l = ltemp;
	}
	

    }
    
};

    
