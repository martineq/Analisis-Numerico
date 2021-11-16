/*
 * ItSEL.cpp
 *
 *  Created on: 17-abr-2009
 *       
 */
#include "TBMatrix.h"
#include "ItSel.h"
#include "math.h"
#include "archivo.h"
#include <string>
#include <iostream>
#include "stdio.h"
using namespace std;

/*------------------------------------------------------------------------------*/
void mostrarMatriz(const TBMatrix & matriz){
	int i,j;
	int n = matriz.dim();
	for(i=0;i<n;i++){
		for (j=0;j<n;j++){
			cout << matriz.get(i,j) << " ";
		}
		cout << '\n';
	}
}

/*-----------------------------------------------------------------------------*/

int criterioConvergencia( double actual[] , double anterior[] , int n , double tol, double & R){
    int i;
    double numerador = 0.00;
    double denominador = 0.00;
    for ( i=0 ; i<n ; i++ ){
        if ( fabs(actual[i]-anterior[i]) > numerador )
            numerador = fabs(actual[i]-anterior[i]) ;
        if ( fabs(actual[i]) > denominador )
            denominador = fabs(actual[i]);
    }
    if ( denominador==0.00 ) return 1;    /* División por cero  */
    else{
		R = numerador /denominador;
		if ( R <= tol ) return 1;
		else return 0;
    }

}

/*-----------------------------------------------------------------------------*/

int imprimirVector( double vec[] , int longitud){
    int i;
    for ( i=0 ; i<longitud ; i++ ){
        cout << vec[i] << " ";
    }
    return 0;
}
/*-----------------------------------------------------------------------------*/

int copiarVector( double destino[] , double origen[] , int longitud ){
    int i;
    for ( i=0 ; i<longitud ; i++ ){
        destino[i] = origen[i];
    }
    return 0;
}

/*-----------------------------------------------------------------------------*/


double* multiplicarMatrizPorVector(const TBMatrix & A, double* x){
	int i, j;
	int n = A.dim();
	double sum;
	double* b = new double[n];

	for (i=0 ; i<n ; i++){
		sum = 0;
		for(j=0 ; j<n ; j++){
			sum += A.get(i,j) * x[j];
		}
		b[i] = sum;
	}
	return b;
}

/*--------------------------------------------------------------------------------------------*/

double* jacobi(const TBMatrix & A, double* b){

	int k = 1;              /* Número de iteración */
	int i,j;                /* subindices para filas y columnas */
	double sum = 0;  		/* variable auxiliar para la sumatoria */
	int converge = 0;      	/* me indica el criterio de corte, inicialmente en Falso==0 */
	double rActual, rAnterior, radioEspectral; /* los valores de R^k , R^k-1 y radio espectral*/

	int n = A.dim();

	/* Creamos el archivo donde guardar los datos */
	char nombreArchivo[20];
	sprintf(nombreArchivo,"Jacobi%d.txt",n);
	Archivo archivo(nombreArchivo);
	/*--------------------------------------------*/

    double* xkm = new double[n]; //xkm: x^k+1
    double* xk = new double[n];  //xk: x^k

    /* En la primer iteración xkm y xk seran el nulo */
    for (i=0 ; i<n ; i++){
    	xkm[i] = 0;
    	xk[i] = 0;
    }

    /* Preparamos el encabezado de la tabla en el archivo */
    archivo.imprimir("b = ");
    char cadena[15];
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"%f\t", b[i]);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n\n");
    archivo.imprimir("k\tR^k\t\tRadio Espectral\t");
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"x[%d]\t\t",i+1);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n");

    /*----------------------------------------------------*/

    //cout << "Comienzo Jacobi" << '\n';

    while (!converge){

    	/* separamos los casos anticipandonos a lo que sería el metodo de GS */

    	for ( i=0 ; i<n ; i++ ){
    		sum = 0;
    		for (j=(i<3)?(0):(i-3) ; j<i ; j++ ){ /* suma de los elementos a la izq de la diagonal */
            	if (  ( j==i-1 ) || ( j==i-3 ) ){  /* Condición para las matrices tridiagonales. Para cualquier matriz la condicion es " j!=i " */
                	sum += ((A.get(i,j)) * (xk[j]));        /* Hago la sumatoria */
            	}
        	}
    		for (j=i+1 ; j<((i<n-3)?(i+4):(n)) ; j++){ /* suma de los elementos a la derecha de la diagonal */
    			if (( j==i+1 ) || ( j==i+3 )){
    				sum += ((A.get(i,j)) * (xk[j]));
    			}
    		}
        	xkm[i] = ( b[i] - sum ) / A.get(i,i);
    	}

    	converge = criterioConvergencia(xkm, xk, n, RTOL, rActual);
    	if ((k>1) and (rAnterior != 0)){
			radioEspectral = rActual / rAnterior;
    	}else{
    		radioEspectral = 0;
    	}
    	/* Grabamos los datos de esta iteracion en el archivo */
    	char cadena[20];
    	sprintf(cadena,"%d\t%f\t%f\t", k, rActual, radioEspectral);
    	archivo.imprimir(cadena);
    	for (i=0 ; i<n ; i++){
    		sprintf(cadena,"%f\t", xkm[i]);
    		archivo.imprimir(cadena);
    	}
    	archivo.imprimir("\n");

    	/*----------------------------------------------------*/

    	rAnterior = rActual;

    	copiarVector (xk,xkm,n);
    	k++;
    }

    cout << "Jacobi" << endl;
    imprimirVector(xkm,n);
    //cout << "Fin Jacobi" << '\n';
    cout << "k = " << k << endl;
    cout << "radio espectral: " << radioEspectral << endl;
    delete[] xk;


    return xkm;
}

/*--------------------------------------------------------------------------------------------*/

double* gaussSeidel(const TBMatrix & A, double* b){

	int k = 1;              /* Número de iteración */
	int i,j;                /* subindices para filas y columnas */
	double sum = 0;  		/* variable auxiliar para la sumatoria */
	int converge = 0;     	/* me indica el criterio de corte, inicialmente en Falso==0 */
	double rActual, rAnterior, radioEspectral; /* los valores de R^k , R^k-1 y radio espectral*/

	int n = A.dim();

	/* Creamos el archivo donde guardar los datos */
	char nombreArchivo[20];
	sprintf(nombreArchivo,"Gauss Seidel%d.txt",n);
	Archivo archivo(nombreArchivo);
	/*--------------------------------------------*/

    double* xkm = new double[n]; //xkm: x^k+1
    double* xk = new double[n];  //xk: x^k

    /* En la primer iteración xkm y xk seran el nulo */
    for (i=0 ; i<n ; i++){
    	xkm[i] = 0;
    	xk[i] = 0;
    }

    /* Preparamos el encabezado de la tabla en el archivo */
    archivo.imprimir("b = ");
    char cadena[15];
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"%f\t", b[i]);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n\n");
    archivo.imprimir("k\tR^k\t\tRadio Espectral\t");
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"x[%d]\t\t",i+1);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n");

    /*----------------------------------------------------*/

    //cout << "Comienzo Gauss Seidel" << '\n';

    while (!converge){

    	for ( i=0 ; i<n ; i++ ){
    		sum = 0;
    		for (j=(i<3)?(0):(i-3) ; j<i ; j++ ){ /* suma de los elementos a la izq de la diagonal */
            	if (  ( j==i-1 ) || ( j==i-3 ) ){  /* Condición para las matrices tridiagonales. Para cualquier matriz la condicion es " j!=i " */
                	sum += ((A.get(i,j)) * (xkm[j]));        /* Hago la sumatoria */
            	}
        	}
    		for (j=i+1 ; j<((i<n-3)?(i+4):(n)) ; j++){ /* suma de los elementos a la derecha de la diagonal */
    			if (( j==i+1 ) || ( j==i+3 )){
    				sum += ((A.get(i,j)) * (xk[j]));
    			}
    		}
        	xkm[i] = ( b[i] - sum ) / A.get(i,i);
    	}


    	converge = criterioConvergencia(xkm, xk, n, RTOL, rActual);
    	if ((k>1) and (rAnterior != 0)){
    		radioEspectral = rActual / rAnterior;
    	}else{
    		radioEspectral = 0;
    	}

    	/* Grabamos los datos de esta iteracion en el archivo */
    	char cadena[20];
    	sprintf(cadena,"%d\t%f\t%f\t", k, rActual, radioEspectral);
    	archivo.imprimir(cadena);
    	for (i=0 ; i<n ; i++){
    		sprintf(cadena,"%f\t", xkm[i]);
    		archivo.imprimir(cadena);
    	}
    	archivo.imprimir("\n");

    	/*----------------------------------------------------*/

    	rAnterior = rActual;
    	copiarVector (xk,xkm,n);
    	k++;
    }

    cout << "Gauss Seidel" << endl;
    imprimirVector(xkm,n);
    //cout << "Fin Gauss Seidel" << '\n';
    cout << "k = " << k << endl;
    cout << "radio espectral: " << radioEspectral << endl;
    delete[] xk;


    return xkm;
}

/*--------------------------------------------------------------------------------------------*/

double* SOR(const TBMatrix & A, double* b, double w, int & k){

	k = 1;              /* Número de iteración */
	int i,j;                /* subindices para filas y columnas */
	double sum = 0;  		/* variable auxiliar para la sumatoria */
	int converge = 0;      	/* me indica el criterio de corte, inicialmente en Falso==0 */
	double rActual, rAnterior, radioEspectral; /* los valores de R^k , R^k-1 y radio espectral*/

	int n = A.dim();

	/* Creamos el archivo donde guardar los datos */
	char nombreArchivo[20];
	sprintf(nombreArchivo,"SOR%d.txt",n);
	Archivo archivo(nombreArchivo);
	/*--------------------------------------------*/

    double* xkm = new double[n]; //xkm: x^k+1
    double* xk = new double[n];  //xk: x^k

    /* En la primer iteración xkm y xk seran el nulo */
    for (i=0 ; i<n ; i++){
    	xkm[i] = 0;
    	xk[i] = 0;
    }

    /* Preparamos el encabezado de la tabla en el archivo */
    archivo.imprimir("b = ");
    char cadena[15];
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"%f\t", b[i]);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n\n");
    archivo.imprimir("k\tR^k\t\tRadio Espectral\t");
    for (i=0 ; i<n ; i++){
    	sprintf(cadena,"x[%d]\t\t",i+1);
    	archivo.imprimir(cadena);
    }
    archivo.imprimir("\n");

    /*----------------------------------------------------*/

    //cout << "Comienzo SOR" << '\n';

    while (!converge){

    	for ( i=0 ; i<n ; i++ ){
    		sum = 0;
    		for (j=(i<3)?(0):(i-3) ; j<i ; j++ ){ /* suma de los elementos a la izq de la diagonal */
            	if (  ( j==i-1 ) || ( j==i-3 ) ){  /* Condición para las matrices tridiagonales. Para cualquier matriz la condicion es " j!=i " */
                	sum += ((A.get(i,j)) * (xkm[j]));        /* Hago la sumatoria */
            	}
        	}
    		for (j=i+1 ; j<((i<n-3)?(i+4):(n)) ; j++){ /* suma de los elementos a la derecha de la diagonal */
    			if (( j==i+1 ) || ( j==i+3 )){
    				sum += ((A.get(i,j)) * (xk[j]));
    			}
    		}
        	xkm[i] = ( b[i] - sum ) / A.get(i,i);

        	/* aplico el w */
        	xkm[i] = ((xkm[i] - xk[i]) * w) + xk[i];
    	}

    	converge = criterioConvergencia(xkm, xk, n, RTOL, rActual);
    	if ((k>1) and (rAnterior != 0)){
    		radioEspectral = rActual / rAnterior;
    	}else{
    		radioEspectral = 0;
    	}

    	/* Grabamos los datos de esta iteracion en el archivo */
    	char cadena[20];
    	sprintf(cadena,"%d\t%f\t%f\t", k, rActual, radioEspectral);
    	archivo.imprimir(cadena);
    	for (i=0 ; i<n ; i++){
    		sprintf(cadena,"%f\t", xkm[i]);
    		archivo.imprimir(cadena);
    	}
    	archivo.imprimir("\n");

    	/*----------------------------------------------------*/

    	rAnterior = rActual;
    	copiarVector (xk,xkm,n);
    	k++;
    }

    cout << "SOR" << endl;
    imprimirVector(xkm,n);
    //cout << "Fin SOR" << '\n';
    cout << "k = " << k << endl;
    cout << "radio espectral: " << radioEspectral << endl;
    delete[] xk;

    k = k-1;
    return xkm;
}


