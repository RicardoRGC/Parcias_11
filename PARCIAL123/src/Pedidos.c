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
#include "auxiliar.h"

void HardcodePedidos(ePedidos lista[], int len)
{
	ePedidos listaHardcodeada[] = { { 1, 30, PENDIENTE, 4, 5, 5, 300 }, { 3, 40, COMPLETADO, 6, 6, 6,
					400 }, { 1, 50, PENDIENTE, 0, 0, 0, 500 } };
	for (int i = 0; i < 3; i++)
	{
		lista[i] = listaHardcodeada[i];
	}
}
float cantidadKilos(ePedidos* listaPedidos, int tamPedidos, eClientes* listaClientes,
				int tamClientes)
{
	float retorno = -1;
	float auxContadorKilos;
	int auxContadorClientes;

	auxContadorClientes = 0;
	auxContadorKilos = 0;
	eAuxiliar contadorkilos[tamPedidos];
//eAuxiliar contadorClientes[tamClientes];

	for (int i = 0; i < tamPedidos; i++)
	{

		{
			contadorkilos[i].contador = listaPedidos[i].PP;
			contadorkilos[i].id = listaPedidos[i].idINCREMENTABLE;
		}

	}
	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].isEmpty == COMPLETADO)
		{
			auxContadorKilos += contadorkilos[i].contador;

		}
	}


	for (int i = 0; i < tamClientes; i++) //clientes
	{
		if (listaClientes[i].isEmpty == CARGADO)
		{
			for (int j = 0; j < tamPedidos; j++) //pedidos
			{

				if (listaClientes[i].id == listaPedidos[j].idClientes && (listaPedidos[j].PP > 0)
								&& listaPedidos[j].isEmpty==COMPLETADO)
				{
					auxContadorClientes++;
					break;
				}


			}

		}
	}
	printf("clientes total %d \n", auxContadorClientes);

	printf("Cantidad de kilos Totales %.f kilos\n", auxContadorKilos);

	retorno = auxContadorKilos / auxContadorClientes;

	return retorno;

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

	if (EspacioVacioPedidos(lista, tam) != -1 && buscarlistaCargada(listaCliente, tamClientes) == 1)
	{
		if ((getNumero(&kilos, "kilos", "error", 0, LONG_MAX, REINTENTOS) == 0))
		{
			auxContador++;

			retorno = addPedidos(lista, tam, auxContador, kilos, listaCliente, tamClientes,
							idPedidoCliente);

		}
		else
		{
			printf("\n supero los intentos, No pudo cargar\n");
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
	espacioVacio = EspacioVacioPedidos(list, len);

	if ((list != 0) && (len > 0) && (espacioVacio != -1))
	{

		list[espacioVacio].idINCREMENTABLE = id;
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
	int index;
	float HDPE;
	float LDPE;
	float PP;
	int idPPendiente;
	int retorno = -1;
	if (EspacioPendientePedidos(listaPedidos, tamPedidos) != -1)
	{
		printPedidosPendiente(listaPedidos, listaCliente, PEDIDOS, CLIENTES);
		getNumero(&idPPendiente, "ingrese id pedido pendiente", "error", 0, contadorPedidos,
		REINTENTOS);

		index = buscarPorIdPedidos(listaPedidos, tamPedidos, idPPendiente);

		if (index != -1 && listaPedidos[index].isEmpty == PENDIENTE)
		{

			if (!getNumeroFlotante(&HDPE, "ingrese cantidad kilos de HDPE ", "Error", 0, LONG_MAX,
			REINTENTOS) && !getNumeroFlotante(&PP, "ingrese cantidad kilos de PP ", "Error", 0, LONG_MAX,
			REINTENTOS)
							&& !getNumeroFlotante(&LDPE, "ingrese cantidad kilos de LDPE ", "Error", 0, LONG_MAX,
							REINTENTOS) && (HDPE + LDPE + PP <= listaPedidos[index].kilos))
			{

				listaPedidos[index].HDPE = HDPE;
				listaPedidos[index].LDPE = LDPE;
				listaPedidos[index].PP = PP;
				listaPedidos[index].isEmpty = COMPLETADO;
				printf("carga correcta");
				retorno = 0;

			}
			else
			{
				printf("supero los kilos ");
			}

		}
		else
		{
			printf("Error");
		}

	}

	return retorno;
}
int buscarPorIdPedidos(ePedidos* listaPedidos, int tamPedidos, int idPedido)
{
	int retorno = -1;

	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].idINCREMENTABLE == idPedido && listaPedidos[i].isEmpty == PENDIENTE)
		{
			retorno = i;
		}

	}
	return retorno;
}
int EspacioPendientePedidos(ePedidos* lista, int tam)
{
	int index;
	index = -1;

	int i;

	for (i = 0; i < tam; i++)
	{
		if (lista[i].isEmpty == PENDIENTE)
		{
			index = i;

			break;
		}
	}

	return index;
}
int buscarListaPendientePedidos(ePedidos* lista, int tam)
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
}
int buscarListaCargadaPedidos(ePedidos* lista, int tam)
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
}
int EspacioVacioPedidos(ePedidos* lista, int tam)
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
int printPedidos(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos, int tamClientes)
{
	int retorno = -1;
	int espacioCLiente;

	//Cuit del cliente, dirección del cliente, cantidad de kilos a recolectar.
	if (listaPedidos != NULL && tamPedidos > 0 && EspacioVacioPedidos(listaPedidos, tamPedidos) != -1)
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
int printPedidosCompletado(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes)
{
	int retorno = -1;

	if (listaPedidos != NULL && tamPedidos > 0 && EspacioVacioPedidos(listaPedidos, tamPedidos) != -1)
	{
		printf("              LISTA PEDIDOS COMPLETADOS\n"
						"----------------------------------------------------------\n"
						"IDPEDIDO       CUIT          DIRECCION    DHPE  LDPE  PP                  \n"
						"-----------------------------------------------------------\n");
		for (int i = 0; i < tamPedidos; i++) //pedidos
		{
			if (listaPedidos[i].isEmpty == COMPLETADO)
			{
				for (int j = 0; j < tamClientes; j++)
				{

					if (listaClientes[j].id == listaPedidos[i].idClientes&& listaClientes[j].isEmpty==CARGADO)
					{

						MostrarPedidoConPlastico(listaPedidos[i], listaClientes[j]);
					}

				}

			}
			//espacioCLiente = BuscarIgualesPyC(listaPedidos[i], listaClientes, tamPedidos, tamClientes);

		}
	}
	return retorno;
}
int printPedidosPendiente(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes)
{
	int retorno = -1;
	//int espacioCLiente;

	if (listaPedidos != NULL && tamPedidos > 0)
	{
		printf("              LISTA PEDIDOS PENDIENTES\n"
						"----------------------------------------------------------\n"
						"IDPEDIDO         CUIT          DIRECCION       KILOS                  \n"
						"-----------------------------------------------------------\n");
		for (int i = 0; i < tamPedidos; i++) //pedidos
		{
			if (listaPedidos[i].isEmpty == PENDIENTE)
			{
				for (int j = 0; j < tamClientes; j++)
				{
					if (listaPedidos[i].idClientes == listaClientes[j].id&& listaClientes[j].isEmpty==CARGADO)
					{

						MostrarPedido(listaPedidos[i], listaClientes[j]);
						retorno = 0;
					}
				}
			}

			//espacioCLiente = BuscarIgualesPyC(listaPedidos[i], listaClientes, tamPedidos, tamClientes);
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
		if (listaPedidos[i].idClientes == listaClientes.id)
		{
			retorno = i; //devuelve espacio de pedido
		}
	}
	return retorno;
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
{ //Cuit del cliente, dirección del cliente, cantidad de kilos a recolectar.
	if (listaclientes.cuit != -1 && list.idINCREMENTABLE != -1 && listaclientes.direccion != NULL
					&& list.kilos != -1)
	{
		printf("%-13d %-15.f %-17s %d\n", list.idINCREMENTABLE, listaclientes.cuit,
						listaclientes.direccion, list.kilos);
	}
	else
	{
		printf("error al mostrar");
	}

}
void MostrarPedidoConPlastico(ePedidos list, eClientes listaclientes)
{ //Cuit del cliente, dirección del cliente, cantidad de kilos a recolectar.
	if (listaclientes.cuit != -1 && list.idINCREMENTABLE != -1 && listaclientes.direccion != NULL
					&& list.kilos != -1)
	{
		printf("%-13d %-15.f %-10s %0.f  %0.f  %0.f \n", list.idINCREMENTABLE, listaclientes.cuit,
						listaclientes.direccion, list.HDPE, list.LDPE, list.PP);
	}
	else
	{
		printf("error al mostrar");
	}

}

