/*
 * MatrizA.cpp
 *
 *
 *    
 */

#include "MatrizA.h"
#include "Bloque.h"
#include <iostream>
#include "stdio.h"

/*--------------------------------------------------------------------------*/

MatrizA::MatrizA(int n){
	this->n = n;
	this->setDp();
	this->setDs();
}

/*--------------------------------------------------------------------------*/

MatrizA::~MatrizA(){
	//delete[] this->Dp;
	//delete[] this->Ds;
}

/*--------------------------------------------------------------------------*/


double MatrizA::get(int i, int j) {

	double resultado=0;
	int n = this->n;

    if ( (i>=0) and ( i<n*n ) and (j>=0) and ( j<n*n ) ){  /* Verifico que los indices sean validos */

        // Acá convierto los indices DE n^2 X n^2 a una de n X n  de (i,j) -> (col,fil)
        int fil,col;
        fil=i/n;
        col=j/n;

        switch (col-fil){ /* identifico en que diagonal tengo que buscar */

		case 0: //Módulo "T"
            resultado = this->Dp->get( i-(n)*fil , j-(n)*col );
			break;

		case  1: //Módulo "-I"
        case -1: //Módulo "-I"
			resultado = this->Ds->get( i-(n)*fil , j-(n)*col );
			break;

		default: //Módulo nulo, por ende el valor es un cero
			resultado = 0;
			break;
		}
    }
	return resultado;
}


/*--------------------------------------------------------------------*/

int MatrizA::dim(){
    return this->n;
}

/*--------------------------------------------------------------------*/

void MatrizA::setDp(){
    this->Dp = new Bloque(this->dim(),1);
}

/*--------------------------------------------------------------------*/

void MatrizA::setDs(){
	this->Ds = new Bloque(this->dim(),2);
}

