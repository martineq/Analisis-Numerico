/*
 * Archivo.h
 *
 *  Created on: 18-abr-2009
 *       
 */

#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <iostream>
using namespace std;

/*
* Clase que representa la salida de texto en un archivo
*/


class Archivo{

public:

	Archivo();

	Archivo(char* nombre);

	void imprimir(char* c);

	void cerrar();

	~Archivo();

	/*--------------------------------------------------------------------*/

private:

    /*
	 * Representa al archivo de texto
	 */
    FILE *archivo;

    char* nombre;

	void setNombre(char* nombre);

	void abrir();


};

#endif // ARCHIVO_H_INCLUDED
