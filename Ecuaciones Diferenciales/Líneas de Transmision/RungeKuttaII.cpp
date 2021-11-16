
#include "RungeKuttaII.h"


/*------------------------------------------------------------------------------------------*/

int resolverSistemaCompletoRKII(double VInicial, double vInicial, double deltaT, double tiempoCorte, int variable){

	double tActual = 0;
	double VActual = VInicial; //Valor inicial de la variable
	double vActual = vInicial; //Valor inicial de la derivada de la variable

	double tSiguiente, VSiguiente, vSiguiente,VMax=0;

    char var[20];
	char cadena[100];


	if (variable == 1){
        sprintf(var,"%c_RKII_%.5f.txt",'I',deltaT);
        sprintf(cadena,"Posición z(m)\t%c(Ampere)\n----------------------------\n",'I');
	}else{sprintf(var,"%c_RKII_%.5f.txt",'V',deltaT);
          sprintf(cadena,"Posición z(m)\t%c(Volt)\n----------------------------\n",'V');
	}

	Archivo archivo(var);
	archivo.imprimir(cadena);
	sprintf(cadena,"%f\t%f\n", tActual, VActual);
    archivo.imprimir(cadena);

	while(tActual<tiempoCorte){

		obtenerValoresParaPasoSiguienteRKII(VActual, vActual, tActual, VSiguiente, vSiguiente, tSiguiente, deltaT);
		tActual = tSiguiente;
		VActual = VSiguiente;
		vActual = vSiguiente;

        if ( (VSiguiente>VMax) or (-VSiguiente<-VMax) ) VMax=VSiguiente;

		sprintf(cadena,"%f\t%f\n", tActual, VActual);
		archivo.imprimir(cadena);
	}

    sprintf(cadena,"----------------------------\nMódulo Máx:%f\n", VMax);
    archivo.imprimir(cadena);

	return 0;
}

/*------------------------------------------------------------------------------------------*/

int obtenerValoresParaPasoSiguienteRKII(double VActual, double vActual, double tActual,
            double &VSiguiente, double &vSiguiente, double &tSiguiente, double deltaT){

	/* Discretización:
	 * V: Variable original
	 * v: Derivada de la variable
	 */

	double qV1, qV2, qv1, qv2;

	qV1 = deltaT * funcionV(vActual);
	qv1 = deltaT * funcionv(VActual);
	qV2 = deltaT * funcionV(vActual + qv1);
	qv2 = deltaT * funcionv(VActual + qV1);
	VSiguiente = VActual + 0.5 * (qV1 + qV2);
	vSiguiente = vActual + 0.5 * (qv1 + qv2);

	tSiguiente = tActual + deltaT;

	return 0;
}

