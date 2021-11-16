/*
 * MatrizA.h
 *  
 */


#ifndef MATRIZA_H_INCLUDED
#define MATRIZA_H_INCLUDED


/*
 * El objetivo de la clase es modelar una matriz tridiagonal en bloques simetrica, cada bloque contiene matrices.
 */

/*
 * El objetivo de la clase es modelar una matriz tridiagonal en bloques simetrica, cada bloque contiene valores numéricos (double).
 * Existen 3 tipos de matrices: "T", "-I" y Nulas".
 */

class MatrizA{

public:

	/*
	 * pre: n debe ser un entero mayor a 1.
	 * post: inicializa la matriz de dimension n con los valores por defecto.
	 */
	MatrizA(int n);

	/*--------------------------------------------------------------------*/
	/*
	 * pre:
	 * post: libera los recursos asociados a la instancia
	 */
	~MatrizA();

	/*--------------------------------------------------------------------*/

	/*
	 * pre: 0<=fil<(n-1)^2   y   0<=col<(n-1)^2
	 * post: devuelve el valor contenido en la posición fil, col de la matriz
	 */
	double get(int fil, int col) const;

	/*--------------------------------------------------------------------*/
	/*
	 * pre:
	 * post: devuelve la dimensión de la matriz
	 */
	int dim() const;

	/*--------------------------------------------------------------------*/

private:

	/*
	 * diagonales no nulas de la matriz
	 */
	Bloque Dp;
	Bloque Ds;


	/* dimensión de la matriz */
	int n;

	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: Establece los elementos de la diagonal principal, toda la diagonal tiene el mismo valor.
	 */
	void setDp();

	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: Establece los elementos de la diagonal secundaria, toda la diagonal tiene el mismo valor.
	 */
	void setDs();


};

#endif // MatrizA_H_INCLUDED
