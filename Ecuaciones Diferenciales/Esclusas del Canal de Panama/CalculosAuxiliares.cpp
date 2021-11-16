/*
 * CalculosAuxiliares.cpp
 *
 *  Created on: 05-jun-2009
 *       
 */

#include "CalculosAuxiliares.h"


/*-----------------------------------------------------------------------------------------*/

float funcionH1(float Q){
	float resultado = -2 * Q / OHMEGA1;
	return resultado;
}

/*-----------------------------------------------------------------------------------------*/

float funcionH2(float Q){
	float resultado = 2 * Q / OHMEGA2;
	return resultado;
}

/*-----------------------------------------------------------------------------------------*/

float funcionQ(float H1, float H2, float Q, float t, float Tap, float Ke){
	float resultado;

	float Kv = obtenerKv(t, Tap);

	resultado = (G*A/L) * (H1 - H2) - (f/(2*De*A)) * Q * fabs(Q) - (Ke/(2*A*L)) * Q * fabs(Q) - (Kv/(2*A*L)) * Q * fabs(Q);

	return resultado;
}

/*-----------------------------------------------------------------------------------------*/

float obtenerKv(float t, float Tap){

	float porcentajeApertura;

	if (t < Tap){
		porcentajeApertura = (t/Tap) * 100;
	}
	else{
		porcentajeApertura = 100;
	}

	/* Interpolacion ----------------*/

	float apertura[18] = {0, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30, 40, 50, 60, 70, 80, 90, 95, 100};
	float Kv[18] = {10000, 2840, 730, 335, 185, 110, 75, 55, 43, 17, 8, 4, 2, 1, 0.5, 0.26, 0.17, 0.11};

	float resultado;

	if (porcentajeApertura == 100){
		resultado = Kv[17];
	}
	else{
		for (int i = 0; i<=17; i++){
			if((porcentajeApertura >= apertura[i]) and (porcentajeApertura < apertura[i+1])){
				resultado = Kv[i] + ((porcentajeApertura - apertura[i]) * (Kv[i+1] - Kv[i]) / (apertura[i+1] - apertura[i]));
			}
		}
	}
	return resultado;

}
