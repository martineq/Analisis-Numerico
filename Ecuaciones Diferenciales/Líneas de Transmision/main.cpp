
#include "Euler.h"
#include "RungeKuttaII.h"
#include <iostream>

using namespace std;

int main(){

	double VInicial = 10.00;
	double vInicial = 0.00;
    double IInicial = 0.20;
	double iInicial = 0.00;
    double tiempoCorte = 15.00;
    //double deltaT = 0.001; //Uso un solo paso 'K'
    double pasos[8]={0.5,0.1,0.05,0.01,0.005,0.001,0.0005,0.0001}; //Uso un vector con varios pasos 'K'

    for ( int i=0 ; i<8 ; i++){
    resolverSistemaCompletoEuler(VInicial, vInicial, pasos[i], tiempoCorte, 0);
    resolverSistemaCompletoRKII(VInicial, vInicial, pasos[i], tiempoCorte, 0);
    resolverSistemaCompletoEuler(IInicial, iInicial, pasos[i], tiempoCorte, 1);
    resolverSistemaCompletoRKII(IInicial, iInicial, pasos[i], tiempoCorte, 1);
    }

	return 0;
}
