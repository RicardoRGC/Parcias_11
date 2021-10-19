/*
 * Localidad.c
 *
 *  Created on: 19 oct. 2021
 *      Author: riky
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Localidad.h"

void HardcodeLocalidades (eLocalidad lista[],int len)
{
    eLocalidad listaHardcodeada[] = {{1,"Avellaneda",1},{2,"Quilmes",1},{3,"Lanus",1}};
    for (int i = 0; i < 3; i++)
    {
        lista[i]=listaHardcodeada[i];
    }
}


int InicializarArrayLocalidad(eLocalidad* list, int tam)
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
int CargarLocalidad(eLocalidad lista[], int tam, int* contadorId)
{
	int retorno = -1;
	int auxContador;
	auxContador = *contadorId;
	char localidad[TAMCARACTER];

	if (BuscarPrimerEspacioVacioL(lista, tam) != -1)
	{
		if ((getString(localidad, TAMCARACTER, "ingrese Nombre de localidad a agregar:", "\n Error\n", REINTENTOS) == 0))
		{
			auxContador++;

			retorno = addLocalidad(lista, tam, auxContador,localidad);

		}
		else
		{
			printf("\n supero los intentos, No pudo cargar\n");
		}
	}
	else
	{
		printf("lista llena");
	}
	*contadorId = auxContador;
	return retorno;
}
int addLocalidad(eLocalidad* list, int len, int id, char localidad[])
{
	int resultado;
	int espacioVacio;

	resultado = -1;
	espacioVacio = BuscarPrimerEspacioVacioL(list, len);

	if ((list != 0) && (len > 0) && (espacioVacio != -1))
	{

		list[espacioVacio].idLocalidad = id;
		strcpy(list[espacioVacio].descripcion, localidad);
		list[espacioVacio].isEmpty = CARGADO;

		resultado = 0;
	}

	return resultado;
}
int BuscarPrimerEspacioVacioL(eLocalidad* lista, int tam)
{
	int index;
	index = -1;

	int i;

	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == VACIO) //si esta vacio
		{
			index = i;
			break;
		}
	}

	return index;
}
int printLocalidades(eLocalidad* lista, int largo)
{
	int retorno = -1;
	printf("                  LISTA DE LOCALIDADES\n"
					"----------------------------------------------------------\n"
					"ID    localidad   \n"
					"-----------------------------------------------------------\n");

	if (lista != NULL && largo > 0)
	{
		for (int i = 0; i < largo; i++)
		{
			if ((lista[i].isEmpty == 1))
			{

				MostrarLocalidad(lista[i]);
				retorno = 0;
			}

		}
	}
	return retorno;
}
void MostrarLocalidad(eLocalidad list)
{
	printf("\n%-5d %s\n", list.idLocalidad, list.descripcion);

}
