/*
 * Bloque.h
 *  
 */


#ifndef BLOQUE_H_INCLUDED
#define BLOQUE_H_INCLUDED


/*
 * El objetivo de la clase es modelar una matriz tridiagonal en bloques simetrica, cada bloque contiene valores numéricos (double).
 * Existen 3 tipos de matrices: "T", "-I" y "Nulas".
 */

class Bloque{

public:

	/*
	 * pre: n debe ser un entero mayor a 1, El valor de "tipo" puede ser: 1-> Bloque "T", 2-> Bloque "-I".
	 * post: inicializa la matriz de dimension n con los valores por defecto según el tipo de bloque.
	 */
	Bloque(int n, int tipo);

	/*--------------------------------------------------------------------*/
	/*
	 * pre:
	 * post: libera los recursos asociados a la instancia
	 */
	~Bloque();

	/*--------------------------------------------------------------------*/

	/*
	 * pre: 0<=fil<n   y   0<=col<n
	 * post: devuelve el valor contenido en la posición fil, col de la matriz
	 */
	double get(int fil, int col);

	/*--------------------------------------------------------------------*/
	/*
	 * pre:
	 * post: devuelve la dimensión de la matriz
	 */
	int dim();

	/*--------------------------------------------------------------------*/

private:

	/*
	 * diagonales no nulas de la matriz
	 */
	double Dp;
	double Ds;


	/* dimensión de la matriz */
	int n;

	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: Establece los elementos de la diagonal principal, toda la diagonal tiene el mismo valor.
	 */
	void setDp(double valor);

	/*--------------------------------------------------------------------*/

	/*
	 * pre:
	 * post: Establece los elementos de la diagonal secundaria, toda la diagonal tiene el mismo valor.
	 */
	void setDs(double valor);


};

#endif // BLOQUE_H_INCLUDED
