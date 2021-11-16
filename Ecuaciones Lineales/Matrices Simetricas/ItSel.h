/*
 * ItSel.h
 *
 *  Created on: 17-abr-2009
 *       
 */

#ifndef ITSEL_H_
#define ITSEL_H_

#define RTOL 0.001


/*------------------------------------------------------------------------------*/
/*
 * pre:
 * post: imprime la matriz por consola
 */
void mostrarMatriz(const TBMatrix & matriz);
/*------------------------------------------------------------------------------*/
/*
 * pre: n debe ser la dimension de actual y anterior, tol es la precisión relativa.
 * post: devuelve 1 si se cumple el criterio de convergencia R^k <= RTOL
 */
int criterioConvergencia( double actual[] , double anterior[] , int n , double tol );
/*------------------------------------------------------------------------------*/
/*
 * pre: longitud debe ser la dimension de vec
 * post: imprime los elementos de vec por consola
 */
int imprimirVector( double vec[] , int longitud);
/*------------------------------------------------------------------------------*/
/*
 * pre: longitud debe ser la dimension de destino y de origen
 * post: copia el contenido de origen sobre destino
 */
int copiarVector( double destino[] , double origen[] , int longitud );
/*------------------------------------------------------------------------------*/
/*
 * pre: x debe tener la misma dimension que A
 * post: devuelve el resultado de multiplicar el vector x por la matriz A
 */
double* multiplicarMatrizPorVector(const TBMatrix & A, double* x);
/*------------------------------------------------------------------------------*/
/*
 * pre: b debe tener la misma dimension que A
 * post: resuelve el sistema Ax = b con el metodo de Jacobi
 */
double* jacobi(const TBMatrix & A, double* b);
/*------------------------------------------------------------------------------*/
/*
 * pre: b debe tener la misma dimension que A
 * post: resuelve el sistema Ax = b con el metodo de Gauss Seidel
 */
double* gaussSeidel(const TBMatrix & A, double* b);
/*------------------------------------------------------------------------------*/
/*
 * pre: b debe tener la misma dimension que A
 * post: resuelve el sistema Ax = b con el metodo de SOR
 */
double* SOR(const TBMatrix & A, double* b, double w, int & k);
/*------------------------------------------------------------------------------*/

#endif /* ITSEL_H_ */
