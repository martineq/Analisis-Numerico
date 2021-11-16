/*
 * main.cpp
 *
 *  Created on: 30-may-2009
 *       
 */

#include "RungeKuttaII.h"
#include "RungeKuttaIV.h"
#include <iostream>

using namespace std;

int main(){

	float H1Inicial = 20.22;
	float H2Inicial = 0;
	float QInicial = 0;
	float Tap = 180;
	float Ke = 2.6; //2.6
	float deltaT = 1;
	float tiempoCorte = 600;

	resolverSistemaCompletoRKII(H1Inicial, H2Inicial, QInicial, Tap, Ke, deltaT, tiempoCorte);

	resolverSistemaCompletoRKIV(H1Inicial, H2Inicial, QInicial, Tap, Ke, deltaT, tiempoCorte);

	obtenerCurvaDeAjusteParaTiemposDeEcualizacion(7, 21, 1, 180, Ke, deltaT);



	return 0;
}
