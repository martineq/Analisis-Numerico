/*
 * RungeKuttaII.h
 *
 *  Created on: 30-may-2009
 *       
 */

#ifndef RUNGEKUTTAII_H_
#define RUNGEKUTTAII_H_


#include "Archivo.h"
#include "CalculosAuxiliares.h"



/*----------------------------------------------------------------------------------------------------------*/
/*
 * pre: H1Inicial y H2Inicial deben ser valores representativos de una altura de agua, por lo tanto no pueden ser
 * negativos. QInicial es el caudal inicial del primer reservorio al segundo. Tap es un valor del tiempo total
 * de apertura de la valvula, debe ser positivo. El parametro deltaT representa el tamaño del paso de
 * discretizacion y debe ser positivo. tiempoCorte debe ser positivo.
 * post: Resuelve el sistema de EDOs planteado para los valores iniciales pasados por parametro para 0<=t<=tiempoCorte
 * donde tn+1 = tn + deltaT con un metodo de Runge Kutta de orden II. Los resultados son colocados en un archivo
 * de texto de nombre "salidaRKII.txt".
 */
int resolverSistemaCompletoRKII(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT, float tiempoCorte);


/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:H1Actual, H2Actual, tActual y Tap deben ser valores positivos.
 * post: avanza un paso en la discretización utilizando los valores actuales pasados por parametro con un metodo
 * de Runge Kutta de orden II. Los valores obtenidos son almacenados en las variables H1Siguiente, H2Siguiente,
 * QSiguiente y tSiguiente.
 */

int obtenerValoresParaPasoSiguienteRKII(float H1Actual, float H2Actual, float QActual, float tActual,
		float &H1Siguiente, float &H2Siguiente, float &QSiguiente, float &tSiguiente, float deltaT, float Tap, float Ke);


/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre: H1Inicial y H2Inicial deben ser valores representativos de una altura de agua, por lo tanto no pueden ser
 * negativos. QInicial es el caudal inicial del primer reservorio al segundo. Tap es un valor del tiempo total
 * de apertura de la valvula, debe ser positivo. El parametro deltaT representa el tamaño del paso de
 * discretizacion y debe ser positivo.
 * post: Devuelve el tiempo para el cual se igualan por primera vez los niveles de agua H1 y H2, para los valores
 * iniciales pasados por parametro donde tn+1 = tn + deltaT con un metodo de Runge Kutta de orden II.
 */
float obtenerTiempoEcualizacion(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT);

/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:
 * post: Calcula la interseccion entre las rectas
 *
 * 			Y11 + t(Y12-Y11)/(X2 - X1)
 * 			Y21 + t(Y22-Y21)/(X2 - X1)
 *
 * Devuelve X1 + t
 */

float interpolarTiempoEcualizacion(float Y11, float Y21, float X1, float Y12, float Y22, float X2);

/*----------------------------------------------------------------------------------------------------------*/
/*
 * pre: saltoInicial, saltoFinal, pasoSalto, Tap, Ke y deltaT deben ser valores positivos. saltoFinal>saltoInicial.
 * post: Obtiene los tiempos de ecualizacion para valores del salto comprendidos entre saltoInicial y saltoFinal con
 * un paso de pasoSalto. Discretizando el sistema con un paso deltaT en todos los calculos. Utilizando un tiempo de
 * apertura de la valvula Tap y un coeficiente de perdida total del sistema Ke. Los resultados son almacenados
 * en un archivo de nombre "Tiempos de Ecualizacion.txt"
 */

int obtenerCurvaDeAjusteParaTiemposDeEcualizacion(float saltoInicial, float saltoFinal, float pasoSalto, float Tap, float Ke, float deltaT);

#endif /* RUNGEKUTTAII_H_ */
