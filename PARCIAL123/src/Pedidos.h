/*
 * Pedidos.h
 *
 *  Created on: 14 oct. 2021
 *      Author: riky
 */

#ifndef PEDIDOS_H_
#define PEDIDOS_H_
#define REINTENTOS 3
#define VACIO 0
#define CARGADO 1
#define PENDIENTE 5
#define COMPLETADO 1
#define TAMCARACTER 50
#define PEDIDOS 1000
#define CLIENTES 100
typedef struct
{
	int idClientes; // comparte con cliente
	int kilos;
	int isEmpty;
	float HDPE;
	float LDPE;
	float PP;
	int idINCREMENTABLE; //personal

} ePedidos;
/// @param lista carga una lista de pedidos
/// @param len
void HardcodePedidos (ePedidos lista[],int len);
/// @param listaPedidos
/// @param tamPedidos
/// @param listaClientes
/// @param tamClientes
/// @return devuelve el promedio de la cantidad de kilos
float cantidadKilos(ePedidos* listaPedidos,int tamPedidos,eClientes* listaClientes, int tamClientes);
/// @param list muestra los pedidos con sus plasticos
/// @param listaclientes
void MostrarPedidoConPlastico(ePedidos list, eClientes listaclientes);
/// @param lista busca en la lista de pedidos si hay pendientes
/// @param tam
/// @return devuelve el index
int buscarListaPendientePedidos(ePedidos* lista, int tam);
/// @param lista busca en la lista cargada en pedido
/// @param tam
/// @return devuelve el index
int buscarListaCargadaPedidos(ePedidos* lista, int tam);
/// @param listaPedidos
/// @param listaClientes
/// @param tamPedidos
/// @param tamClientes
/// @return devulve el espacio en pedido.
int BuscarClienteEnPedido(ePedidos* listaPedidos ,eClientes listaClientes, int tamPedidos, int tamClientes);
/// @param listaPedidos muestra la lista de pedidos completados
/// @param listaClientes
/// @param tamPedidos
/// @param tamClientes
/// @return -1 error
int printPedidosCompletado( ePedidos* listaPedidos,eClientes* listaClientes, int tamPedidos, int tamClientes);
/// @param lista busca en pedidos index de pedido pendiente
/// @param tam
/// @return devuelve el index.
int EspacioPendientePedidos(ePedidos* lista, int tam);
/// @param listaPedidos
/// @param tamPedidos
/// @param listaCliente
/// @param tamClientes
/// @param contadorPedidos
/// @return -1 error y o correcto
int ProcesarResiduos(ePedidos listaPedidos[], int tamPedidos, eClientes* listaCliente,
				int tamClientes,int contadorPedidos);
/// @param listaPedidos busca en la lista de pedidos por id
/// @param tamPedidos
/// @param idPedido
/// @return  retorna index de ippedido
int buscarPorIdPedidos(ePedidos* listaPedidos, int tamPedidos, int idPedido);
/// @param listaPedidos imprime los pedidos pendientes
/// @param listaClientes
/// @param tamPedidos
/// @param tamClientes
/// @return -1 error 0 correcto
int printPedidosPendiente(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes);
/// @param listaPedidos busca igualdad de id de localidad y clientes
/// @param listaClientes
/// @param tamPedidos
/// @param tamClientes
/// @return retorna el index de clientes
int BuscarIgualesPyC(ePedidos listaPedidos, eClientes* listaClientes, int tamPedidos,
				int tamClientes);
/// @param list adhiere los parametros a la lista de pedidos
/// @param len tamaño de lista
/// @param id
/// @param kilos
/// @param listaCliente
/// @param tamClientes
/// @param idPedidoCliente
/// @return -1 error 0 correcto
int addPedidos(ePedidos* list, int len, int id, int kilos,eClientes* listaCliente,
				int tamClientes,int idPedidoCliente);
/// @param lista pide al usuario los datos para cargar la lista de pedidos
/// @param tam
/// @param contadorId
/// @param listaCliente
/// @param tamClientes
/// @param idPedidoCliente
/// @return
int CargarPedidos(ePedidos lista[], int tam, int* contadorId, eClientes* listaCliente,
				int tamClientes, int idPedidoCliente);
/// @param list inicializa la lista de pedidos a 0
/// @param tam
/// @return -1 error o correcto
int InicializarArrayPedidos(ePedidos* list, int tam);
/// @param lista busca espacio vacio en la lista de pedidos
/// @param tam
/// @return retorna index o -1 error
int EspacioVacioPedidos(ePedidos* lista, int tam);
/// @param listaPedidos
/// @param listaClientes
/// @param tamPedidos
/// @param tamClientes
/// @return
int printPedidos(ePedidos* listaPedidos, eClientes* listaClientes, int tamPedidos, int tamClientes);
/// @param list imprime pedidos
/// @param listaclientes
void MostrarPedido(ePedidos list, eClientes listaclientes);
#endif /* PEDIDOS_H_ */
