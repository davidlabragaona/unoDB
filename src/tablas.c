/******************************************************************************
 *                   unoDb
 *
 * Estructuras que soportan la carga en memoria de la tablas
 *
 * tabla : estructura basica de una tabla
 *
 * campo : estructura de campo de la tabla
 *
 * dato  : union que soporta 1 tipos de datos
 *
 * comienzo_registro : comienzo del registro de una tabla
 *
 *  unoDb :
 *
 *    Jose Julian Buda
 *    Matias Noriega
 *    David Labra Gaona
 *    Marcelo Cuello
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <ctype.h>
#include "../include/tablas.h"


void inicializaTodo(){
     primero = (struct tabla *) NULL;
     ultimo = (struct tabla *) NULL;
     temporal = (struct tabla *) NULL;
     
     leerListaDeTablas();
     temporal=primero;
     printf("Tables en memoria\n");
     while(temporal!=NULL){
     	 printf("\t%s",temporal->nombre_tabla);
         temporal=temporal->siguiente;
     }
}


int leerListaDeTablas(){
	nuevo = (struct tabla *)malloc(sizeof(struct tabla));
 	FILE *archivo; 	
 	char linea[50];

 	archivo = fopen(ARCHIVO_TABLAS,"r"); 	
	if (archivo == NULL)
 		return -1;
        /* voy cargando la lista de tablas*/ 
	while (fgets(linea,50,archivo)!=NULL){
		if (primero==NULL) {
		         //printf( "Primer elemento\n");
		         primero = nuevo;
		         ultimo = nuevo;
		         primero->nombre_tabla = (char *)malloc(strlen(linea));;
			 strcpy(primero->nombre_tabla, linea);
		}
		else {
		        /* el que hasta ahora era el último tiene que apuntar al nuevo */
		        ultimo->siguiente = nuevo;
		        /* hacemos que el nuevo sea ahora el último */
		        ultimo = nuevo;
		        nuevo->nombre_tabla = (char *)malloc(strlen(linea));
			strcpy(nuevo->nombre_tabla, linea);
	        }
		nuevo = (struct tabla *)malloc(sizeof(struct tabla));
 	}
        fclose(archivo);
	return 0;
}
