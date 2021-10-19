/*
 * Localidad.h
 *
 *  Created on: 19 oct. 2021
 *      Author: riky
 */

#ifndef LOCALIDAD_H_
#define LOCALIDAD_H_

#define REINTENTOS 3
#define VACIO 0
#define CARGADO 1
#define TAMCARACTER 50
#include "B.h"
#include "Clientes.h"
typedef struct
{
		int idLocalidad;
		char descripcion[50];
		int isEmpty;
}eLocalidad;
/// @param lista carga una lista de localidades
/// @param len
void HardcodeLocalidades (eLocalidad lista[],int len);
/// @param list inicializa el array en 0
/// @param tam
/// @return
int InicializarArrayLocalidad(eLocalidad* list, int tam);
/// @param list adhiere una localidad
/// @param len
/// @param id
/// @param localidad
/// @return
int addLocalidad(eLocalidad* list, int len, int id, char localidad[]);
/// @param lista busca espacio vacio
/// @param tam
/// @return retorna el index
int BuscarPrimerEspacioVacioL(eLocalidad* lista, int tam);
//
/// @param list lista a mostrar
void MostrarLocalidad(eLocalidad list);
/// @param lista imprime localidades cargadas
/// @param largo tama�o de la lista
/// @return retorna -1 error 0 correcto
int printLocalidades(eLocalidad* lista, int largo);
/// @param lista lista a cargar datos
/// @param tam
/// @param contadorId contador de id localidad
/// @return retorna -1 error 0 correcto
int CargarLocalidad(eLocalidad lista[], int tam, int* contadorId);

#endif /* LOCALIDAD_H_ */
