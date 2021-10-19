/*
 * BValidaciones.h
 *
 *  Created on: 12 oct. 2021
 *      Author: riky
 */

#ifndef BVALIDACIONES_H_
#define BVALIDACIONES_H_
/// @param cadena valida una cadena con minimo max
/// @param longitud
/// @param longMin
/// @return
int myGetMinMax(char* cadena, int longitud,int longMin);
/// @param nombre valida una cadena q tega espacios
/// @return
int validarCadenaEspacios(char nombre[]);
/// @param numero valida q el numero tenga 11 caracteres
/// @param tam
/// @return
int ValidarCuit(char numero[], int tam);
/// @param nombre valida si solo son letras
/// @return retorna 1 si son letras, 0 si es incorrecto.
int validarCadena(char* nombre);
/// @param numero corroborar q sea un numero entero.
/// @param tam tamaño del char.
/// @return 0 si es error, 1 si es valido.
int ValidarCharNumeroEntero(char numero[], int tam);
/// @param numero
/// @param tam
/// @return 0 si es error, 1 si es valido.
int ValidarCharNumerofloat(char numero[], int tam);
/// @param cadena
/// @param longitud
/// @return
int myGets(char* cadena, int longitud);

#endif /* BVALIDACIONES_H_ */
