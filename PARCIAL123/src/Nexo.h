/*
 * Nexo.h
 *
 *  Created on: 13 oct. 2021
 *      Author: riky
 */

#ifndef NEXO_H_
#define NEXO_H_
#define REINTENTOS 3
#define VACIO 0
#define CARGADO 1
#define CLIENTES 100
#define PEDIDOS 1000
#define LOCALIDADES 100

#include "Pedidos.h"

int ClienteMasPedidosPendiente(eClientes* listaClientes,int tamClientes,ePedidos* listaPedidos,int tamPedidos);

/// @param listaLocalidad muestra una localidad y los pedidos pendientes
/// @param listaClientes
/// @param listaPedidos
/// @param tamLocalidad
/// @param tamClientes
/// @param tamPedidos
/// @return
/// muestra pedidos por localidad pendientes
int locadidadPedidosPendientes(eLocalidad* listaLocalidad, eClientes* listaClientes,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos);

/// @param listaClientes listas1 a mostrar
/// @param listaLocalidad lista 2 a mostrar
/// @param listaPedidos  lista 3 a mostar
/// @param tamLocalidad tama�o de lista 2
/// @param tamClientes tam�ano de lista 1
/// @param tamPedidos
/// @return retorna -1 error 0 correcto
int mostrarclientesConPedido(eClientes* listaClientes, eLocalidad* listaLocalidad,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos);
/// @param list lista1 a modificar
/// @param listaLocalidad lista 2 a  modificar
/// @param tamLocalidad tama�o de lista 2
/// @param tamClientes tama�o de lista 1
/// @param limitCarac limites de caracteres
/// @param contadorLocalidad contador de lista 2
/// @return retorna -1 error 0 correcto
int modificarCliente(eClientes* list, eLocalidad* listaLocalidad, int tamLocalidad, int tamClientes,
				int limitCarac, int* contadorLocalidad);
/// @param lista lista 1 a cargar datos
/// @param listLocalidad  lista 2 a cargar
/// @param tamLocalidad tama�o lista 2
/// @param tam tama�o de lista 1
/// @param contadorId  contador de id de lista 1
/// @param contadorLocalidad contador de id lista 2
/// @param limitCarac  limites de caracteres
/// @return retorna -1 error 0 correcto
int CargarCliente(eClientes lista[], eLocalidad listLocalidad[], int tamLocalidad, int tam,
				int* contadorId, int* contadorLocalidad, int limitCarac);
/// @param lista muestra las estruccturas relacionadas
/// @param listaLocalidad lista de estrucctura
/// @param tamLocalidad tama�o de estruccura 2
/// @param largo estrucctura 1
/// @return retorna -1 error 0 correcto
int mostarclientes(eClientes* lista, eLocalidad* listaLocalidad, int tamLocalidad, int largo);
/// @param list lista a mostrar
/// @param listaLocalidad lista a mostrar
void MostrarEmpleado(eClientes list, eLocalidad listaLocalidad);
/// @param lista  lista q va buscar .
/// @param listaLocalidad lista donde se va buscar
/// @param tamLocalidad tama�o de lista donde se va buscar
/// @param largo tama�o de lista q se va buscar
/// @return retorna el indice de la coincidencia
int buscarClientesEnLocalidad(eClientes lista, eLocalidad* listaLocalidad, int tamLocalidad,
				int largo);
/// @param list lista de donde se va elimina el id
/// @param tamClientes tama�o de lista
/// @param id id a eliminar
/// @return
int removeCliente(eClientes* list, int tamClientes, int id);
/// @param list busca en la lista un id cargado
/// @param len tama�o
/// @param id a buscar
/// @return
int buscarPorId(eClientes* list, int len, int id);
#endif /* NEXO_H_ */
