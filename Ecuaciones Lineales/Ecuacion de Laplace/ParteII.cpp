/*
 * ParteII.cpp
 *
 *    
 */

#include "MatrizA.h"
#include "SOR.h"
#include "Archivo.h"
#include "stdio.h"
#include <iostream>
#include "math.h"


int ParteII(int N, double RTOL, double w){

int NdeIteraciones;
	char cadena[50];
    int dim=N-1; // dim es la cantidad de incógnitas a resolver, la matriz A sera de dimensión dim*dim

	/* Generamos el archivo que enlista la cantidad de iteraciones en funcion de w */
	sprintf(cadena,"Parte_II_N%d.txt",N);
	Archivo archOmegaOptimo(cadena);

	/* creamos la matriz del apendice */
	MatrizA A(dim);

	cout << "\nMuestro la matriz A:\n" << endl;
	for ( int i=0; i<(dim*dim); i++){
            for ( int j=0; j<(dim*dim); j++){
                //cout << A.get(i,j) << " // ";
                printf(" %.2f |", A.get(i,j) );
            }
            cout << "\n" << endl;
    }

	/* obtenemos el vector de terminos independientes para la segunda parte */
    double* b = new double[dim*dim];
    int t1=89, t2=81, t3=88, t4=85;

    int B=0,C=dim-1,D=(dim*dim)-1-(dim-1),E=(dim*dim)-1; // B,C,D,E Son las 4 esquinas del cuadrilatero

    for (int i=0 ; i<(dim*dim) ; i++){
        printf("It(%d)",i);
        printf("fmod(i,dim):%d\n",(int)fmod(i,dim));
        printf("fmod(i-1,dim):%d\n",(int)fmod(i+1,dim));
        if ( (i>C) and (i<D) ){
            if ( (((int)fmod(i,dim))==0) ){
                b[i]=t1;
            }else if ( (((int)fmod(i+1,dim))==0) ){
                    b[i]=t3;
                    }else{
                        b[i]=0;
                    }
        }else if ( i<C ){
                b[i]=t2;
                }else if ( i>D ){
                    b[i]=t4;
                }

        if ( i==B ){
             b[i]=t1+t2;
        }
        if ( i==C ){
             b[i]=t2+t3;
        }
        if ( i==D ){
             b[i]=t1+t4;
        }
        if ( i==E ){
             b[i]=t3+t4;
        }
	}

    cout << "\nMuestro el vector b:\n" << endl;
	for ( int i=0; i<(dim*dim); i++){
        printf("(%f)",b[i]);
    }


	/* creamos el vector solucion */
    double* x = new double[dim*dim];

    /* Cargamos la semilla X^0 con el vector nulo */
    for (int i=0 ; i<dim*dim ; i++)	x[i] =0;

	/* escribimos el archivo OmegaOptimo */
	sprintf(cadena, "Con N=%d, obtengo una matriz A de dimension %dX%d y un vector de dimension %d\n",N,dim,dim,dim);
	archOmegaOptimo.imprimir(cadena);
	x = SOR(A, b, w, NdeIteraciones,RTOL,2);
	archOmegaOptimo.imprimir("--------------------\n");
    archOmegaOptimo.imprimir("Vector x = [ ");
	for ( int i=0 ; i<dim*dim ; i++ ){
        sprintf(cadena," %f, ", x[i] );
        archOmegaOptimo.imprimir(cadena);
    }
	sprintf(cadena,"] \tw=%.2f\tCantidad de iteraciones:%d\n", w, NdeIteraciones);
	archOmegaOptimo.imprimir(cadena);
	delete[] x;
	/*-------------------------------------*/

	return 0;

}
