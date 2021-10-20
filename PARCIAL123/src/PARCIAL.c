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
	int contadorID = 10;
	int contadorLocalidad = 20;
	int contadorPedidos = 1000;
	int remover;
	int opcion;
	float KilosTotalesPP;
	int opcion13;

	int idPedidoCliente;

	eClientes listaClientes[CLIENTES] ;
	eLocalidad listaLocalidades[LOCALIDADES];
	ePedidos listaPedidos[PEDIDOS];
	InicializarArrayLocalidad(listaLocalidades, LOCALIDADES);
	InicializarArray(listaClientes, CLIENTES);
	InicializarArrayPedidos(listaPedidos, PEDIDOS);

HardcodeClientes(listaClientes, CLIENTES);
HardcodeLocalidades(listaLocalidades, LOCALIDADES);
HardcodePedidos(listaPedidos, PEDIDOS);
	do
	{
		getNumero(&opcion, "\n1. ALTAS \n2. MODIFICAR \n3. BAJA\n4. PEDIDOS"
						"\n5. Procesar residuos\n6.IMPRIMIR CLIENTES PENDIENTES "
						"\n7.Imprimir Pedidos pendientes \n8.Imprimir Pedidos procesados"
						"\n9.Ingresar Localidad\n10 Cantidad de kilos de polipropileno reciclado promedio ."
						"\n11 cliente mas pedidos pendientes"
						"\n12 cliente mas pedidos completado"
						"\n13 modificar o eliminar localidad"
						"\n0. Salir\n", "error", 0, 13, REINTENTOS);

		switch (opcion)
		{
		case 1:

			if (CargarCliente(listaClientes, listaLocalidades, LOCALIDADES, CLIENTES, &contadorID,
							&contadorLocalidad, TAMCARACTER) == -1)
			{
				printf("ERROR AL CARGAR");
			}
			else
			{
				mostarclientes(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES);
			}
			break;
		case 2:
			mostarclientes(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES);
			modificarCliente(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES, TAMCARACTER,
							&contadorLocalidad);
			mostarclientes(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES);

			break;
		case 3:
			mostarclientes(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES);
			if (buscarlistaCargada(listaClientes, CLIENTES) == 1)
			{

				getNumero(&remover, "id a eliminar", "error", 0, contadorID, REINTENTOS);
				removeCliente(listaClientes, CLIENTES, remover);
				mostarclientes(listaClientes, listaLocalidades, 3, CLIENTES);
			}
			break;
		case 4:	//cargar pedido
			mostarclientes(listaClientes, listaLocalidades, contadorLocalidad, CLIENTES);
			if (buscarlistaCargada(listaClientes, CLIENTES) == 1
							&& !getNumero(&idPedidoCliente, "ingrese id cliente", "  error  ", 0, contadorID,
											REINTENTOS))
			{

				CargarPedidos(listaPedidos,PEDIDOS, &contadorPedidos, listaClientes, CLIENTES, idPedidoCliente);
				//printPedidos(listaPedidos, listaClientes, 5, CLIENTES);
				printPedidosPendiente(listaPedidos, listaClientes, PEDIDOS, CLIENTES);
			}
			break;
		case 5:	//Procesar residuos

			ProcesarResiduos(listaPedidos, PEDIDOS, listaClientes, CLIENTES,contadorPedidos);

			break;
		case 6:

			mostrarclientesConPedido(listaClientes, listaLocalidades, listaPedidos, LOCALIDADES, CLIENTES,
			PEDIDOS);
			break;
		case 7:
			if (buscarlistaCargada(listaClientes, CLIENTES) == 1)
			{
				printPedidosPendiente(listaPedidos, listaClientes, PEDIDOS, CLIENTES);
			}
			break;
		case 8:
			if (buscarlistaCargada(listaClientes, CLIENTES) == 1)
			{
				printPedidosCompletado(listaPedidos, listaClientes, PEDIDOS, CLIENTES);
			}
			break;
		case 9:
			if (buscarlistaCargada(listaClientes, CLIENTES) == 1)
			{
				printLocalidades(listaLocalidades, LOCALIDADES);
				locadidadPedidosPendientes(listaLocalidades, listaClientes, listaPedidos, LOCALIDADES,
				CLIENTES, PEDIDOS);
			}
			break;
		case 10:

KilosTotalesPP= cantidadKilos(listaPedidos, PEDIDOS, listaClientes, CLIENTES) ;
printf("promedio kilos: %.f",KilosTotalesPP);


			break;
		case 11:
			if(!ClienteMasPedidosPendiente(listaClientes, CLIENTES, listaPedidos, PEDIDOS))
			{
				printf("carga exitosa");
			}

			break;
		case 12:

			ClienteMasPedidosCompletado(listaClientes, CLIENTES, listaPedidos, PEDIDOS);

			break;
		case 13:
do{
	getNumero(&opcion13, "\n1. modificar localidad \n2. eliminar localidad "
							"\n0. Salir\n", "error", 0, 3, REINTENTOS);


	switch(opcion13)
	{
	case 1:
		modificarLocalidad(listaLocalidades, LOCALIDADES);
		printLocalidades(listaLocalidades, LOCALIDADES);
		break;
	case 2:
		removeLocaliad(listaLocalidades, LOCALIDADES);
		printLocalidades(listaLocalidades, LOCALIDADES);
		break;
	}

}while(opcion13!=0);




			break;
		}

	}
	while (opcion != 0);




	return EXIT_SUCCESS;
}
