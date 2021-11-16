/*
 * Archivo.cpp
 *
 *    
 */

#include "Archivo.h"

/*--------------------------------------------------------------------------*/

Archivo::Archivo(){
    this->setNombre("salida.txt");
}

Archivo::Archivo(char* nombre){
    this->setNombre(nombre);
}

Archivo::~Archivo(){
	if (this->archivo){
		this->cerrar();
	}
}

void Archivo::setNombre(char* nombre){
    this->nombre=nombre;
    this->abrir();
}

void Archivo::abrir(){
    this->archivo = fopen( (this->nombre) , "w" );
    if( this->archivo )
      cout << endl << "Archivo creado.!" << endl;
    else{
      cout << endl << "Error Archivo NO CREADO." << endl;
   }
}

void Archivo::imprimir(char* c){
    fprintf( this->archivo , c );
}

void Archivo::cerrar(){
   if( !fclose( this->archivo ) ){
      cout << endl << "Archivo guardado." << endl;
   }else{
      cout << "Error: Archivo NO CERRADO." << endl;
    }

}

