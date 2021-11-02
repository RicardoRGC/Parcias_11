/*
 * Pedidos.c
 *
 *  Created on: 14 oct. 2021
 *      Author: riky
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Clientes.h"
#include "Pedidos.h"

void HardcodePedidos(ePedidos lista[], int len)
{
	ePedidos listaHardcodeada[] = { { 4, 30, PENDIENTE, 4, 5, 5, 300 }, { 1, 40, PENDIENTE, 6, 6, 6,
					400 }, { 4, 50, PENDIENTE, 0, 0, 0, 500 } };
	for (int i = 0; i < 3; i++)
	{
		lista[i] = listaHardcodeada[i];
	}
}
int cargarAuxilarPedidos(ePedidos* listaPedidos, int tamPedidos, eClientes* listaClientes,
				int tamClientes, eAuxiliar* listaAux)
{
	int rtn = -1;

	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].isEmpty == COMPLETADO)
		{
			listaAux[i].contador = listaPedidos[i].PP;
			listaAux[i].id = listaPedidos[i].id;
			rtn = 0;
		}

	}

	return rtn;
}

int sumarContadoresAux(ePedidos* listaPedidos, int tamPedidos, eAuxiliar* listaAux,
				float* auxContadorKilos)
{
	int rtn = -1;
	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].isEmpty == COMPLETADO)
		{
			*auxContadorKilos += listaAux[i].contador;
			rtn = 0;
		}
	}
	return rtn;
}
float cantidadKilos(ePedidos* listaPedidos, int tamPedidos, eClientes* listaClientes,
				int tamClientes)
{
	float retorno = -1;
	float auxContadorKilos;
	float auxContadorClientes;

	auxContadorClientes = 0;
	auxContadorKilos = 0;
	eAuxiliar contadorkilos[tamPedidos];

	if (cargarAuxilarPedidos(listaPedidos, tamPedidos, listaClientes, tamClientes, contadorkilos)
					!= -1
					&& sumarContadoresAux(listaPedidos, tamPedidos, contadorkilos, &auxContadorKilos) != -1
					&& contClientesPedidosCompletadosPP(listaPedidos, tamPedidos, listaClientes, tamClientes,
									&auxContadorClientes) != -1)
	{

		if (auxContadorKilos != 0)
		{
			printf("Cantidad de kilos Totales %.2f kilos\n", auxContadorKilos);

		}
	}

	retorno = auxContadorKilos / auxContadorClientes;

	return retorno;

}
int contClientesPedidosCompletadosPP(ePedidos* listaPedidos, int tamPedidos,
				eClientes* listaClientes, int tamClientes, float* auxContadorClientes)
{
	int rtn = -1;
	int contador = *auxContadorClientes;

	for (int i = 0; i < tamClientes; i++) //clientes
	{
		if (listaClientes[i].isEmpty == CARGADO)
		{
			for (int j = 0; j < tamPedidos; j++)
			{
				if (listaClientes[i].id == listaPedidos[j].idClientes&& (listaPedidos[j].PP > 0)
				&& listaPedidos[j].isEmpty==COMPLETADO)
				{
					contador++;

					rtn = 0; // retornar contador.
					break;
				}
			}

		}
	}
	*auxContadorClientes = contador;

	return rtn;
}
int InicializarArrayPedidos(ePedidos* list, int tam)
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
int CargarPedidos(ePedidos lista[], int tam, int* contadorPedidos, eClientes* listaCliente,
				int tamClientes, int idPedidoCliente)
{
	int retorno = -1;
	int auxContador;
	int kilos;
	auxContador = *contadorPedidos;

	if (BuscarPorEstadoPedido(lista, tam, VACIO) != -1
					&& buscarlistaCargada(listaCliente, tamClientes) == 1)
	{
		if ((getNumero(&kilos, "\ningrese kilos a reciclar", "error", 0, LONG_MAX, REINTENTOS) == 0))
		{
			auxContador++;

			retorno = addPedidos(lista, tam, auxContador, kilos, listaCliente, tamClientes,
							idPedidoCliente);

		}
	}
	else
	{
		printf("no hay cliente o lista llena ");
	}
	*contadorPedidos = auxContador;
	return retorno;
}
int addPedidos(ePedidos* list, int len, int id, int kilos, eClientes* listaCliente, int tamClientes,
				int idPedidoCliente) //sacar clientes
{
	int resultado;
	int espacioVacio;

	resultado = -1;
	espacioVacio = BuscarPorEstadoPedido(list, len, VACIO);

	if ((list != 0) && (len > 0) && (espacioVacio != -1))
	{

		list[espacioVacio].id = id;
		list[espacioVacio].kilos = kilos;
		list[espacioVacio].idClientes = idPedidoCliente;
		list[espacioVacio].isEmpty = PENDIENTE;

		resultado = 0;
	}

	return resultado;
}
int ProcesarResiduos(ePedidos listaPedidos[], int tamPedidos, eClientes* listaCliente,
				int tamClientes, int contadorPedidos)
{
	int opcion;
	int index;
	float HDPE;
	float LDPE;
	float PP;
	int idPPendiente;
	int retorno = -1;
	float kilosTotales;
	if (BuscarPorEstadoPedido(listaPedidos, tamPedidos, PENDIENTE) != -1)
	{

		printPedidosPorEstado(listaPedidos, listaCliente, tamPedidos, tamClientes, PENDIENTE);
		getNumero(&idPPendiente, "ingrese id pedido pendiente", "error", 0, PEDIDOS,
		REINTENTOS);

		index = buscarPorIdPedidos(listaPedidos, tamPedidos, idPPendiente);

		kilosTotales = listaPedidos[index].kilos;

		if (index != -1 && listaPedidos[index].isEmpty == PENDIENTE)
		{
			do
			{
				getNumero(&opcion, "\n1. HDPE \n2. PP \n3. LDPE\n0. SALIR", "error", 0, 3, REINTENTOS);

				switch (opcion)
				{
				case 1:
					if (!getNumeroFlotante(&HDPE, "ingrese cantidad kilos de HDPE ", "Error", 0, kilosTotales,
					REINTENTOS))
					{
						printf("carga correcta");
						kilosTotales = kilosTotales - HDPE;
						listaPedidos[index].HDPE = HDPE;
						listaPedidos[index].isEmpty = COMPLETADO;
						retorno = 0;
					}
					break;
				case 2:
					if (!getNumeroFlotante(&PP, "ingrese cantidad kilos de PP ", "Error", 0, kilosTotales,
					REINTENTOS))
					{
						printf("carga correcta");
						kilosTotales = kilosTotales - PP;
						listaPedidos[index].PP = PP;
						listaPedidos[index].isEmpty = COMPLETADO;
						retorno = 0;
					}
					break;
				case 3:
					if (!getNumeroFlotante(&LDPE, "ingrese cantidad kilos de LDPE ", "Error", 0, kilosTotales,
					REINTENTOS))
					{
						printf("carga correcta");
						kilosTotales = kilosTotales - LDPE;
						listaPedidos[index].LDPE = LDPE;
						listaPedidos[index].isEmpty = COMPLETADO;
						retorno = 0;
					}
					break;
				}

			}
			while (opcion != 0 && kilosTotales != 0);

		}

	}

	return retorno;
}
int buscarPorIdPedidos(ePedidos* listaPedidos, int tamPedidos, int idPedido)
{
	int retorno = -1;

	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].id == idPedido && listaPedidos[i].isEmpty == PENDIENTE)
		{
			retorno = i;
		}

	}
	return retorno;
}
int BuscarPorEstadoPedido(ePedidos* lista, int tam, int estadoDelPedido)
{
	int index;
	index = -1;
	int i;

	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == estadoDelPedido)
		{
			index = i;

			break;
		}
	}

	return index;
}
/*int buscarListaPendientePedidos(ePedidos* lista, int tam)
 {
 int index;
 index = 0;

 int i;

 for (i = 0; i < tam; i++)
 {
 if (lista[i].isEmpty == PENDIENTE) //si la lista esta pendiente devuelve 1
 {
 index = 1;
 break;
 }
 }
 return index;
 }*/
/*int buscarListaCargadaPedidos(ePedidos* lista, int tam)
 {
 int index;
 index = 0;

 int i;

 for (i = 0; i < tam; i++)
 {
 if (lista[i].isEmpty == CARGADO) //si la lista esta cargada devuelve 1
 {
 index = 1;
 break;
 }
 }
 return index;
 }*/
/*int EspacioVacioPedidos(ePedidos* lista, int tam)
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
 }*/
int printPedidos(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos, int tamClientes)
{
	int retorno = -1;
	int espacioCLiente;

	//Cuit del cliente, direcci�n del cliente, cantidad de kilos a recolectar.
	if (listaPedidos != NULL && tamPedidos > 0
					&& BuscarPorEstadoPedido(listaPedidos, tamPedidos, VACIO) != -1)
	{
		printf("                  LISTA DE PEDIDOS\n"
						"----------------------------------------------------------\n"
						"IDPEDIDO    CUIT    DIRECCION    KILOS \n"
						"-----------------------------------------------------------\n");
		for (int i = 0; i < tamPedidos; i++)
		{
			//for (int j = 0; j < tamLocalidad; j++)

			if ((listaPedidos[i].isEmpty == COMPLETADO))
			{
				espacioCLiente = BuscarIgualesPyC(listaPedidos[i], listaClientes, tamPedidos, tamClientes);
				if (espacioCLiente != -1)
				{
					MostrarPedido(listaPedidos[i], listaClientes[espacioCLiente]);
				}
				retorno = 0;
			}
		}
	}
	return retorno;
}
int printPedidosPorEstado(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes, int estado)
{
	int retorno = -1;

	if (listaPedidos != NULL && tamPedidos > 0
					&& BuscarPorEstadoPedido(listaPedidos, tamPedidos, VACIO) != -1)
	{
		if (estado == COMPLETADO)
		{
			printf("                    LISTA PEDIDOS PROCESADOS\n"
							"----------------------------------------------------------\n"
							"IDPEDIDO       CUIT          DIRECCION      DHPE  LDPE  PP                  \n"
							"-----------------------------------------------------------\n");
		}
		else
		{
			printf("              LISTA PEDIDOS PENDIENTES\n"
							"----------------------------------------------------------\n"
							"IDPEDIDO         CUIT          DIRECCION       KILOS                  \n"
							"-----------------------------------------------------------\n");
		}
		for (int i = 0; i < tamPedidos; i++) //pedidos
		{
			if (listaPedidos[i].isEmpty == estado)
			{
				if (mostrarPedidoPendiente_Completado(listaPedidos, listaClientes, tamPedidos, tamClientes,
								i) != -1)
				{
					retorno = 0;
				}

			}

		}
	}
	return retorno;
}
int BuscarClienteEnPedido(ePedidos* listaPedidos, eClientes listaClientes, int tamPedidos,
				int tamClientes)
{
	int retorno = -1;
	for (int i = 0; i < tamPedidos; i++) //pedidos
	{
		if (listaPedidos[i].idClientes == listaClientes.id && listaClientes.isEmpty == CARGADO)
		{
			retorno = i; //devuelve espacio de pedido

		}
	}
	return retorno;
}
int mostrarPedidoPendiente_Completado(ePedidos* listaPedidos, eClientes* listaClientes,
				int tamPedidos, int tamClientes, int espacioEnPedido)
{
	int rtn = -1;

	for (int j = 0; j < tamClientes; j++)
	{

		if (listaPedidos[espacioEnPedido].idClientes
						== listaClientes[j].id&& listaClientes[j].isEmpty==CARGADO
						&&listaPedidos[espacioEnPedido].isEmpty == PENDIENTE)
		{

			MostrarPedido(listaPedidos[espacioEnPedido], listaClientes[j]);
			rtn = 0;
		}

		if (listaClientes[j].id
						== listaPedidos[espacioEnPedido].idClientes&& listaClientes[j].isEmpty==CARGADO
						&&listaPedidos[espacioEnPedido].isEmpty == COMPLETADO)
		{

			MostrarPedidoConPlastico(listaPedidos[espacioEnPedido], listaClientes[j]);
		}

	}

	return rtn;
}
int BuscarIgualesPyC(ePedidos listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes)
{
	int retorno = -1;
	for (int i = 0; i < tamClientes; i++) //clientes
	{
		if (listaClientes[i].id == listaPedidos.idClientes)
		{

			retorno = i;

		}
	}
	return retorno;
}
void MostrarPedido(ePedidos list, eClientes listaclientes)
{ //Cuit del cliente, direcci�n del cliente, cantidad de kilos a recolectar.
	if (listaclientes.cuit != -1 && list.id != -1 && listaclientes.direccion != NULL
					&& list.kilos != -1)
	{
		printf("%-13d %-15.f %-17s %d\n", list.id, listaclientes.cuit, listaclientes.direccion,
						list.kilos);
	}
	else
	{
		printf("error al mostrar");
	}

}
void MostrarPedidoConPlastico(ePedidos list, eClientes listaclientes)
{ //Cuit del cliente, direcci�n del cliente, cantidad de kilos a recolectar.
	if (listaclientes.cuit != -1 && list.id != -1 && listaclientes.direccion != NULL
					&& list.kilos != -1)
	{
		printf("%-13d %-14.f %-15s %-4.f  %-3.f  %0.f \n", list.id, listaclientes.cuit,
						listaclientes.direccion, list.HDPE, list.LDPE, list.PP);
	}
	else
	{
		printf("error al mostrar");
	}

}

