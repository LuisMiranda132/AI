#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

unsigned int mask[8] = {15,240,3840,61440,983040,15728640,251658240,4026531840};

class State
{

public:

    // se guardan 2 numeros por INT
    int square[8];
    
    State(int* squareInt){
	copy(squareInt,squareInt+8,this->square);
    };
    
    bool isGoal( State &goal);

    void whereSpace(int *pos, bool *front);
    bool legalMove(int *posblank, bool *front);
        
};

bool operator== (const State &left,const State &right)
{
    for(int i=0;i<8;i++){
	if(left.square[i]!=right.square[i]){
	    return false;
	};
    };
    return true;
};
    
ostream& operator<<(ostream& out,const State dummy)
{
    out << "\n";
    for(int i=0;i<8;i++){
	if(i&1){
	    out << ((240&dummy.square[i])>>4) << "\t"<< (15&dummy.square[i]) << "\n";
	}else{
	    out << ((240&dummy.square[i])>>4) << "\t"<< (15&dummy.square[i]) << "\t";
	};
		
    };
    out << "\n";
    return out;
	    
};

void State::whereSpace(int *pos, bool *front){
    
    for(int i=0;i<8;i++){
	if(!(this->square[i]&240)){
	    *pos = i;
	    *front = 1;
	}else if(!(this->square[i]&15)){
	    *pos = i;
	    *front = 0;
	};
    }
    
};

bool State::isGoal( State &goal){

    return (this == &goal);
};

int main( int argc, char *argv[] )
{
    int* dummy = new int[8];

    unsigned int derpA = 0;
    unsigned int derpB = 7;
    
    for(int i=1;i<8;i++){
    	derpA = derpA << 4;
    	derpA += i;
    };
    for(int i=8;i<16;i++){
    	derpB = derpB << 4;
    	derpB += i;
    };
            	    
    cout<<"\n";
    
    for(int i=7;i>=4;i--){
	cout << ((derpA&mask[i])>>(i*4)) <<"\t";
    };
    cout<<"\n";
    for(int i=3;i>=0;i--){
	cout << ((derpA&mask[i])>>(i*4)) <<"\t";
    };
    cout<<"\n";
    for(int i=7;i>=4;i--){
	cout << ((derpB&mask[i])>>(i*4)) <<"\t";
    };
    cout<<"\n";
    for(int i=3;i>=0;i--){
	cout << ((derpB&mask[i])>>(i*4)) <<"\t";
    };
    cout<<"\n";

    cout << derpA <<"\t"<< derpB;
    
    
    dummy[0]=11<<4;
    dummy[0]+=1;
    dummy[1]=2<<4;
    dummy[1]+=3;
    dummy[2]=4<<4;
    dummy[2]+=5;
    dummy[3]=6<<4;
    dummy[3]+=7;
    dummy[4]=8<<4;
    dummy[4]+=9;
    dummy[5]=10<<4;
    dummy[5]+=0;
    dummy[6]=12<<4;
    dummy[6]+=13;
    dummy[7]=14<<4;
    dummy[7]+=15;

    // dummy[0]=15;
    // cout << dummy[0] << "\t";
    // dummy[0]=dummy[0]<<4;
    // cout << dummy[0] << "\n";

    // dummy[0]=dummy[0]+2;
    // cout << dummy[0] << "\t";
    // int wut = 15&dummy[0];
    // cout << wut << "\t";
    // wut = (240&dummy[0])>>4;
    // cout << wut << "\n";
    
    State prueba(dummy);

    State goal(dummy);

    // cout << prueba ;
    
    int pos;
    bool front;
    
    prueba.whereSpace(&pos, &front);
    
    // cout << "\npos: " << pos<<"\tfront: "<<front;

    cout << "\n";

    cout << prueba;
    
}
