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
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos, int idlocali)
{
	int retorno = -1;

	int contadorPendientes = 0;

	if (listaLocalidad != NULL && tamLocalidad > 0)
	{
		for (int i = 0; i < tamLocalidad; i++)
		{
			if ((listaLocalidad[i].isEmpty == CARGADO && listaLocalidad[i].idLocalidad == idlocali))
			{
				MostrarLocalidad(listaLocalidad[i]); //localidades
				printf("\n------------PEDIDOS PENDIENTES--------------\n");

				contadorPendientes = contadorPedidosPorEstado(listaClientes, tamClientes, listaPedidos,
								tamPedidos, listaLocalidad[i], PENDIENTE); ///sacar index
				retorno = 0;

			}

		}
		printf("TOTAL: %d", contadorPendientes);
	}

	{

	}

	return retorno;
}
int contadorPedidosPorEstado(eClientes* listaClientes, int tamCliente, ePedidos* listaPedidos,
				int tamPedidos, eLocalidad listaLocalidad, int estado)
{
	int contador = 0;

	for (int j = 0; j < tamCliente; j++)
	{
		if (listaClientes[j].idLocalidad
						== listaLocalidad.idLocalidad&& listaClientes[j].isEmpty==CARGADO)
		{
//contador pedidos
			contador = buscaEnPedidosYCuenta(listaClientes[j], tamCliente, listaPedidos, tamPedidos, estado);
		}

	}

	return contador;
}
int buscaEnPedidosYCuenta(eClientes listaClientes, int tamCliente, ePedidos* listaPedidos, int tamPedidos,
				int estado)
{
	int contador = 0;
	for (int k = 0; k < tamPedidos; k++) //pedidos
	{
		if (listaPedidos[k].idClientes == listaClientes.id && listaPedidos[k].isEmpty == estado)
		{
			contador++;
		}
	}
	return contador;
}

int CargarCliente(eClientes lista[], eLocalidad listLocalidad[], int tamLocalidad, int tamCliente,
				int* contadorIdCliente, int* contadorLocalidadID, int limitCarac)
{
	int retorno = -1;
	int auxContadorIdCliente;
	char empresa[limitCarac];
	char direccion[limitCarac];
	int localidad;
	double cuit;
	int opcion;
	int auxContadorIdLocalidad = *contadorLocalidadID;
	auxContadorIdCliente = *contadorIdCliente;

	if (BuscarPorEstadoEnCliente(lista, tamCliente, VACIO) != -1
					&& printLocalidades(listLocalidad, tamLocalidad) != -1)
	{

		if ((getNumero(&opcion, "Ingrese id localidad  o '0' para agregar Localidad", " \nERROR", 0,
						auxContadorIdLocalidad,
						REINTENTOS) != -1))
		{
			if (opcion == 0)
			{
				if (CargarLocalidad(listLocalidad, tamLocalidad, &auxContadorIdLocalidad) == 0)
				{
					*contadorLocalidadID = auxContadorIdLocalidad;

					if (printLocalidades(listLocalidad, tamLocalidad)!=-1
									&&getNumero(&localidad, "Ingrese id de localidad", "\n Error\n", 1,
									auxContadorIdLocalidad,
									REINTENTOS)!=-1)
					{
						printf("cargo localidad\n");
					}
				}

			}
			else
			{
				localidad = opcion;

			}

			if (getString(empresa, limitCarac, "Ingrese Empresa", "\n Error\n", REINTENTOS) == 0
							&& getStringDireccion(direccion, limitCarac, "Ingrese Direccion", "\n Error\n",
							REINTENTOS) == 0
							&& (getNumeroCuit(&cuit, "Ingrese cuit, 11 digitos de corrido", "\n Error\n", 0,
							LONG_MAX, REINTENTOS) == 0))
			{

				if (localidad > 0)
				{

					auxContadorIdCliente++;

					retorno = addEmployee(lista, tamCliente, auxContadorIdCliente, empresa, direccion,
									localidad, cuit);
				}

			}

		}

	}
	*contadorIdCliente = auxContadorIdCliente;
	return retorno;
}

int mostrarclientesConPedidoPendiente(eClientes* listaClientes, eLocalidad* listaLocalidad,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos)
{
	int rtn = -1;

	if (listaClientes != NULL && tamClientes > 0
					&& BuscarPorEstadoPedido(listaPedidos, tamPedidos, PENDIENTE) != -1
					&& listaLocalidad != NULL && tamLocalidad > 0)
	{
		for (int i = 0; i < tamLocalidad; i++)
		{
			if ((listaLocalidad[i].isEmpty == CARGADO
							&& RecorreClientes_cuentaPedidos(listaClientes, listaLocalidad[i], listaPedidos,
											tamLocalidad, tamClientes, tamPedidos) != -1))
			{
				rtn = 0;

			}

		}
	}
	return rtn;
}
int RecorreClientes_cuentaPedidos(eClientes* listaClientes, eLocalidad listaLocalidad,
				ePedidos* listaPedidos, int tamLocalidad, int tamClientes, int tamPedidos)
{
	int rtn = -1;
	int contador = 0;
	for (int j = 0; j < tamClientes; j++)
	{
		if (listaClientes[j].isEmpty == CARGADO
						&& listaLocalidad.idLocalidad == listaClientes[j].idLocalidad)
		{
			contador = buscaEnPedidosYCuenta(listaClientes[j], tamClientes, listaPedidos, tamPedidos,
			PENDIENTE);

			if (contador > 0)
			{
				printf("                \n"
								"----------------------------------------------------------\n"
								"ID   EMPRESA    DIRECCION   LOCALIDAD   CUIT\n"
								"-----------------------------------------------------------\n");
				MostrarEmpleado(listaClientes[j], listaLocalidad);
				printf("cantidad de pedidos pendientes: %d\n", contador);
				contador = 0;
				rtn = 0;

			}

		}
	}
	return rtn;
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
int mostarclientes(eClientes* listaCliente, eLocalidad* listaLocalidad, int tamCliente, int tamLocalidad)
{
	int retorno = -1;
	int localidad;

	if (listaCliente != NULL && tamCliente > 0 && buscarlistaCargada(listaCliente, tamCliente) == 1)
	{

		printf("                  LISTA DE EMPLEADOS\n"
						"----------------------------------------------------------\n"
						"ID   EMPRESA   DIRECCION   localidad   cuit\n"
						"-----------------------------------------------------------\n");

		for (int i = 0; i < tamCliente; i++)
		{
			//for (int j = 0; j < tamLocalidad; j++)

			if ((listaCliente[i].isEmpty == CARGADO))
			{
				localidad = buscarClientesEnLocalidad(listaCliente[i], listaLocalidad, tamLocalidad);
				if (localidad != -1)
				{
					MostrarEmpleado(listaCliente[i], listaLocalidad[localidad]);
				}
				retorno = 0;
			}

		}
	}
	return retorno;
}

int buscarClientesEnLocalidad(eClientes lista, eLocalidad* listaLocalidad, int tamLocalidad)
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
int removeCliente(eClientes* list, int tamClientes, int id, ePedidos* listaPedidos, int tamPedidos)
{
	int retorno = -1;
	int indexABorrar;
	int confirmacion;

	indexABorrar = buscarPorId(list, tamClientes, id);

	if (getNumero(&confirmacion, "ingrese 1 para confirmar 0 para cancelar", "error", 0, 1,
	REINTENTOS) != -1)
	{

		if (confirmacion == 1 && indexABorrar != -1 && list[indexABorrar].isEmpty == CARGADO)
		{
			list[indexABorrar].isEmpty = VACIO;
			if (borrarPedidoPorIdcliente(list[indexABorrar], listaPedidos, tamPedidos) != -1)
			{
				printf("Tambien se borraron sus pedidos");
			}

			//MostrarEmpleado(list[remoIde]);
			retorno = 0;
		}

	}

	return retorno;
}
int borrarPedidoPorIdcliente(eClientes listaCliente, ePedidos* listaPedidos, int tamPedidos)
{
	int rtn = -1;
	for (int i = 0; i < tamPedidos; i++)
	{
		if (listaPedidos[i].idClientes == listaCliente.id)
		{
			listaPedidos[i].isEmpty = VACIO;
			rtn = 0;
		}
	}

	return rtn;
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
	int confirmacion;
	if (buscarlistaCargada(list, tamClientes) == 1)
	{

		if (getNumero(&idModificacion, "\n ingrese id a modificar ", "no se puedo modifcar", 1,
		INT_MAX, 3) != -1
						&& getNumero(&confirmacion, "ingrese 1 para confirmar 0 para cancelar", "error", 0, 1,
						REINTENTOS) != -1 && confirmacion != 0)
		{
			modifIde = buscarPorId(list, tamClientes, idModificacion);
			if (modifIde != -1 && list[modifIde].isEmpty == CARGADO)
			{
				if (getString(empresa, limitCarac, "ingrese nombre de empresa: ", "\n Error\n", REINTENTOS)
								== 0 && getStringDireccion(direccion, limitCarac, "Ingrese Direccion", "\n Error\n",
				REINTENTOS) == 0
								&& (getNumeroCuit(&cuit, "ingrese cuit, 11 digitos de corrido :", "\n Error\n", 0,
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

			}

		}
///-----------------------------------------------
	}

	return retorno;
}

int cargareAuxiliarConListaCliente(eClientes* listaClientes, int tamClientes,
				eAuxiliar* listaAuxiliar)
{
	int retorno = -1;
	if (listaClientes != NULL && tamClientes > 0)
	{

		for (int i = 0; i < tamClientes; i++)
		{
			if (listaClientes[i].isEmpty == CARGADO)
			{
				listaAuxiliar[i].contador2 = 0;
				listaAuxiliar[i].id = listaClientes[i].id;
				retorno = 0;
			}
		}
	}

	return retorno;
}
int ClienteConMasPedidosPorEstado(eClientes* listaClientes, int tamClientes, ePedidos* listaPedidos,
				int tamPedidos, int estado, char* mensaje)
{
	eAuxiliar auxContadorPedidos[tamClientes];
	int retorno;
	int bandera;
	int maximo;
	//int espacioEnCliete;
	retorno = -1;
	bandera = 1;

	if (cargareAuxiliarConListaCliente(listaClientes, tamClientes, auxContadorPedidos) != -1
					&& listaPedidos != NULL && tamPedidos > 0)
	{

		for (int i = 0; i < tamClientes; ++i)
		{
			if (listaClientes[i].isEmpty == CARGADO)
			{
				auxContadorPedidos[i].contador2 = contarPedidosPorClienteAux(listaPedidos, tamPedidos,
								estado, auxContadorPedidos[i]);
			}
			//busca maximo
			if ((auxContadorPedidos[i].contador2 > maximo || bandera)
							&& listaClientes[i].isEmpty == CARGADO)
			{

				maximo = auxContadorPedidos[i].contador2;

				bandera = 0;
			}

		}
		printf(mensaje);

		if (buscaMaximoEnClientes_Muestra(listaClientes, auxContadorPedidos, maximo, tamClientes) != -1)
		{
			retorno = 0;
		}
	}

	return retorno;
}

int buscaMaximoEnClientes_Muestra(eClientes* listaClientes, eAuxiliar* contadorPedidos, int maximo,
				int tamClientes)
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

int contarPedidosPorClienteAux(ePedidos* listaPedidos, int tamPedidos, int estado,
				eAuxiliar listaAuxiliar)
{

	int contador = 0;
	for (int j = 0; j < tamPedidos; ++j)
	{
		if (listaPedidos[j].isEmpty == estado && (listaAuxiliar.id == listaPedidos[j].idClientes))
		{

			contador++;
			//	printf("contador %d\n",listaAuxiliar.contador2);

		}
	}
	return contador; //contador
}

