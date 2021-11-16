/*
 * RungeKuttaII.cpp
 *
 *  Created on: 30-may-2009
 *       
 */

#include "RungeKuttaII.h"


/*------------------------------------------------------------------------------------------*/
int resolverSistemaCompletoRKII(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT, float tiempoCorte){

	float tActual = 0;
	float H1Actual = H1Inicial;
	float H2Actual = H2Inicial;
	float QActual = QInicial;

	float tSiguiente, H1Siguiente, H2Siguiente, QSiguiente;

	/* Falta preparar el archivo */
	Archivo archivo("salidaRKII.txt");
	archivo.imprimir("Tiempo(seg)\tH1(m)\t\tH2(m)\t\tCaudal(m^3/seg)\n");
	char cadena[100];
	sprintf(cadena,"%f\t%f\t%f\t%f\n", tActual, H1Actual, H2Actual, QActual);
	archivo.imprimir(cadena);

	while(tActual<tiempoCorte){



		obtenerValoresParaPasoSiguienteRKII(H1Actual, H2Actual, QActual, tActual, H1Siguiente, H2Siguiente, QSiguiente, tSiguiente, deltaT, Tap, Ke);
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

int obtenerValoresParaPasoSiguienteRKII(float H1Actual, float H2Actual, float QActual, float tActual,
		float &H1Siguiente, float &H2Siguiente, float &QSiguiente, float &tSiguiente, float deltaT, float Tap, float Ke){

	/* Discretizacion
	 * u = Q
	 * v = H1
	 * w = H2
	 */

	float q1u, q2u, q1v, q2v, q1w, q2w;

	q1u = deltaT * funcionQ(H1Actual, H2Actual, QActual, tActual, Tap, Ke);
	q1v = deltaT * funcionH1(QActual);
	q1w = deltaT * funcionH2(QActual);

	q2u = deltaT * funcionQ(H1Actual + q1v, H2Actual + q1w, QActual + q1u, tActual + deltaT, Tap, Ke);
	q2v = deltaT * funcionH1(QActual + q1u);
	q2w = deltaT * funcionH2(QActual + q1u);

	QSiguiente = QActual + 0.5 * (q1u + q2u);
	H1Siguiente = H1Actual + 0.5 * (q1v + q2v);
	H2Siguiente = H2Actual + 0.5 * (q1w + q2w);
	tSiguiente = tActual + deltaT;

	return 1;
}

/*-----------------------------------------------------------------------------------------*/

int obtenerCurvaDeAjusteParaTiemposDeEcualizacion(float saltoInicial, float saltoFinal, float pasoSalto, float Tap, float Ke, float deltaT){

	float salto = saltoInicial;
	float tiempoEcualizacion;

	/* Preparacion del Archivo de salida */
	Archivo archivo("Tiempos de Ecualizacion.txt");
	archivo.imprimir("Salto (m)\tTiempo de Ecualizacion(seg)\n");
	char cadena[100];

	while(salto<=saltoFinal){
		tiempoEcualizacion = obtenerTiempoEcualizacion(salto, 0, 0, Tap, Ke, deltaT);
		sprintf(cadena,"%f\t%f\n",salto,tiempoEcualizacion);
		archivo.imprimir(cadena);
		salto += pasoSalto;
	}

	return 1;

}

/*-----------------------------------------------------------------------------------------*/

float obtenerTiempoEcualizacion(float H1Inicial, float H2Inicial, float QInicial, float Tap, float Ke, float deltaT){

	/* Este metodo es muy similar a resolverSistemaCompletoRKII solo que cambia la condicion de corte
	 * y se agrega una interpolacion para determinar con mayor presicion el valor de tiempoEcualizacion buscado
	 */

	float tiempoEcualizacion;

	float tActual = 0;
	float H1Actual = H1Inicial;
	float H2Actual = H2Inicial;
	float QActual = QInicial;

	float tSiguiente, H1Siguiente, H2Siguiente, QSiguiente, H1Anterior, H2Anterior;

	while (H1Actual > H2Actual){

		obtenerValoresParaPasoSiguienteRKII(H1Actual, H2Actual, QActual, tActual, H1Siguiente, H2Siguiente, QSiguiente, tSiguiente, deltaT, Tap, Ke);

		H1Anterior = H1Actual;	/* datos almacenados para la posterior interpolacion */
		H2Anterior = H2Actual;

		tActual = tSiguiente;
		H1Actual = H1Siguiente;
		H2Actual = H2Siguiente;
		QActual = QSiguiente;
	}

	tiempoEcualizacion = interpolarTiempoEcualizacion(H1Anterior, H2Anterior, tActual - deltaT, H1Actual, H2Actual, tActual);

	return tiempoEcualizacion;
}

/*-----------------------------------------------------------------------------------------*/

float interpolarTiempoEcualizacion(float Y11, float Y21, float X1, float Y12, float Y22, float X2){

	/*
	 * Y11 + t(Y12-Y11)/(X2 - X1) = Y21 + t(Y22-Y21)/(X2 - X1)
	 *
	 * Y11 - Y21 = t((Y22-Y21)/(X2 - X1) - (Y12-Y11)/(X2 - X1))
	 * Y11 - Y21 = t{[(Y22-Y21) - (Y12-Y11)]/(X2 - X1)}
	 *
	 * t = [(Y11 - Y21) * (X2 - X1)]/[(Y22-Y21) - (Y12-Y11)]
	 */

	float resultado = X1 + ((Y11 - Y21) * (X2 - X1))/((Y22 - Y21) - (Y12 - Y11));

	return resultado;

}
