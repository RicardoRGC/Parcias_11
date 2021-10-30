/*
 * Clientes.c
 *
 *  Created on: 19 oct. 2021
 *      Author: riky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Clientes.h"
#include "Localidad.h"
#define REINTENTOS 3
#define VACIO 0
#define CARGADO 1
/////////////////////////////////////////////////////////////////////////
///
void HardcodeClientes (eClientes lista[],int len)
{
    eClientes listaHardcodeada[] = {
    				{1,"EDESUR","AV JUJUY 1100",2035580883,1,1},
    				{2,"TELEFONICA","AV CORDOBA 4000",3045649737,1,1},
						{3,"METROGAS","AV CORRIENTES 2000",20643676741,2,1},
						{4,"METROVIAS","LINIERS 2233",20734786464,3,1},
						{5," COTO","OSORIO 1320",2066737474,2,1}};
    for (int i = 0; i < 5; i++)
    {
        lista[i]=listaHardcodeada[i];
    }
}

int InicializarArray(eClientes* list, int tam)
{
	int retorno;
	retorno = -1;
	if (list != NULL && tam > 0)
	{
		for (int i = 0; i < tam; i++)
		{
			list[i].isEmpty = VACIO;
			retorno = 0;
		}
	}

	return retorno;
}
int BuscarPorEstadoEnCliente(eClientes* lista, int tam, int estado)
{
	int index;
	index = -1;
	int i;
	if (lista != NULL && tam > 0)
	{
	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == estado)
		{
			index = i;
			break;
		}
	}
	}

	return index;
}
int buscarlistaCargada(eClientes* lista, int tam)
{
	int index;
	index = 0;
	int i;
	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == CARGADO) //si hay uno cargado devuelve 1
		{
			index = 1;
			break;
		}
	}

	return index;
}



int addEmployee(eClientes* list, int len, int id, char empresa[],char direccion[],int localidad,
				double cuit)
{
	int resultado;
	int espacioVacio;

	resultado = -1;
	espacioVacio= BuscarPorEstadoEnCliente(list, len, VACIO);

	if ((list != 0) && (len > 0) && (espacioVacio != -1)&&(localidad!=-1)) // separar en 2 if..
	{

		list[espacioVacio].id = id;
		 strcpy(list[espacioVacio].empresa, empresa);
		 strcpy(list[espacioVacio].direccion, direccion);
		 list[espacioVacio].idLocalidad = localidad;
		 list[espacioVacio].cuit = cuit;
		 list[espacioVacio].isEmpty = CARGADO;

		resultado = 0;
	}

	return resultado;
}

