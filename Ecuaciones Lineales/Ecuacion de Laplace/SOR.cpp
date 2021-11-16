/*
 * ItSEL.cpp
 *
 *
 *    
 */

#include "MatrizA.h"
#include "SOR.h"
#include "math.h"
#include "Archivo.h"
#include <string>
#include <iostream>
#include "stdio.h"



double* SOR( MatrizA & A, double* b, double w, int & k, double RTOL, int parte){

	k = 1;              /* Número de iteración */
	int i,j;                /* subindices para filas y columnas */
	double sum = 0;  		/* variable auxiliar para la sumatoria */
	int converge = 0;      	/* me indica el criterio de corte, inicialmente en Falso==0 */
	double rActual, rAnterior, radioEspectral; /* los valores de R^k , R^k-1 y radio espectral*/

	int n = (A.dim()) * (A.dim()) ;
	/* Creamos el archivo donde guardar los datos */
	char nombreArchivo[20];

	sprintf(nombreArchivo,"SOR_pI_N%d_w%.2f.txt",A.dim()+1,w);
	if ( parte==2 ){ sprintf(nombreArchivo,"SOR_pII_N%d_w%.2f.txt",A.dim()+1,w); }// Para diferenciar los archivos ParteI de los ParteII
	Archivo archivo(nombreArchivo);

	sprintf(nombreArchivo,"RADIO_pI_N%d_w%.2f.txt",A.dim()+1,w);
	if ( parte==2 ){ sprintf(nombreArchivo,"RADIO_pII_N%d_w%.2f.txt",A.dim()+1,w); }// Para diferenciar los archivos ParteI de los ParteII
	Archivo archivoB(nombreArchivo);

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
        int d=A.dim(); // Lo voy a usar para saber la distancia "d" de separación entre la diagonal principal y la diag de -I
    	for ( i=0 ; i<n ; i++ ){
    		sum = 0;
    		for (j=(i<d)?(0):(i-d) ; j<i ; j++ ){ /* suma de los elementos a la izq de la diagonal */
            	if (  ( j==i-1 ) || ( j==i-d ) ){  /* Condición para las matrices tridiagonales. Para cualquier matriz la condicion es " j!=i " */
                	sum += ((A.get(i,j)) * (xkm[j]));        /* Hago la sumatoria */
            	}
        	}

    		for (j=i+1 ; j<( (i<n-d)?(i+d+1):(n) ) ; j++){ /* suma de los elementos a la derecha de la diagonal */
    			if (( j==i+1 ) || ( j==i+d )){
    				sum += ((A.get(i,j)) * (xk[j]));
    			}
    		}

        	xkm[i] = ( b[i] - sum ) / A.get(i,i);

        	/* aplico el w */
        	xkm[i] = ((xkm[i] - xk[i]) * w) + xk[i];
    	}

    	converge = criterioConvergencia(xkm, xk, n, RTOL , rActual);
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

       /* Grabamos los datos de esta iteracion en el archivo RADIO */
    	sprintf(cadena,"%d\t%f\t%f\t", k, rActual, radioEspectral);
    	archivoB.imprimir(cadena);
    	archivoB.imprimir("\n");




    	/*----------------------------------------------------*/

    	rAnterior = rActual;
    	copiarVector (xk,xkm,n);
    	k++;
    }

    cout << "SOR" << endl;
    imprimirVector(xkm,n);
    cout << "Fin SOR" << '\n';
    cout << "k = " << k << endl;
    cout << "radio espectral: " << radioEspectral << endl;
    delete[] xk;

    k = k-1;
    return xkm;
}

/*-----------------------------------------------------------------------------*/

void mostrarMatriz( MatrizA & matriz){
	int i,j;
	int n = (matriz.dim()) * (matriz.dim());
	for(i=0;i<n;i++){
		for (j=0;j<n;j++){
			cout << matriz.get(i,j) << " ";
		}
		cout << '\n';
	}
}

/*-----------------------------------------------------------------------------*/

int criterioConvergencia( double actual[] , double anterior[] , int n , double tol, double & R){

    double numerador = 0.00;
    double denominador = 0.00;
    double SUMnumerador = 0.00;
    double SUMdenominador = 0.00;

    for ( int i=0 ; i<n ; i++ ){
        SUMnumerador += (actual[i]-anterior[i])*(actual[i]-anterior[i]);
        SUMdenominador += (actual[i])*(actual[i]);
    }

    numerador=sqrt(SUMnumerador);
    denominador=sqrt(SUMdenominador);

    if ( denominador==0.00 ) return 1;    /* División por cero  */
    else{
		R = numerador /denominador;
		if ( R <= tol ) return 1;
		else return 0;
    }

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

int imprimirVector( double vec[] , int longitud){
    int i;
    for ( i=0 ; i<longitud ; i++ ){
        cout << vec[i] << " ";
    }
    return 0;
}
