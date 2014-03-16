#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

unsigned int mask[8] = {15,240,3840,61440,983040,15728640,251658240,4026531840};

// arriba,abajo,izquierda,derecha
int posZero[16]={5, 7, 7, 6,
		 13,15,15,14,
		 13,15,15,14,
		 9,11,11,10};

inline int getpos(int i, int j)
{
    return ((i&mask[j])>>(j*4));
}
inline int setpos(int i, int j, int pos)
{
    return (i&(4294967295-mask[pos]))|(j<<4*pos);
}

class State
{

public:

    unsigned int half_up, half_down, zero;
    
    State(unsigned int up=19088743,
	  unsigned int down=2309737967,
	  unsigned int X=0):
	half_up(up),half_down(down),zero(X){};
    
    bool isGoal( State &goal);

    void getSucc();
    State move( int orig, int dest);
    State down();
    State up();
    State right();
    State left();
};

bool operator== (const State &left,const State &right)
{

    return (left.half_up==right.half_up)&&(left.half_down==right.half_down);
    
};
    
ostream& operator<<(ostream& out,const State dummy)
{

    for(int i=7;i>=4;i--){
	out << ((dummy.half_up&mask[i])>>(i*4)) <<"\t";
    };
    out<<"\n";
    for(int i=3;i>=0;i--){
	out << ((dummy.half_up&mask[i])>>(i*4)) <<"\t";
    };
    out<<"\n";
    for(int i=7;i>=4;i--){
	out << ((dummy.half_down&mask[i])>>(i*4)) <<"\t";
    };
    out<<"\n";
    for(int i=3;i>=0;i--){
	out << ((dummy.half_down&mask[i])>>(i*4)) <<"\t";
    };
    out<<"\n Zero: "<<dummy.zero<<"\n";

    return out;
    	    
};

// State State::move( int orig, int dest)
// {
//     State dummy(this->half_up,this->half_down,this->zero);
    
//     // this->half_up => this->half_down
//     if((orig<8)&&(dest>7)){
// 	dummy->half_up = setpos(dummy->half_up,getpos)
//     // this->half_down => this->half_up 
//     }else if((dest<8)&&(orig>7)){

//     // this->half_up	
//     }else if((dest<8)&&(orig<8)){
    
//     // this->half_down 
//     }else{
	
//     };
                    
// };


void State::getSucc()
{
    //derecha
    int dummy = posZero[this->zero];

    if( (dummy&1) ){
	State right(this->half_up, this->half_down, this->zero);
	right.right();
	cout<<right;
    };
    //izquierda
    if((dummy&2)>>1){
	State left(this->half_up, this->half_down, this->zero);
	left.left();
	cout<<left;
    };
    //abajo
    if((dummy&4)>>2){
	State down(this->half_up, this->half_down, this->zero);
	down.down();
	cout<<down;
    };
    //arriba
    if((dummy&8)>>3){
	State up(this->half_up, this->half_down, this->zero);
	up.up();
	cout<<up;
    };
    
    cout<<"\n\n";    
};

State State::down()
{
    int posicion = 7 - (this->zero);
    if(3 < (this->zero) && (this->zero)<8){
	this->half_up = setpos(this->half_up,
			       getpos(this->half_down,posicion+4),posicion);
	this->half_down = setpos(this->half_down,0,posicion+4);
	this->zero = (this->zero)+4;
    }else if((this->zero)<4){
	this->half_up = setpos(this->half_up,getpos(this->half_up,posicion-4),
			       posicion);
	this->half_up = setpos(this->half_up,0,posicion-4);
	this->zero = this->zero + 4;
    }else{
	posicion = 7 - (this->zero-8);
	this->half_down = setpos(this->half_down,
				 getpos(this->half_down,posicion-4),
				 posicion);
	this->half_down = setpos(this->half_down,0,posicion-4);
	this->zero = this->zero + 4;
    };
    
};

State State::up()
{
    int posicion = 7 - (this->zero-8);
    if(7 < (this->zero) && (this->zero)<12){
	this->half_down = setpos(this->half_down,
				 getpos(this->half_up,posicion-4),posicion);
	this->half_up = setpos(this->half_up,0,posicion-4);
	this->zero = (this->zero)-4;
    }else if(11<(this->zero)){
	this->half_down = setpos(this->half_down,
				 getpos(this->half_down,posicion+4),
				 posicion);
	this->half_down = setpos(this->half_down,0,posicion+4);
	this->zero = this->zero - 4;
    }else{
	posicion = 7 - (this->zero);
	this->half_up = setpos(this->half_up,getpos(this->half_up,posicion+4),
			       posicion);
	this->half_up = setpos(this->half_up,0,posicion+4);
	this->zero = this->zero - 4;
    };
};

State State::right()
{
    int posicion;
    if((this->zero)<8){
	posicion = 7 - (this->zero);
	this->half_up = setpos(this->half_up,
			       getpos(this->half_up,posicion-1),posicion);
	this->half_up = setpos(this->half_up,0,posicion-1);
	this->zero = (this->zero)+1;
    }else{
	posicion = 7 - (this->zero-8);
	this->half_down = setpos(this->half_down,
			       getpos(this->half_down,posicion-1),posicion);
	this->half_down = setpos(this->half_down,0,posicion-1);
	this->zero = (this->zero)+1;
    };        
};

State State::left()
{
    int posicion;
    if((this->zero)<8){
	posicion = 7 - (this->zero);
	this->half_up = setpos(this->half_up,
			       getpos(this->half_up,posicion+1),posicion);
	this->half_up = setpos(this->half_up,0,posicion+1);
	this->zero = (this->zero)-1;
    }else{
	posicion = 7 - (this->zero-8);
	this->half_down = setpos(this->half_down,
			       getpos(this->half_down,posicion+1),posicion);
	this->half_down = setpos(this->half_down,0,posicion+1);
	this->zero = (this->zero)-1;
    };        
};

int main( int argc, char *argv[] )
{
    int* dummy = new int[8];

    State goal;
    
    unsigned int derpA = 0;
    unsigned int derpB = 7;
    
    for(int i=7;i>=0;i--){
    	derpA = derpA << 4;
    	derpA += i;
    };
    for(int i=8;i<16;i++){
    	derpB = derpB << 4;
    	derpB += i;
    };
      
    State derp;
    State herp;
            
    cout<<herp<<"\n";

    herp.getSucc();

    herp.down();
    herp.getSucc();

    herp.right();
    herp.getSucc();

    cout<<"\n\t"<<(herp==derp)<<"\n";
}
