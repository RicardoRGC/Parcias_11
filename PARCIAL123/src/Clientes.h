/*
 * Clientes.h
 *
 *  Created on: 19 oct. 2021
 *      Author: riky
 */

#ifndef CLIENTES_H_
#define CLIENTES_H_


#include "B.h"
typedef struct
{
		int id;
		char empresa[50];
		char direccion[50];
		double cuit;
		int idLocalidad;
		int isEmpty;
}eClientes;
/// @param lista carga una lista en clientes
/// @param len tamaño de la lista
void HardcodeClientes (eClientes lista[],int len);
/// @param lista busca q la lista tengo isempty cargado;
/// @param tam
/// @return retorna el index cargado;
int buscarlistaCargada(eClientes* lista, int tam);
/// @param list lista a adherir parametros
/// @param len tamaño de lista
/// @param id
/// @param empresa
/// @param direccion
/// @param localidad
/// @param cuit
/// @return retorna -1 error 0 correcto
int addEmployee(eClientes* list, int len, int id, char empresa[],char direccion[],int localidad,
				double cuit);
//void MostrarEmpleado(eClientes list);
/// @param list inicializa la lista en vacio.
/// @param tam
/// @return retorna -1 error 0 correcto
int InicializarArray(eClientes* list, int tam);
/// @param lista  busca espacio vacio en lista
/// @param tam
/// @return retorna el index de espacio vacio
int BuscarPrimerEspacioVacio(eClientes* lista, int tam);


#endif /* CLIENTES_H_ */
