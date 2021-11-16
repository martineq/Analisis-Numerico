/*
 * TBMatrix.cpp
 *
 *  Created on: 16-abr-2009
 *       
 */

#include "TBMatrix.h"


/*--------------------------------------------------------------------------*/

TBMatrix::TBMatrix(int n){

	this->n = n;
	this->setD1();
	this->setD2();
	this->setD3();
}

/*--------------------------------------------------------------------------*/

TBMatrix::TBMatrix(double* d1, double* d2, double* d3, int n){

	this->n = n;
	this->setD1(d1);
	this->setD2(d2);
	this->setD3(d3);
}

/*--------------------------------------------------------------------------*/

TBMatrix::~TBMatrix(){
	delete[] this->d1;
	delete[] this->d2;
	delete[] this->d3;
}

/*--------------------------------------------------------------------------*/

double TBMatrix::get(int fil, int col) const{

	double resultado = 0;
	int n = this->n;

	/* verifico que los indices sean validos */

	if ((fil<n) and (fil>=0) and (col<n) and (col>=0)){

		/* identifico en que diagonal tengo que buscar */

		switch (col-fil){

		case 0: //debo buscar en d1

			/* en este caso el numero de fila o de columna coincide con
			 * la posicione en la diagonal
			 */
			resultado = this->d1[fil];
			break;

		case 1: // debo buscar en d2 pensando en la parte superior

			/* en este caso el numero de fila corresponde con la posicion
			 * en la diagonal
			 */
			resultado = this->d2[fil];
			break;


		case -1: //debo buscar en d2 pensando en la parte inferior

			/* en este caso el numero de columna corresponde con la posicion
			 * en la diagonal
			 */
			resultado = this->d2[col];
			break;

		case 3: //debo buscar en d3 pensando en la parte superior

			/* en este caso el numero de fila corresponde con la posicion
			 * en la diagonal
			 */
			resultado = this->d3[fil];
			break;

		case -3: //debo buscar en d3 pensando en la parte inferior

			/* en este caso el numero de columna corresponde con la posicion
			 * en la diagonal
			 */
			resultado = this->d3[col];
			break;

		default: /*debo devolver un 0 porque el indice no corresponde
			      * a ninguna diagonal no nula */
			resultado = 0;
			break;

		}

	}
	return resultado;
}

/*--------------------------------------------------------------------------*/

int TBMatrix::dim() const{
	return this->n;
}

/*--------------------------------------------------------------------------*/

void TBMatrix::setD1(){
	int i;
	int n = this->n;

	this->d1 = new double[n];

	/* completo la diagonal hasta donde termina B1 */
	for (i = 0; (i<3) and (i<n); i++ ){
		this->d1[i]=2;
	}
	/* completo la diagonal hasta donde empieza B3 */
	for (i = 3; (i<n-3); i++ ){
		this->d1[i]=4;
	}
	/* completo la diagonal segun B3 en la parte que queda */
	for (i = n-3; i<n; i++ ){
		this->d1[i]=3;
	}

}

/*---------------------------------------------------------------------------*/

void TBMatrix::setD2(){
	int i;
	int n = this->n;

	this->d2 = new double[n-1];

	/* completo la diagonal hasta donde termina B1 */
	for (i = 0; (i<2) and (i<n-1); i++ ){
		this->d2[i]= -0.5;
	}
	/* completo la diagonal hasta donde empieza B3 */
	for (i = 3; (i<n-4); i++ ){
		this->d2[i]= -1;
	}
	/* completo la diagonal segun B3 en la parte que queda */
	for (i = n-3; i<n-1; i++ ){
		this->d2[i]= -0.5;
	}

	/* agrego los 0 que me estan faltando en la diagonal */
	for (i = 2; i<n-1;i= i + 3){
		this->d2[i]=0;
	}

}

/*---------------------------------------------------------------------------*/

void TBMatrix::setD3(){
	int i;
	int n = this->n;

	this->d3 = new double[n-3];

	/* Esta es facil porque son todos -1 */

	for (i=0 ; i<n-3 ; i++){
		this->d3[i]=-1;
	}

}

/*---------------------------------------------------------------------------*/

void TBMatrix::setD1(double* diag){
	int i;
	int n = this->n;

	this->d1 = new double[n];

	/* copio los elementos de la diagonal pasada por parametro a la propia de
	 * la instancia
	 */
	for (i=0 ; i<n ; i++){
		this->d1[i] = diag[i];
	}
}

/*---------------------------------------------------------------------------*/

void TBMatrix::setD2(double* diag){
	int i;
	int n = this->n;

	this->d2 = new double[n-1];

	/* copio los elementos de la diagonal pasada por parametro a la propia de
	 * la instancia
	 */
	for (i=0 ; i<n-1 ; i++){
		this->d2[i] = diag[i];
	}
}

/*--------------------------------------------------------------------------*/

void TBMatrix::setD3(double* diag){
	int i;
	int n = this->n;

	this->d3 = new double[n];

	/* copio los elementos de la diagonal pasada por parametro a la propia de
	 * la instancia
	 */
	for (i=0 ; i<n-3 ; i++){
		this->d3[i] = diag[i];
	}
}
