#ifndef SOR_H_INCLUDED
#define SOR_H_INCLUDED

//#define RTOL 0.01

double* SOR( MatrizA & A, double* b, double w, int & k, double RTOL,int parte);

/*-----------------------------------------------------------------------------*/

void mostrarMatriz( MatrizA & matriz);

/*-----------------------------------------------------------------------------*/

int criterioConvergencia( double actual[] , double anterior[] , int n , double tol, double & R);

/*-----------------------------------------------------------------------------*/

int copiarVector( double destino[] , double origen[] , int longitud );

/*------------------------------------------------------------------------------*/
/*
 * pre: longitud debe ser la dimension de vec
 * post: imprime los elementos de vec por consola
 */
int imprimirVector( double vec[] , int longitud);
/*------------------------------------------------------------------------------*/

#endif // SOR_H_INCLUDED
