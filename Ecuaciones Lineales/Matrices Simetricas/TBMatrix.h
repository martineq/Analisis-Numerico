/*
 * TBMatrix.h
 *
 *  Created on: 16-abr-2009
 *       
 */

#ifndef TBMATRIX_H_
#define TBMATRIX_H_

/*
 * El objetivo de la clase es modelar una matriz tridiagonal en bloques simetrica
 */

class TBMatrix{

public:

	/*
	 * pre: n puede valer 6,9,12,30
	 * post: inicializa la matriz de dimension n con los valores por defecto
	 */
	TBMatrix(int n);

	/*--------------------------------------------------------------------*/

	/*
	 * pre: n pude valer 6,9,12,30. d1 debe apuntar a un arreglo de dimension n.
	 * d2 debe apuntar a un arreglo de dimension n-1 y d3 debe apuntar a un
	 * arreglo de dimensión n-3
	 * post: inicializa la matriz de dimensión n con las diagonales dadas
	 * por d1, d2 y d3
	 */
	TBMatrix(double* d1, double* d2, double* d3, int n);

	/*--------------------------------------------------------------------*/
	/*
	 * pre:
	 * post: libera los recursos asociados a la instancia
	 */
	~TBMatrix();

	/*--------------------------------------------------------------------*/

	/*
	 * pre: 0<=fil<n   y   0<=col<n
	 * post: devuelve el valor contenido en la posición fil, col de la matriz
	 */
	double get(int fil, int col) const;

	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: devuelve la dimension de la matriz
	 */
	int dim() const;

	/*--------------------------------------------------------------------*/

private:

	/*
	 * diagonales no nulas de la matriz
	 */
	double* d1;
	double* d2;
	double* d3;

	/* dimension de la matriz */
	int n;

	/*--------------------------------------------------------------------*/

	/*
	 * pre: diag debe apuntar a un arreglo de dimension n
	 * post: establece los elementos de la diagonal d1 identicos a los pasados
	 * por parametro
	 */
	void setD1(double* diag);
	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: establece los elementos de la diagonal d1 por defecto
	 */
	void setD1();

	/*--------------------------------------------------------------------*/

	/*
	 * pre: diag debe apuntar a un arreglo de dimension n-1
	 * post: establece los elementos de la diagonal d2 identicos a los pasados
	 * por parametro
	 */
	void setD2(double* diag);
	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: establece los elementos de la diagonal d2 por defecto
	 */
	void setD2();

	/*--------------------------------------------------------------------*/

	/*
	 * pre: diag debe apuntar a un arreglo de dimension n-3
	 * post: establece los elementos de la diagonal d3 identicos a los pasados
	 * por parametro
	 */
	void setD3(double* diag);
	/*--------------------------------------------------------------------*/

	/*
	 * pre: n pude valer 6,9,12,30.
	 * post: establece los elementos de la diagonal d3 por defecto
	 */
	void setD3();

	/*--------------------------------------------------------------------*/


};

#endif /* TBMATRIX_H_ */
