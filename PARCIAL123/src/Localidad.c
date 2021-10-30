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
int BuscarPrimerEspacioPorEstadoLocalidad(eLocalidad* lista, int tam,int estado)
{
	int index;
	index = -1;

	int i;

	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == estado) //si esta vacio
		{
			index = i;
			break;
		}
	}

	return index;
}
/*int buscarlistaCargadaLocalidad(eLocalidad* listaLocalidad, int tamLocalidad)
{
	int index;
	index = 0;
	int i;
	for (i = 0; i < tamLocalidad; i++)
	{
		if (listaLocalidad[i].isEmpty == CARGADO) //si hay uno cargado devuelve 1
		{
			index = 1;
			break;
		}
	}

	return index;
}*/
int buscarPorIdLocalidad(eLocalidad* list, int len, int id)
{
	int retorno = -1;

	for (int i = 0; i < len; i++)
	{
		if (list[i].idLocalidad == id && list[i].isEmpty == CARGADO)
		{
			retorno = i;
		}

	}

	return retorno;
}
int removeLocaliad(eLocalidad* listaLocalidad, int tamLocaliad)
{
	int retorno = -1;
	int confirmacion;
	int idLocalidad;
	int eliminarid;

	printLocalidades(listaLocalidad, tamLocaliad);

		if ( BuscarPrimerEspacioPorEstadoLocalidad(listaLocalidad, tamLocaliad,CARGADO)!=-1 )
		{

			if (getNumero(&idLocalidad, "\n ingrese id a eliminar", "no se puedo modifcar", 1,
			INT_MAX, 3) != 0)
			{
				printf("\n"
								"supero el maximo de intentos");
			}
			else
			{
				eliminarid = buscarPorIdLocalidad(listaLocalidad, tamLocaliad, idLocalidad);
	getNumero(&confirmacion, "ingrese 1 para confirmar 0 para cancelar", "error", 0, 1, REINTENTOS);

	if (confirmacion == 1)
	{


		if (eliminarid != -1 && listaLocalidad[eliminarid].isEmpty == CARGADO)
		{
			listaLocalidad[eliminarid].isEmpty = VACIO;

			retorno = 0;
		}
		else
		{
			printf("Error no se encontro id");
		}
	}
			}}
	return retorno;
}

int modificarLocalidad(eLocalidad* listaLocalidad, int tamLocalidad)
{
	int retorno=-1;
	int idLocalidad;
	int modifIde;
	char localidad[50];

	printLocalidades(listaLocalidad, tamLocalidad);

	if (BuscarPrimerEspacioPorEstadoLocalidad(listaLocalidad, tamLocalidad,CARGADO)!= -1)
	{

		if (getNumero(&idLocalidad, "\n ingrese id a modificar ", "no se puedo modifcar", 1,
		INT_MAX, 3) != 0)
		{
			printf("\n"
							"supero el maximo de intentos");
		}
		else
		{

			modifIde = buscarPorIdLocalidad(listaLocalidad, tamLocalidad, idLocalidad);
			if (modifIde != -1 && listaLocalidad[modifIde].isEmpty == CARGADO)
			{
				if (!getString(localidad, 50, "ingrese localidad", "error", REINTENTOS))
				{



					strcpy(listaLocalidad[modifIde].descripcion, localidad);

					retorno = 0;
				}
				else
				{
					printf("\n supero los intentos, No pudo cargar\n");

				}
			}

		}
///-----------------------------------------------
	}

	return retorno;

}
void CargarLocalidadesPorDefecto (eLocalidad lista[],int len)
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

	if (BuscarPrimerEspacioPorEstadoLocalidad(lista, tam,VACIO) != -1)
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
	espacioVacio = BuscarPrimerEspacioPorEstadoLocalidad(list, len,VACIO);

	if ((list != 0) && (len > 0) && (espacioVacio != -1))
	{

		list[espacioVacio].idLocalidad = id;
		strcpy(list[espacioVacio].descripcion, localidad);
		list[espacioVacio].isEmpty = CARGADO;

		resultado = 0;
	}

	return resultado;
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
