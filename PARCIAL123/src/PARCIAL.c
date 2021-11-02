/*
 ============================================================================
 Name        : PARCIAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Clientes.h"
#include "Localidad.h"
#include "Nexo.h"
#include "B.h"
#include "Plasticos.h"
#include "Pedidos.h"
#define CLIENTES 100
#define PEDIDOS 1000
#define LOCALIDADES 100
#define TAMCARACTER 50
#define VACIO 0
#define CARGADO 1
#define COMPLETADO 1
#define PENDIENTE 5
#define REINTENTOS 3

int main(void)
{
	setbuf(stdout, NULL);
	int contadorIDCliente = 5;
	int contadorLocalidadID = 8;
	int contadorPedidos = 0;
	int remover;
	int opcion;
	float KilosTotalesPP;
	int opcion13;
	int idlocalidad;
	int idPedidoCliente; ///probar con estatica

	eClientes listaClientes[CLIENTES];
	eLocalidad listaLocalidades[LOCALIDADES];
	ePedidos listaPedidos[PEDIDOS];
	InicializarArrayLocalidad(listaLocalidades, LOCALIDADES);
	InicializarArray(listaClientes, CLIENTES);
	InicializarArrayPedidos(listaPedidos, PEDIDOS);
	HardcodeClientes(listaClientes, CLIENTES);
	HardcodePedidos(listaPedidos, PEDIDOS);

	CargarLocalidadesPorDefecto(listaLocalidades, LOCALIDADES);
	do
	{
		if (getNumero(&opcion, "\n1. ALTAS "
						"\n2. MODIFICAR "
						"\n3. BAJA"
						"\n4. PEDIDOS"
						"\n5. Procesar residuos"
						"\n6.Imprimir Cliente y cantidad de pedidos pendientes "
						"\n7.Imprimir Pedidos pendientes "
						"\n8.Imprimir Pedidos procesados"
						"\n9.Cantidad de pedidos pendientes por Localidad"
						"\n10 Cantidad de kilos de polipropileno reciclado promedio ."
						"\n11 cliente mas pedidos pendientes"
						"\n12 cliente mas pedidos completado"
						"\n13 modificar o eliminar localidad"
						"\n0. Salir\n", "error", 0, 13, REINTENTOS) == -1)
		{
			printf("Error al cargar");

		}

		switch (opcion)
		{
		case 1:

			if (CargarCliente(listaClientes, listaLocalidades, LOCALIDADES, CLIENTES, &contadorIDCliente,
							&contadorLocalidadID, TAMCARACTER) == -1)
			{
				printf("ERROR AL CARGAR");
			}
			else
			{
				mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES);
			}
			break;
		case 2:
			if (BuscarPorEstadoEnCliente(listaClientes, CLIENTES, CARGADO) != -1
							&& mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES)
											!= -1
							&& modificarCliente(listaClientes, listaLocalidades, contadorLocalidadID, CLIENTES,
											TAMCARACTER, &contadorLocalidadID) != -1
							&& mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES)
											!= -1)
			{

				printf("Modificacion exitosa");

			}
			else
			{
				printf("Error al modificar");
			}

			break;
		case 3:

			if (buscarlistaCargada(listaClientes, CLIENTES) == 1
							&& mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES)
											!= -1)
			{
				if (getNumero(&remover, "ingrese id a eliminar\n", "error\n", 0, contadorIDCliente, REINTENTOS)
								!= -1 && removeCliente(listaClientes, CLIENTES, remover, listaPedidos, PEDIDOS) != -1
								&& mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES) != -1)
				{

					printf("Borrado exitoso");

				}
				else
				{

					printf("no se pudo remover el cliente");
				}

			}
			else
			{
				printf("lista vacia");
			}
			break;
		case 4:	//cargar pedido

			if (mostarclientes(listaClientes, listaLocalidades, CLIENTES,LOCALIDADES) != -1
							&& buscarlistaCargada(listaClientes, CLIENTES) == 1
							&& !getNumero(&idPedidoCliente, "ingrese id cliente", " ERROR Id Incorrecto \n ", 0,
											contadorIDCliente,
											REINTENTOS))
			{
				if (CargarPedidos(listaPedidos, PEDIDOS, &contadorPedidos, listaClientes, CLIENTES,
								idPedidoCliente) != -1)
				{
					//printPedidosPendiente(listaPedidos, listaClientes, PEDIDOS, CLIENTES);
				}
				else
				{
					printf("no se pudo cargar el pedido");
				}

			}
			break;
		case 5:	//Procesar residuos
			if (BuscarPorEstadoPedido(listaPedidos, PEDIDOS, PENDIENTE) != -1)
			{
				ProcesarResiduos(listaPedidos, PEDIDOS, listaClientes, CLIENTES, contadorPedidos);
			}
			else
			{
				printf("No hay Pedidos Pendientes\n");

			}

			break;
		case 6:
			if (BuscarPorEstadoPedido(listaPedidos, PEDIDOS, PENDIENTE) != -1)
			{
				mostrarclientesConPedidoPendiente(listaClientes, listaLocalidades, listaPedidos,
				LOCALIDADES, CLIENTES,
				PEDIDOS);
			}
			else
			{
				printf("No hay Pedidos Pendientes\n");

			}
			break;
		case 7:
			if (BuscarPorEstadoPedido(listaPedidos, PEDIDOS, PENDIENTE) != -1)
			{
				printPedidosPorEstado(listaPedidos, listaClientes, PEDIDOS, CLIENTES, PENDIENTE);
				//printPedidosPendiente(listaPedidos, listaClientes, PEDIDOS, CLIENTES);
			}
			else
			{
				printf("no hay pedido pendiente para mostrar");
			}

			break;
		case 8:
			if (BuscarPorEstadoPedido(listaPedidos, PEDIDOS, COMPLETADO) != -1)
			{
				printPedidosPorEstado(listaPedidos, listaClientes, PEDIDOS, CLIENTES, COMPLETADO);
			}
			else
			{
				printf("no hay pedidos completados para mostrar");
			}
			break;
		case 9:
			if (BuscarPorEstadoPedido(listaPedidos, PEDIDOS, PENDIENTE) != -1
							&& printLocalidades(listaLocalidades, LOCALIDADES) != -1
							&& getNumero(&idlocalidad, "ingrese id localidad", "error", 1, contadorLocalidadID, REINTENTOS)
											!= -1)
			{

				printf("                  LISTA DE LOCALIDADES\n"
								"----------------------------------------------------------\n"
								"ID    localidad   \n"
								"-----------------------------------------------------------\n");

			}
			if (locadidadPedidosPendientes(listaLocalidades, listaClientes, listaPedidos, LOCALIDADES,
			CLIENTES, PEDIDOS, idlocalidad) == -1)
			{
				printf("error al cargar");
			}
			break;
		case 10:

			KilosTotalesPP = cantidadKilos(listaPedidos, PEDIDOS, listaClientes, CLIENTES);
			if (KilosTotalesPP > 0)
			{
				printf("promedio kilos: %.2f", KilosTotalesPP);
			}
			else
			{
				printf("no hay q mostrar\n");
			}

			break;
		case 11:
			if (!ClienteConMasPedidosPorEstado(listaClientes, CLIENTES, listaPedidos, PEDIDOS, PENDIENTE,
							"cliente con mas pedidos Pendientes \n"))
			{
				printf("carga exitosa");
			}
			else
			{
				printf("nada q mostrar");
			}

			break;
		case 12:

			if (!ClienteConMasPedidosPorEstado(listaClientes, CLIENTES, listaPedidos, PEDIDOS, COMPLETADO,
							"cliente con mas pedidos completados\n"))
			{
				printf("carga exitosa");
			}
			else
			{
				printf("nada q mostrar");
			}

			break;
		case 13:
			do
			{
				getNumero(&opcion13, "\n1. modificar localidad \n2. eliminar localidad "
								"\n0. Salir\n", "error", 0, 3, REINTENTOS);

				switch (opcion13)
				{
				case 1:
					if (modificarLocalidad(listaLocalidades, LOCALIDADES) != -1
									&& printLocalidades(listaLocalidades, LOCALIDADES) != -1)
					{
						printf("modificacion exitosa");
					}
					else
					{
						printf("error al modificar");
					}

					break;
				case 2:
					if (removeLocaliad(listaLocalidades, LOCALIDADES) != -1
									&& printLocalidades(listaLocalidades, LOCALIDADES) != -1)
					{
						printf("borrado exitoso");
					}
					else
					{
						printf("error al borrar");
					}

					break;
				}

			}
			while (opcion13 != 0);

			break;
		}

	}
	while (opcion != 0);

	return EXIT_SUCCESS;
}
