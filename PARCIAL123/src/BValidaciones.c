/*
 * B.c
 *
 *  Created on: 21 sep. 2021
 *      Author: riky
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "B.h"
#include "BValidaciones.h"
int validarCadenaEspacios(char nombre[])
{

	int retorno;
		int longitud;

		retorno = 0;
		longitud = strlen(nombre);

		for (int i = 0; i < longitud; i++)
		{
			if ((isalpha(nombre[i]) || isdigit(nombre[i]) )&& longitud!= 0)
			{
				retorno = 1;

			}
		}

		return retorno;
}
int validarCadena(char nombre[])
{

	int retorno;
	int longitud;

	retorno = 1;
	longitud = strlen(nombre);

	for (int i = 0; i < longitud; i++)
	{
		if (!isalpha(nombre[i]) || longitud == 0)
		{
			retorno = 0;
		}
	}

	return retorno;
}
int myGetMinMax(char* cadena, int longitud,int longMin)
{
	char buffer[10000];
	int retorno;
	retorno = -1;

	if (cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
			if (buffer[strnlen(buffer, sizeof(buffer)) - 1] == '\n')
			{
				buffer[strnlen(buffer, sizeof(buffer)) - 1] = '\0'; //remplaza \n por \0.
			}
			if (strnlen(buffer, sizeof(buffer)) <= longitud && strlen(buffer) != 0 && (strnlen(buffer, sizeof(buffer)) >= 11))
			{
				strncpy(cadena, buffer, longitud);

				retorno = 0; //corecto
			}
		}
	}
	return retorno;
}
int myGets(char* cadena, int longitud)
{
	char buffer[10000];
	int retorno;
	retorno = -1;

	if (cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
			if (buffer[strnlen(buffer, sizeof(buffer)) - 1] == '\n')
			{
				buffer[strnlen(buffer, sizeof(buffer)) - 1] = '\0'; //remplaza \n por \0.
			}
			if (strnlen(buffer, sizeof(buffer)) <= longitud && strlen(buffer) != 0)
			{
				strncpy(cadena, buffer, longitud);

				retorno = 0; //corecto
			}
		}
	}
	return retorno;
}
int ValidarCharNumerofloat(char numero[], int tam)
{
	int bandera = 1;
	int auxstr;

	auxstr = strlen(numero);
	int i;

	if ((numero[0] == '-' && auxstr != 1 && tam < auxstr) || (numero[0] == '.' && auxstr != 1)
					|| (isdigit(numero[0]) && (numero[1] == '.' && auxstr > 2)) || (isdigit(numero[0])))
	{

		for (i = 2; i < auxstr; i++)
		{

			if (!(isdigit(numero[i])))

			{

				bandera = 0;
				break;

			}

		}

	}
	else
	{

		bandera = 0;

	}

	return bandera;
}

int ValidarCharNumeroEntero(char numero[], int tam)
{
	int bandera = 1;
	int auxstr;

	auxstr = strlen(numero);
	int i;

	if ((numero[0] == '-' && auxstr != 1 && tam > auxstr) || (isdigit(numero[0]) && tam > auxstr))
	{

		for (i = 1; i < auxstr; i++)
		{

			if (!(isdigit(numero[i])))

			{
				bandera = 0;		//error
				break;

			}
		}
	}
	else
	{
		bandera = 0;		//error

	}

	return bandera;
}
int ValidarCuit(char numero[], int tam)
{
	int bandera = 1;
	int auxstr;

	auxstr = strlen(numero);
	int i;

	if (/*(numero[0] == '-' &&auxstr != 1 && tam > auxstr) || */(isdigit(numero[0]) && tam >= auxstr))
	{

		for (i = 1; i < auxstr; i++)
		{

			if (!(isdigit(numero[i])))

			{
				bandera = 0;		//error
				break;

			}
		}
	}
	else
	{
		bandera = 0;		//error

	}

	return bandera;
}

