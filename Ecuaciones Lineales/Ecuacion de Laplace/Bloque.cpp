/*
 * Bloque.cpp
 *  
 */

#include "Bloque.h"
#include <iostream>
#include "stdio.h"

Bloque::Bloque(int n, int tipo){

        this->n = n;

		switch (tipo){ /* Identifico el tipo de bloque */

		case  1: // Bloque "T"
            this->setDp(4);
			this->setDs(-1);
        printf("Creado BOLQUE T con Dp:%f y Ds:%f\n",this->Dp,this->Ds);
			break;

        case  2: // Bloque "-I"
            this->setDp(-1);
			this->setDs(0);
		printf("Creado BOLQUE -I con Dp:%f y Ds:%f\n",this->Dp,this->Ds);
			break;

		default: // Si no se elije entre los valores "1" o "2", creo un bloque nulo
            this->setDp(0);
			this->setDs(0);
			break;
		}

}

/*--------------------------------------------------------------------*/

Bloque::~Bloque(){
    // ¿ Hace falta el " delete[] this->Dp "  ?
}

/*--------------------------------------------------------------------*/

double Bloque::get(int fil, int col){
    double resultado=0;
	int n = this->n;

    if ((fil<n) and (fil>=0) and (col<n) and (col>=0)){  /* Verifico que los índices sean válidos */

		switch (col-fil){ /* identifico en que diagonal tengo que buscar */

		case 0: //Debo buscar en la diagonal principal
			resultado = this->Dp;
			break;

		case  1: //Caso: diagonal secundaria superior
        case -1: //Caso: diagonal secundaria inferior
			resultado = this->Ds;
			break;

		default: //Caso: Es donde los valores de la matriz valen cero.
			resultado = 0;
			break;
		}
	}
    return resultado;
}

/*--------------------------------------------------------------------*/

int Bloque::dim(){
    return this->n;
}

/*--------------------------------------------------------------------*/

void Bloque::setDp(double valor){
    this->Dp=valor;
}

/*--------------------------------------------------------------------*/

void Bloque::setDs(double valor){
	this->Ds=valor;
}

