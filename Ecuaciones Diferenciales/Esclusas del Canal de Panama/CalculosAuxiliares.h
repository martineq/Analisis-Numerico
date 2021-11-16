/*
 * CalculosAuxiliares.h
 *
 *  Created on: 05-jun-2009
 *       
 */

#ifndef CALCULOSAUXILIARES_H_
#define CALCULOSAUXILIARES_H_

#include "math.h"

#define OHMEGA1 26950  	//area superficial de la esclusa 1 (55 m * 490 m)
#define OHMEGA2 26950  	//area superficial de la esclusa 2 (55 m * 490 m)
#define G 9.8 			//aceleracion de la gravedad 9.8 m/seg^2
#define A 53.95 		//area de la sección transversal de cada conducto (8.30 m * 6.50 m)
#define L 800			//longitud de cada conducto 800 m
#define f 0.02			//factor de friccion de Darcy-Weisbach
#define De 8.288		//diametro equivalente de la seccion transversal ((4*A/Pi)^1/2)


/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:
 * post: devuelve el valor de dH1/dt para el valor de Q pasado por parametro.
 */

float funcionH1(float Q);

/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:
 * post: devuelve el valor de dH2/dt para el valor de Q pasado por parametro.
 */

float funcionH2(float Q);

/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre: H1, H2, t y Tap deben ser valores positivos.
 * post: devuelve el valor de dQ/dt para los valores pasados por parametro
 */

float funcionQ(float H1, float H2, float Q, float t, float Tap, float Ke);

/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre: t y Tap deben ser valores positivos.
 * post: Devuelve el valor de Kv para los valores pasados por parametro mediante interpolacion lineal.
 */

float obtenerKv(float t, float Tap);


#endif /* CALCULOSAUXILIARES_H_ */
