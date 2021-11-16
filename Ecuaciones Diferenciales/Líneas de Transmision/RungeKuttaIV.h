
#ifndef RUNGEKUTTAIV_H_
#define RUNGEKUTTAIV_H_


#include "Archivo.h"
#include "CalculosAuxiliares.h"



/*----------------------------------------------------------------------------------------------------------*/
/*
 * pre: H1Inicial y H2Inicial deben ser valores representativos de una altura de agua, por lo tanto no pueden ser
 * negativos. QInicial es el caudal inicial del primer reservorio al segundo. Tap es un valor del tiempo total
 * de apertura de la valvula, debe ser positivo. El parametro deltaT representa el tamaño del paso de
 * discretizacion y debe ser positivo. tiempoCorte debe ser positivo.
 * post: Resuelve el sistema de EDOs planteado para los valores iniciales pasados por parametro para 0<=t<=tiempoCorte
 * donde tn+1 = tn + deltaT con un metodo de Runge Kutta de orden IV. Los resultados son colocados en un archivo
 * de texto de nombre "salidaRKIV.txt".
 */
int resolverSistemaCompletoRKIV(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT, float tiempoCorte);


/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:H1Actual, H2Actual, tActual y Tap deben ser valores positivos.
 * post: avanza un paso en la discretización utilizando los valores actuales pasados por parametro con un metodo
 * de Runge Kutta de orden IV. Los valores obtenidos son almacenados en las variables H1Siguiente, H2Siguiente,
 * QSiguiente y tSiguiente.
 */

int obtenerValoresParaPasoSiguienteRKIV(float H1Actual, float H2Actual, float QActual, float tActual,
		float &H1Siguiente, float &H2Siguiente, float &QSiguiente, float &tSiguiente, float deltaT, float Tap, float Ke);




#endif /* RUNGEKUTTAIV_H_ */
