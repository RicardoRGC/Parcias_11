/*
 * B.c
 *
 *  Created on: 25 sep. 2021
 *      Author: riky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "B.h"
#include "BValidaciones.h"

void revisarResulado(char mensajeError[], char mensaje[], int resultado)
{
	if (resultado == -1)
	{
		printf(mensajeError);

	}
	else
	{
		printf(mensaje);
	}


}
int getFloat(float* eResultado)
{
	int retorno = -1;
	char buffer[50];
	if (eResultado != NULL && myGets(buffer, sizeof(buffer)) == 0
					&& ValidarCharNumerofloat(buffer, sizeof(buffer)))
	{
		retorno = 0;
		*eResultado = atof(buffer);
	}

	return retorno;
}
int getcuit(double* eResultado)
{
	int retorno = -1;
	char buffer[12];
	if (eResultado != NULL && myGetMinMax(buffer, sizeof(buffer),11) == 0 //modificar longitud de caracter minimo
					&& ValidarCuit(buffer, sizeof(buffer)))
	{
		retorno = 0;
		*eResultado = atof(buffer);

	}

	return retorno;
}
int getInt(int* eResultado)
{
	int retorno = -1;
	char buffer[50];
	if (eResultado != NULL && myGets(buffer, sizeof(buffer)) == 0
					&& ValidarCharNumeroEntero(buffer, sizeof(buffer)))
	{
		retorno = 0;
		*eResultado = atoi(buffer);
	}

	return retorno;
}

int getNumeroCuit(double* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos)
{
	double bufferInt;
	int retorno = -1;
	if (mensaje != NULL && mensajeError != NULL && eResultado != NULL && minimo <= maximo)
	{
		do
		{
			printf(mensaje);
			if (getcuit(&bufferInt) == 0/* && bufferInt >= minimo && bufferInt <= maximo*/)
			{
				*eResultado = bufferInt;

				retorno = 0;
				break;
			}
			else
			{
				printf(mensajeError);

			}
			reintentos--;
		}
		while (reintentos > 0);
	}
	return retorno;
}
int getNumero(int* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos)
{
	int bufferInt;
	int retorno = -1;
	if (mensaje != NULL && mensajeError != NULL && eResultado != NULL && minimo <= maximo)
	{
		do
		{
			printf(mensaje);
			if (getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*eResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf(mensajeError);

			}
			reintentos--;
		}
		while (reintentos > 0);
	}
	return retorno;
}


int getStringDireccion(char* eResultado, int tam, char* mensaje, char* mensajeError, int reintentos)
{
 char bufferChar[50];
	int retorno = -1;

	if (mensaje != NULL && mensajeError != NULL && eResultado != NULL)
	{
		do
		{
			printf(mensaje);
			fflush(stdin);

			if (myGets(bufferChar, 50) == 0 && validarCadenaEspacios(bufferChar))
			{
				strncpy(eResultado, bufferChar, tam);
				retorno = 0;
				break;
			}
			else
			{
				printf(mensajeError);

			}
			reintentos--;
		}
		while (reintentos > 0);
	}

	return retorno;
}
int getString(char* eResultado, int tam, char* mensaje, char* mensajeError, int reintentos)
{
 char bufferChar[50];
	int retorno = -1;

	if (mensaje != NULL && mensajeError != NULL && eResultado != NULL)
	{
		do
		{
			printf(mensaje);
			fflush(stdin);

			if (myGets(bufferChar, 50) == 0 && validarCadena(bufferChar))
			{
				strncpy(eResultado, bufferChar, tam);
				retorno = 0;
				break;
			}
			else
			{
				printf(mensajeError);

			}
			reintentos--;
		}
		while (reintentos > 0);
	}

	return retorno;
}

 
int getNumeroFlotante(float* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos)
{
	float bufferFloat;
	int retorno = -1;
	if (mensaje != NULL && mensajeError != NULL && eResultado != NULL && minimo <= maximo)
	{
		do
		{
			printf(mensaje);
			if (getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{

				*eResultado = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf(mensajeError);

			}
			reintentos--;
		}
		while (reintentos > 0);
	}
	return retorno;
}


