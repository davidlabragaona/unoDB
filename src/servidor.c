/*
*   Servidor que escucha en el puerto PUERTO_TCP (include/general.h)
*
*   unoDb :
*		Jose Julian Buda
*		David Labra Gaona
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h> 
#include "../include/servidor.h"
#include "../include/general.h"
#include "../include/tablas.h"
#include "../include/parser.h"

int main(int argc, char *argv[])
{
	int socket_desc, client_sock, c;
	struct sockaddr_in server, client;
        pthread_t thread_id;
        argumentos_thread_conexion argumentos_de_thread_conexion;

        inicializaTodo();//esto carga en memoria la definicion de tablas y los datos de esas tablas
	// Creo el socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1) {
		printf("No se pudo crear el socket");
		return 1;
 	}
	// Configuro la conexion a establecer
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PUERTO_TCP);
	// hago el "bindeo"
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("No se pudo hacer el bind");
		return 2;
	}
	// Listen
	listen(socket_desc, 5);
        bannerDeBienvenida();	c = sizeof(struct sockaddr_in);
	c = sizeof(struct sockaddr_in);
	while((argumentos_de_thread_conexion.socket_asociado = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
                /*extraigo la IP del cliente*/
                inet_ntop(AF_INET, &(client.sin_addr), argumentos_de_thread_conexion.ip_cliente, INET_ADDRSTRLEN);
                printf("Cliente %s conectado\n", argumentos_de_thread_conexion.ip_cliente);
                /* creo el thread y le paso al mismo la funciona handler y los argumentos*/ 
        	if(pthread_create( &thread_id, NULL,  recibeConexion, (void*) &argumentos_de_thread_conexion) < 0) {
			perror("Mmm...No se pudo crear el thread");
			return 3;
		}
	}
	if (argumentos_de_thread_conexion.socket_asociado < 0) {
		perror("No se acepto la conexion...");
		return 4;
	}
	return 0;
}

void bajarServidor(){
   fflush(stdout);
   //con este while espero que terminen todos los hijos
   while(cantidad_de_clientes){
     printf("\n\nEsperando que terminen clientes...");
     wait();
     cantidad_de_clientes--;
   }
   printf("\n\n\t\tAhora si, terminaron todos los clientes\n\n\n");
   exit(1);
}

void bannerDeBienvenida(){
     //Banner de Bienvenida al arrancar servidor
     printf("Bienvenido a unoDb Server\n");
     printf("Server version: %s\n\n",VERSION);
}

void *recibeConexion(void *argumentos){
        /*recibo argumentos del thread*/
        argumentos_thread_conexion argumentos_de_thread=*(argumentos_thread_conexion*)argumentos;
        int sock,read_size,n;
	char respuesta_a_cliente[2000];
        char consulta[MAX_LONG_CONS];

        sock= argumentos_de_thread.socket_asociado;
	while( (read_size = recv(sock, consulta, MAX_LONG_CONS, 0)) > 0 )  {
                printf("Comando recibido desde cliente %s : %s\n",argumentos_de_thread.ip_cliente,consulta);

                // el parser chequear_consulta() debera devolver un (char *) , no modificar
                //una variable global como lo hacia en la version 1 con procesos
                //descomentar la siguiente linea cuando lo haga y comentar la que le sigue 
                //strcpy(respuesta_a_cliente,chequear_consulta(consulta));
                strcpy(respuesta_a_cliente,"Prueba momentanea hasta solucionar chequear_consulta()");

		// Envio la respuesta al cliente...
		n = write(sock, respuesta_a_cliente, strlen(respuesta_a_cliente));
                if (n < 0)
                      error("ERROR de escritura en el socket");
		// limpio el buffer 
		memset(respuesta_a_cliente, 0, MAX_LONG_CONS);
	}
	if(read_size == 0) {
		printf("Se desconecto cliente %s\n",argumentos_de_thread.ip_cliente);
		fflush(stdout);
	}
	else if(read_size == -1) {
		perror("Fallo de recepcion");
	}
	return 0;
}
