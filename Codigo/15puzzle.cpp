/** Class 15pluzzle
* Clase que implementa los estados del problema 15puzzle
* @param half_up: Entero que representa la parte de arriba del tablero
* @param half_down: Entero que representa la parte de abajo del tablero
* @param zero: Posicion del 0 en este momento
**/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>

using namespace std;

// Mascaras que se usan para filtar las casillas del tablero en la representacion
// Se usan 4 bits para representar una casilla del tablero
unsigned int mask[8] = {15,240,3840,61440,983040,15728640,251658240,4026531840};

// Representacion de que posiciones son posibles dependiendo de la posicion del 0
// Cada bit representa respectivamente:
// arriba,abajo,izquierda,derecha
int posZero[16]={5, 7, 7, 6,
		 13,15,15,14,
		 13,15,15,14,
		 9,11,11,10};

// Funcion que ayuda a optener el valor de alguna casilla del tablero
inline int getpos(int i, int j)
{
    return ((i&mask[j])>>(j*4));
}
// Funcion que ayuda a guardar un valor en alguna casilla del tablero
inline int setpos(int i, int j, int pos)
{
    return (i&(4294967295-mask[pos]))|(j<<4*pos);
}

class State
{

public:

    unsigned int half_up, half_down, zero;
    
    /**
     * Constructor de State
     * El default es la representacion:
     * 0  1  2  3
     * 4  5  6  7
     * 8  9  10 11
     * 12 13 14 15
     * @param up: la mitad de arriba
     * @param down: la mitad de abajo
     * @param X: posicion del zero
     * @return State construido
     **/
    State(unsigned int up=19088743,
	  unsigned int down=2309737967,
	  unsigned int X=0):
	half_up(up),half_down(down),zero(X){};
    
    bool isGoal( State &goal);
    vector<State> getSucc();

    //////////////////////////////
    // pendiente	        //
    // int actionCost(){        //
    // 	return 1;	        //
    // }		        //
    //////////////////////////////
    
private:

    State down();
    State up();
    State right();
    State left();

};

// Reescritura del operador == para la clase State
bool operator== (const State &left,const State &right)
{

    return (left.half_up==right.half_up)&&(left.half_down==right.half_down);
    
};
    
// Reescritura del operador << para la clase State
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

/**
 * Calcula todos los posibles estados a los que se le pueden llegar haciendo
 * movimientos validos
 * @return vector con los estados 
 **/
vector<State> State::getSucc()
{
    vector<State> out;
    int dummy = posZero[this->zero];

    //derecha
    if( (dummy&1) ){
	State right(this->half_up, this->half_down, this->zero);
	right.right();
	out.push_back(right);
	//cout<<right;
    };
    //izquierda
    if((dummy&2)>>1){
	State left(this->half_up, this->half_down, this->zero);
	left.left();
	out.push_back(left);
	//cout<<left;
    };
    //abajo
    if((dummy&4)>>2){
	State down(this->half_up, this->half_down, this->zero);
	down.down();
	out.push_back(down);
	//cout<<down;
    };
    //arriba
    if((dummy&8)>>3){
	State up(this->half_up, this->half_down, this->zero);
	up.up();
	out.push_back(up);
	//cout<<up;
    };
    
    cout<<"\n\n";    
    
    return out;
};

// Accion de mover el 0 hacia abajo en el estado
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

// Accion de mover el 0 hacia arriba en el estado
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

// Accion de mover el 0 hacia la derecha en el estado
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

// Accion de mover el 0 hacia la izquierda en el estado
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

// main de prueba
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

    vector<State> laSalida = herp.getSucc();

    for(vector<State>::iterator yomama=laSalida.begin();yomama!=laSalida.end();++yomama){
	cout<<*yomama;
    };
    
    cout<<"\n\t"<<(herp==derp)<<"\n";
}
