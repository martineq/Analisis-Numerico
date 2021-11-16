/*
 * RungeKuttaIV.cpp
 *
 *  Created on: 05-jun-2009
 *       
 */

#include "RungeKuttaIV.h"


/*------------------------------------------------------------------------------------------*/
int resolverSistemaCompletoRKIV(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT, float tiempoCorte){

	float tActual = 0;
	float H1Actual = H1Inicial;
	float H2Actual = H2Inicial;
	float QActual = QInicial;

	float tSiguiente, H1Siguiente, H2Siguiente, QSiguiente;

	/* Falta preparar el archivo */
	Archivo archivo("salidaRKIV.txt");
	archivo.imprimir("Tiempo(seg)\tH1(m)\t\tH2(m)\t\tCaudal(m^3/seg)\n");
	char cadena[100];
	sprintf(cadena,"%f\t%f\t%f\t%f\n", tActual, H1Actual, H2Actual, QActual);
	archivo.imprimir(cadena);

	while(tActual<tiempoCorte){



		obtenerValoresParaPasoSiguienteRKIV(H1Actual, H2Actual, QActual, tActual, H1Siguiente, H2Siguiente, QSiguiente, tSiguiente, deltaT, Tap, Ke);
		tActual = tSiguiente;
		H1Actual = H1Siguiente;
		H2Actual = H2Siguiente;
		QActual = QSiguiente;

		sprintf(cadena,"%f\t%f\t%f\t%f\n", tActual, H1Actual, H2Actual, QActual);
		archivo.imprimir(cadena);

	}
	return 1;
}

/*------------------------------------------------------------------------------------------*/

int obtenerValoresParaPasoSiguienteRKIV(float H1Actual, float H2Actual, float QActual, float tActual,
		float &H1Siguiente, float &H2Siguiente, float &QSiguiente, float &tSiguiente, float deltaT, float Tap, float Ke){

	/* Discretizacion
	 * u = Q
	 * v = H1
	 * w = H2
	 */

	float q1u, q2u, q3u, q4u, q1v, q2v, q3v, q4v, q1w, q2w, q3w, q4w;

	q1u = deltaT * funcionQ(H1Actual, H2Actual, QActual, tActual, Tap, Ke);
	q1v = deltaT * funcionH1(QActual);
	q1w = deltaT * funcionH2(QActual);

	q2u = deltaT * funcionQ(H1Actual + 0.5*q1v, H2Actual + 0.5*q1w, QActual + 0.5*q1u, tActual + 0.5*deltaT, Tap, Ke);
	q2v = deltaT * funcionH1(QActual + 0.5*q1u);
	q2w = deltaT * funcionH2(QActual + 0.5*q1u);

	q3u = deltaT * funcionQ(H1Actual + 0.5*q2v, H2Actual + 0.5*q2w, QActual + 0.5*q2u, tActual + 0.5*deltaT, Tap, Ke);
	q3v = deltaT * funcionH1(QActual + 0.5*q2u);
	q3w = deltaT * funcionH2(QActual + 0.5*q2u);

	q4u = deltaT * funcionQ(H1Actual + q3v, H2Actual + q3w, QActual + q3u, tActual + deltaT, Tap, Ke);
	q4v = deltaT * funcionH1(QActual + q3u);
	q4w = deltaT * funcionH2(QActual + q3u);

	QSiguiente = QActual + 0.166667 * (q1u + 2*q2u + 2*q3u + q4u);
	H1Siguiente = H1Actual + 0.166667 * (q1v + 2*q2v + 2*q3v + q4v);
	H2Siguiente = H2Actual + 0.166667 * (q1w + 2*q2w + 2*q3w + q4w);
	tSiguiente = tActual + deltaT;

	return 1;
}

