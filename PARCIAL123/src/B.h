/*
 * B.h
 *
 *  Created on: 21 sep. 2021
 *      Author: riky
 */

#ifndef B_H_
#define B_H_

/// @param eResultado
/// @param tam
/// @param mensaje
/// @param mensajeError
/// @param reintentos
/// @return
int getStringDireccion(char* eResultado, int tam, char* mensaje, char* mensajeError, int reintentos);
/// @param eResultado devuelve el resultado numero de 11 caracteres
/// @param mensaje
/// @param mensajeError
/// @param minimo
/// @param maximo
/// @param reintentos
/// @return -1 error 0 correcto
int getNumeroCuit(double* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos);
/// @param eResultado
/// @return
int getcuit(double* eResultado);
/// @param mensajeError
/// @param mensaje
/// @param resultado a corroborar si es corrrecto o no.
void revisarResulado(char mensajeError[], char mensaje[], int resultado);
/// @param eResultado es el flotante q va devolver la funcion.
/// @param mensaje mensaje q recibe el usuario para ingresar
/// @param mensajeError
/// @param minimo rango minimo para el flotante
/// @param maximo rango maximo para el flotante
/// @param reintentos la cantidad de equivocaciones q pueden tener
/// @return retorna -1 error, 0 correcto.
int getNumeroFlotante(float* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos);
/// @param eResultado la cadena q va devolver.
/// @param tamCadena tamaño de la cadena, caracteres
/// @param mensaje al usuario.
/// @param mensajeError si la cadena no es correcta
/// @param reintentos la cantidad de equivocaciones q pueden tener
/// @return retorna -1 error, 0 correcto.
int getString(char* eResultado, int tamCadena, char* mensaje, char* mensajeError, int reintentos);
/// @param eResultado el puntero donde se va guardar el dato.
/// @return -1 si no se pudo guardar ,0 si es correcto
int getFloat(float* eResultado);
/// @param eResultado el puntero donde se va guardar el dato.
/// @return -1 si no se pudo guardar ,0 si es correcto
int getInt(int* eResultado);
/// @param eResultado es el numero entero q va devolver la funcion.
/// @param mensaje  al usuario.
/// @param mensajeError
/// @param minimo  rango minimo del numero entero.
/// @param maximo rango maximo del numero entero.
/// @param reintentos la cantidad de equivocaciones q pueden tener
/// @return retorna -1 error, 0 correcto.
int getNumero(int* eResultado, char* mensaje, char* mensajeError, int minimo, int maximo,
				int reintentos);

#endif /* B_H_ */
