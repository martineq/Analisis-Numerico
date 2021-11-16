/*
 * MatrizBloque.cpp
 *
 *
 *    
 */

#include "MatrizBloque.h"


/*--------------------------------------------------------------------------*/

MatrizBloque::MatrizBloque(int n){
	this->n = n;
	this->setDp();
	this->setDs();
}

/*--------------------------------------------------------------------------*/

MatrizBloque::~MatrizBloque(){
	delete[] this->Dp;
	delete[] this->Ds;
}

/*--------------------------------------------------------------------------*/


double MatrizBloque::get(int i, int j) const{

	double resultado=0;
	int n = this->n;

    if (( i<(n-1)^2 ) and (i>=0) and ( j<(n-1)^2 ) and (j>=0)){  /* Verifico que los indices sean validos */

        // AC� CONVIERTO los indices DE n^2 X n^2 a una de n X n  de (i,j) -> (col,fil)

        int fil,col;
        fil=entero(i/(n-1));
        col=entero(j/(n-1));

        switch (col-fil){ /* identifico en que diagonal tengo que buscar */

		case 0: //M�dulo "T"
			resultado = this->Dp->get( i-(n-1)*fil , j-(n-1)*col );
			break;

		case  1: //M�dulo "-I"
        case -1: //M�dulo "-I"
			resultado = this->Ds->get( i-(n-1)*fil , j-(n-1)*col );
			break;

		default: //M�dulo nulo, por ende el valor es un cero
			resultado = 0;
			break;
		}
    }
	return resultado;
}


/*--------------------------------------------------------------------*/

int Bloque::dim() const{
    return this->n;
}

/*--------------------------------------------------------------------*/

void Bloque::setDp(){
    this->Dp = new Bloque(this->dim,1)
}

/*--------------------------------------------------------------------*/

void Bloque::setDs(){
	this->Dp = new Bloque(this->dim,2)
}

