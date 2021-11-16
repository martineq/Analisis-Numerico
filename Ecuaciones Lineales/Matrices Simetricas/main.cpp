/*
 * main.cpp
 *
 *  Created on: 16-abr-2009
 *       
 */

#include "TBMatrix.h"
#include "ItSel.h"
#include "Archivo.h"
#include "stdio.h"
#include <iostream>
using namespace std;


/*---------------------------------------------------------*/

int main(){
	int kSOR;
	char cadena[10];

	/* creamos un vector con los valores de w optimo para cada tamaño de matriz */
	float wOptimo[4] = {1.18, 1.25, 1.28, 1.31};

	/* Generamos el archivo que enlista la cantidad de iteraciones en funcion de w */
	Archivo archOmegaOptimo("OmegaOptimo.txt");
	archOmegaOptimo.imprimir("w\tk\n");

	for (int dim=6 ; dim<13 ; dim += 3){

		/* creamos el vector solucion */
		double* x = new double[dim];

		/* lo cargamos con 1 */
		for (int i=0 ; i<dim ; i++){
			x[i] = 1;
		}

		/* creamos la matriz del apendice */
		TBMatrix A(dim);

		/* obtenemos el vector de terminos independientes */
		double* b = multiplicarMatrizPorVector(A, x);

		/* resolvemos el sistema con los distintos metodos */
		delete[] x;
		x = jacobi(A, b);
		delete[] x;
		x = gaussSeidel(A, b);
		delete[] x;

		/* escribimos el archivo OmegaOptimo */
		sprintf(cadena, "A%d\n", dim);
		archOmegaOptimo.imprimir(cadena);
		for (double w=1 ; w<2 ; w += 0.05){
			x = SOR(A, b, w, kSOR);
			sprintf(cadena,"%f\t%d\n", w, kSOR);
			archOmegaOptimo.imprimir(cadena);
			delete[] x;
		}
		/*-------------------------------------*/

		/* finalmente pisamos el archivo correspondiente de SORn.txt con el valor de w optimo */
		x = SOR(A, b, wOptimo[(dim/3)-2], kSOR);
		delete[] x;
		delete[] b;
		/*-------------------------------------------------*/
	}

	/* creamos el vector solucion */
	double* x = new double[30];

	/* lo cargamos con 1 */
	for (int i=0 ; i<30 ; i++){
		x[i] = 1;
	}

	/* creamos la matriz del apendice */
	TBMatrix A(30);

	/* obtenemos el vector de terminos independientes */
	double* b = multiplicarMatrizPorVector(A, x);

	/* resolvemos el sistema con los distintos metodos */

	delete[] x;
	x = jacobi(A, b);
	delete[] x;
	x = gaussSeidel(A, b);
	delete[] x;

	archOmegaOptimo.imprimir("A30\n");
	for (double w=1 ; w<2 ; w += 0.05){
		x = SOR(A, b, w, kSOR);
		char cadena[10];
		sprintf(cadena,"%f\t%d\n", w, kSOR);
		archOmegaOptimo.imprimir(cadena);
		delete[] x;
	}

	/* finalmente pisamos el archivo correspondiente de SORn.txt con el valor de w optimo */
	x = SOR(A, b, wOptimo[3], kSOR);
	delete[] x;
	delete[] b;

	return 0;
}
