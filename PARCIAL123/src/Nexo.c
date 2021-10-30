/*
 * Nexo.c
 *
 *  Created on: 13 oct. 2021
 *      Author: riky
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Clientes.h"
#include "Localidad.h"
#include "Nexo.h"
#include "Pedidos.h"

/*int localidadEnClientes(eClientes* listaClientes, eLocalidad listaLocalidad, int tamLocalidad,
 int tamclientes)
 {
 int retorno = -1;
 for (int i = 0; i < tamclientes; i++)
 {
 if (listaClientes[i].idLocalidad == listaLocalidad.idLocalidad)
 {
 retorno = i;
 }
 }
 return retorno;
 }*/
int locadidadPedidosPendientes(eLocalidad* listaLocalidad, eClientes* listaClientes,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos)
{
	int retorno = -1;
	int idlocali;
	int contadorPendientes = 0;

	getNumero(&idlocali, "ingrese id localidad", "error", 1, LOCALIDADES, REINTENTOS);

	printf("                  LISTA DE LOCALIDADES\n"
					"----------------------------------------------------------\n"
					"ID    localidad   \n"
					"-----------------------------------------------------------\n");

	if (listaLocalidad != NULL && tamLocalidad > 0)
	{
		for (int i = 0; i < tamLocalidad; i++)
		{
			if ((listaLocalidad[i].isEmpty == CARGADO && listaLocalidad[i].idLocalidad == idlocali))
			{
				MostrarLocalidad(listaLocalidad[i]); //localidades
				printf("\n------------PEDIDOS PENDIENTES--------------\n");

				contadorPedidosPendiente(listaClientes, tamClientes, listaPedidos, tamPedidos,
								listaLocalidad, i, &contadorPendientes);


			}

		}
		printf("TOTAL: %d", contadorPendientes);
	}

	{

	}

	return retorno;
}
int contadorPedidosPendiente(eClientes* listaClientes, int tamCliente, ePedidos* listaPedidos,
				int tamPedidos, eLocalidad* listaLocalidad, int espacioLocalidad, int* contadorPendientes)
{
	int retorno = -1;
	int contador = *contadorPendientes;

	for (int j = 0; j < tamCliente; j++)
	{
		if (listaClientes[j].idLocalidad
						== listaLocalidad[espacioLocalidad].idLocalidad&& listaClientes[j].isEmpty==CARGADO)
		{

			for (int k = 0; k < tamPedidos; k++) //pedidos
			{
				if (listaPedidos[k].idClientes == listaClientes[j].id&& listaPedidos[k].isEmpty==PENDIENTE)
				{
					contador++;

					retorno = 0;

				}
			}

		}
		*contadorPendientes = contador;
	}
	return retorno;
}
int CargarCliente(eClientes lista[], eLocalidad listLocalidad[], int tamLocalidad, int tam,
				int* contadorId, int* contadorLocalidad, int limitCarac)
{
	int retorno = -1;
	int auxContador;
	char empresa[limitCarac];
	char direccion[limitCarac];
	int localidad;
	double cuit;
	int opcion;
	int auxLocalidad = *contadorLocalidad;
	auxContador = *contadorId;

	if (BuscarPorEstadoEnCliente(lista, tam, VACIO) != -1)
	{
		printLocalidades(listLocalidad, tamLocalidad);
		if ((getNumero(&opcion, "Ingrese id localidad  o '0' para agregar Localidad", " \nERROR", 0,
						auxLocalidad,
						REINTENTOS) == 0))
		{
			if (opcion == 0)
			{
				if (CargarLocalidad(listLocalidad, tamLocalidad, &auxLocalidad) == 0)
				{

					*contadorLocalidad = auxLocalidad;
					printLocalidades(listLocalidad, tamLocalidad);

					if (!getNumero(&localidad, "Ingrese id de localidad", "\n Error\n", 1, auxLocalidad,
					REINTENTOS))
					{
						printf("cargo localidad\n");
					}
				}

			}
			else
			{
				localidad = opcion;

			}

		}
		if (getString(empresa, limitCarac, "Ingrese Empresa", "\n Error\n", REINTENTOS) == 0
						&& getStringDireccion(direccion, limitCarac, "Ingrese Direccion", "\n Error\n",
						REINTENTOS) == 0
						&& (getNumeroCuit(&cuit, "Ingrese cuit, 11 digitos de corrido", "\n Error\n", 0,
						LONG_MAX, REINTENTOS) == 0))
		{

			if (localidad > 0)
			{

				auxContador++;

				retorno = addEmployee(lista, tam, auxContador, empresa, direccion, localidad, cuit);
			}

		}
		else
		{
			printf("\n Supero los intentos, No pudo cargar\n");

		}
	}
	*contadorId = auxContador;
	return retorno;
}
int mostrarclientesConPedidoPendiente(eClientes* listaClientes, eLocalidad* listaLocalidad,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos)
{
	int retorno = -1;
	int localidad;

	if (listaClientes != NULL && tamClientes > 0
					&& BuscarPorEstadoPedido(listaPedidos, tamPedidos, PENDIENTE) != -1)
	{

		for (int i = 0; i < tamClientes; i++) //clientes

		{
			if (listaClientes[i].isEmpty == CARGADO)
			{
				int espacioEnPEdido;
				espacioEnPEdido = BuscarClienteEnPedido(listaPedidos, listaClientes[i], tamPedidos,
								tamClientes);

				if (espacioEnPEdido != -1 && listaPedidos[espacioEnPEdido].isEmpty == PENDIENTE)
				{

					printf("                 CLIENTE\n"
									"----------------------------------------------------------\n"
									"ID   EMPRESA    DIRECCION   LOCALIDAD   CUIT\n"
									"-----------------------------------------------------------\n");

					localidad = buscarClientesEnLocalidad(listaClientes[i], listaLocalidad, tamLocalidad,
									tamClientes);

					if (localidad != -1)
					{

						MostrarEmpleado(listaClientes[i], listaLocalidad[localidad]); // listaclientes y localidad(lugar q coincide)
						{

							printf("PEDIDO PENDIENTES\n"
											"----------------------------------------------------------\n"
											"IDPEDIDO         CUIT          DIRECCION       KILOS                  \n"
											"-----------------------------------------------------------\n");

////
							buscarClienteEnPedido_Mostrar(listaPedidos, tamPedidos, listaClientes, tamClientes,
											i);

						}
						retorno = 0;
					}
				}

			}
		}
	}
	return retorno;
}
int buscarClienteEnPedido_Mostrar(ePedidos* listaPedidos, int tamPedidos, eClientes* listaClientes,
				int tamClientes, int espacioEnCLiente)
{
	int rtn = -1;

	for (int j = 0; j < tamPedidos; j++) //pedidos
	{
		if (listaClientes[espacioEnCLiente].id
						== listaPedidos[j].idClientes&& listaClientes[espacioEnCLiente].isEmpty==CARGADO
						&& listaPedidos[j].isEmpty==PENDIENTE)
		{
			//mostrar
			MostrarPedido(listaPedidos[j], listaClientes[espacioEnCLiente]);
		}
	}
	return rtn;
}
int mostarclientes(eClientes* lista, eLocalidad* listaLocalidad, int tamLocalidad, int largo)
{
	int retorno = -1;
	int localidad;

	if (lista != NULL && largo > 0 && buscarlistaCargada(lista, largo) == 1)
	{
		printf("                  LISTA DE EMPLEADOS\n"
						"----------------------------------------------------------\n"
						"ID   EMPRESA   DIRECCION   localidad   cuit\n"
						"-----------------------------------------------------------\n");

		for (int i = 0; i < largo; i++)
		{
			//for (int j = 0; j < tamLocalidad; j++)

			if ((lista[i].isEmpty == CARGADO))
			{
				localidad = buscarClientesEnLocalidad(lista[i], listaLocalidad, tamLocalidad, largo);
				if (localidad != -1)
				{
					MostrarEmpleado(lista[i], listaLocalidad[localidad]);
				}
				retorno = 0;
			}

		}
	}
	return retorno;
}

int buscarClientesEnLocalidad(eClientes lista, eLocalidad* listaLocalidad, int tamLocalidad,
				int largo)
{
	int retorno = -1;
	for (int i = 0; i < tamLocalidad; i++)
	{
		if (listaLocalidad[i].idLocalidad == lista.idLocalidad)
		{
			retorno = i;
		}
	}
	return retorno;
}

void MostrarEmpleado(eClientes list, eLocalidad listaLocalidad)
{
	printf("%-5d %-10s %-10s %-10s %0.f \n", list.id, list.empresa, list.direccion,
					listaLocalidad.descripcion, list.cuit);

}
int removeCliente(eClientes* list, int tamClientes, int id)
{
	int retorno = -1;
	int remoIde;
	int confirmacion;
	printf("entro");
	remoIde = buscarPorId(list, tamClientes, id);
	if (getNumero(&confirmacion, "ingrese 1 para confirmar 0 para cancelar", "error", 0, 1,
					REINTENTOS) != -1)
	{

		if (confirmacion == 1)
		{
			printf("entro");

			if (remoIde != -1 && list[remoIde].isEmpty == CARGADO)
			{
				list[remoIde].isEmpty = VACIO;
				//MostrarEmpleado(list[remoIde]);
				retorno = 0;
			}
			else
			{
				printf("Error no se encontro id");
			}
		}
	}

	return retorno;
}

int buscarPorId(eClientes* list, int len, int id)
{
	int retorno = -1;

	for (int i = 0; i < len; i++)
	{
		if (list[i].id == id && list[i].isEmpty == CARGADO)
		{
			retorno = i;
		}

	}

	return retorno;
}
int modificarCliente(eClientes* list, eLocalidad* listaLocalidad, int tamLocalidad, int tamClientes,
				int limitCarac, int* contadorLocalidad)
{
	int opcion;
	char empresa[50];
	char direccion[50];
	int localidad;
	double cuit;
	int retorno = -1;
	int modifIde;
	int idModificacion;
	if (buscarlistaCargada(list, tamClientes) == 1)
	{

		if (getNumero(&idModificacion, "\n ingrese id a modificar ", "no se puedo modifcar", 1,
		INT_MAX, 3) != 0)
		{
			printf("\n"
							"supero el maximo de intentos");
		}
		else
		{
			/*modificarCliente(list, listaLocalidad, LOCALIDADES, CLIENTES, idModificacion, TAMCARACTER,
			 &contadorLocalidad);*/
			modifIde = buscarPorId(list, tamClientes, idModificacion);
			if (modifIde != -1 && list[modifIde].isEmpty == CARGADO)
			{
				if (getString(empresa, limitCarac, "empresa", "\n Error\n", REINTENTOS) == 0
								&& getString(direccion, limitCarac, "direccion", "\n Error\n", REINTENTOS) == 0
								&& (getNumeroCuit(&cuit, "ingrese cuit, 11 digitos de corrido", "\n Error\n", 0,
								LONG_MAX, REINTENTOS) == 0))
				{
					printLocalidades(listaLocalidad, tamLocalidad);
					if (getNumero(&opcion, "ingrese id localidad  o 0 para agregar", "ERROR", 0, 1000,
					REINTENTOS) == 0)
					{
						if (opcion == 0)
						{
							CargarLocalidad(listaLocalidad, tamLocalidad, contadorLocalidad);
							printLocalidades(listaLocalidad, tamLocalidad);
							getNumero(&localidad, "ingrese id localidad", "\n Error\n", 1, 10000, REINTENTOS);

						}
						else
						{

							localidad = opcion;
						}

					}
					strcpy(list[modifIde].empresa, empresa);
					strcpy(list[modifIde].direccion, direccion);
					list[modifIde].idLocalidad = localidad;
					list[modifIde].cuit = cuit;
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

int cargareAuxiliarConListaCliente(eClientes* listaClientes, int tamClientes, eAuxiliar* listaAuxiliar)
{
	int retorno = -1;

	for (int i = 0; i < tamClientes; i++)
	{
		if (listaClientes[i].isEmpty == CARGADO)
		{
			listaAuxiliar[i].contador2 = 0;
			listaAuxiliar[i].id = listaClientes[i].id;
			retorno = 0;
		}
	}

	return retorno;
}
int ClienteConMasPedidosPorEstado(eClientes* listaClientes, int tamClientes, ePedidos* listaPedidos,
				int tamPedidos, int estado, char* mensaje)
{
	eAuxiliar contadorPedidos[tamClientes];
	int retorno;

	int bandera;
	int maximo;
	//int espacioEnCliete;
	retorno = -1;
	bandera = 1;

	cargareAuxiliarConListaCliente(listaClientes, tamClientes, contadorPedidos);


	for (int i = 0; i < tamClientes; ++i)
	{
		if (listaClientes[i].isEmpty == CARGADO)
		{
			contarPedidosPorCliente(listaPedidos, tamPedidos, estado, contadorPedidos, i);

		}
		//busca maximo
		if ((contadorPedidos[i].contador2 > maximo || bandera) && listaClientes[i].isEmpty == CARGADO)
		{

			maximo = contadorPedidos[i].contador2;

			bandera = 0;
		}

	}
	printf(mensaje);
	//// funcion
	///
	if( buscaMaximoEnClientes_Muestra(listaClientes, contadorPedidos, maximo, tamClientes)!=-1)
	{
		retorno=0;
	}



	return retorno;
}

int buscaMaximoEnClientes_Muestra(eClientes* listaClientes,eAuxiliar* contadorPedidos,int maximo ,int tamClientes )
{
	int rtn = -1;
	for (int i = 0; i < tamClientes; ++i)
	{
		if (maximo == contadorPedidos[i].contador2 && listaClientes[i].isEmpty == CARGADO
						&& maximo != 0)
		{
			for (int j = 0; j < tamClientes; j++)
			{
				if (contadorPedidos[i].id == listaClientes[j].id)
				{
					printf("%s \n", listaClientes[i].empresa);
					rtn = 0;
					break;
				}
			}

		}

	}
	return rtn;
}

int contarPedidosPorCliente(ePedidos* listaPedidos, int tamPedidos, int estado, eAuxiliar* listaAuxiliar,
				int espacioEnPedido)
{
	int retorno = -1;
	for (int j = 0; j < tamPedidos; ++j)
	{
		if (listaPedidos[j].isEmpty == estado
						&& (listaAuxiliar[espacioEnPedido].id == listaPedidos[j].idClientes))
		{
			listaAuxiliar[espacioEnPedido].contador2++;
			//	printf("contador %d\n",listaAuxiliar.contador2);
			retorno = 0;

		}
	}
	return retorno;
}

