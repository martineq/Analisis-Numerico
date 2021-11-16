
#ifndef RUNGEKUTTAII_H_
#define RUNGEKUTTAII_H_


#include "Archivo.h"
#include "CalculosAuxiliares.h"



/*----------------------------------------------------------------------------------------------------------*/
/*
 * pre: VInicial y vInicial deben ser valores representativos de una altura de agua, por lo tanto no pueden ser
 * negativos. QInicial es el caudal inicial del primer reservorio al segundo. El parametro deltaT representa el tamaño del paso de
 * discretizacion y debe ser positivo. tiempoCorte debe ser positivo. Si variable=1 resuelvo para corriente, sino, para potencial.
 * post: Resuelve el sistema de EDOs planteado para los valores iniciales pasados por parametro para 0<=t<=tiempoCorte
 * donde tn+1 = tn + deltaT con un metodo de Runge Kutta de orden II. Los resultados son colocados en un archivo
 * de texto de nombre "X_RKII.txt".
 */
int resolverSistemaCompletoRKII(double VInicial, double vInicial, double deltaT, double tiempoCorte, int variable);



/*----------------------------------------------------------------------------------------------------------*/

/*
 * pre:VActual, vActual, tActual deben ser valores positivos.
 * post: avanza un paso en la discretización utilizando los valores actuales pasados por parametro con un metodo
 * de Runge Kutta de orden II. Los valores obtenidos son almacenados en las variables VSiguiente, vSiguiente, tSiguiente.
 */

int obtenerValoresParaPasoSiguienteRKII(double VActual, double vActual, double tActual,
            double &VSiguiente, double &vSiguiente, double &tSiguiente, double deltaT);


/*----------------------------------------------------------------------------------------------------------*/



#endif /* RUNGEKUTTAII_H_ */
