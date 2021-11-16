#ifndef EULER_H_INCLUDED
#define EULER_H_INCLUDED

#include "Archivo.h"
#include "CalculosAuxiliares.h"

int resolverSistemaCompletoEuler(double VInicial, double vInicial, double deltaT, double tiempoCorte, int variable);

/*------------------------------------------------------------------------------------------*/

int obtenerValoresParaPasoSiguienteEuler(double VActual, double vActual, double tActual,
            double &VSiguiente, double &vSiguiente, double &tSiguiente, double deltaT);

#endif // EULER_H_INCLUDED
