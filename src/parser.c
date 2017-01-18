/*
Gramática libre de contexto (BNF)

accion:
	[listar] lista_select expresion_tabla

lista_select:
	[*] | sublista_select coma sublista_select
sublista_select -> campo
expresion_tabla -> de tabla
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
#include "../include/general.h"
#include "../include/parser.h"


void chequear_consulta(char *consulta)
{
	char temp[MAX_LONG_CONS] = "";

        strcpy(cadena, "");
        strcpy(cadenamin, "");
        strcpy(campos, "");
        strcpy(tabla, "");
        pos=0;

	ej_bien = false;
		todos = false;
		for (pos = 0; pos < MAX_LONG_CONS -1; pos++)
			temp[pos] = 0;
		pos = 0;
		comando = NO;
		//gets(cadena);
		strcpy(cadena, consulta);
		convertir_minuscula();
		accion();
		
			if (ej_bien) {
				switch (comando) {
					case LISTAR:
						strcat(temp, "Consulta ejecutada correctamente\n");
						if (todos)
							strcat(temp, "Listar todos los campos ");
						else {
							strcat(temp, "Listar campos ( ");
							strcat(temp, campos);
							strcat(temp, ") ");
						}
						strcat(temp, "de la tabla (");
						strcat(temp, tabla);
						strcat(temp, ")");
						
						break;
					case BORRAR:
						strcat(temp, "Consulta ejecutada correctamente\n");
						strcat(temp, "Borrando registros de la tabla (");
						strcat(temp, tabla);
						strcat(temp, ")");
						break;
				}
				strcpy(respuesta, temp);
			}
		limpiar_variables();
}

bool coincidir(char texto[]) {
	char temp[100] = "";
	
	strncpy(temp, &cadenamin[pos], (unsigned)strlen(texto));
	
	if (strcmp(temp, texto) == 0)
		return true;
	else
		return false;
}

void leer(char texto[]) {
	if (coincidir(texto))
		pos += strlen(texto);
}

void accion(void) {
	saltar_espacios();
	if (coincidir("listar")) {
		comando = LISTAR;
		leer("listar");
		lista_select();
	} else if (coincidir("borrar")) {
		comando = BORRAR;
		leer("borrar");
		expresion_tabla();
	}
	else {
		comando = NO;
		comando_incompleto();
	}
}

void lista_select(void) {
	int c;
	saltar_espacios();
	if (coincidir("*")) {
		leer("*");
		todos = true;
		saltar_espacios();
		if (coincidir(",")) {
			leer(",");
			if (!sublista_select())
				expresion_tabla();
		}
		else
			expresion_tabla();
	}
	else
		if (!sublista_select())
			expresion_tabla();
	
	
}

int sublista_select(void) {
	int cad, cad0;
	saltar_espacios();
	cad = strlen(campos);
	cad0 = cad;
	while (isalnum(cadenamin[pos]))
		campos[cad++] = cadenamin[pos++];
	
	if (cad0 < cad) {
		campos[cad] = ' ';
		if(coincidir(",")) {
			leer(",");
			return sublista_select();
		}
	}
	else {
		printerr("Falta especificar el nombre del campo");
		return ERROR;
	}
	return CORRECTO;
}

int saltar_espacios(void) {
	while (cadenamin[pos] == ' ')
	{
		if (pos > MAX_LONG_CONS - 1)
			return EOF;
		pos++;
	}
	return 0;
}

int expresion_tabla(void) {
	saltar_espacios();
	if (coincidir("de")) {
		leer("de");
	}
	else {
		printerr("Se esperaba la expresion \"de\"");
		return ERROR;
	}
	if (!nombre_tabla()) {
		ej_bien = true;
		return CORRECTO;
	}
	else
		return ERROR;
}

int nombre_tabla(void) {
	int cad;
	saltar_espacios();
	cad = strlen(tabla);
	while (isalnum(cadenamin[pos]))
	{
		tabla[cad++] = cadenamin[pos++];
	}
	
	if (!strlen(tabla)) {
		printerr("Se esperaba el nombre de la tabla");
		return ERROR;
	}
	return CORRECTO;
}

void limpiar_variables(void)
{
	pos = 0;
	while (pos < MAX_LONG_CONS)
	{
		cadenamin[pos] = 0;
		campos[pos] = 0;
		tabla[pos] = 0;
		cadena[pos] = 0;
		pos++;
	}
	comando = NO;
	pos = 0;
}

void convertir_minuscula(void)
{
	int i;
	for (i = 0; cadena[i] != '0' && i < MAX_LONG_CONS; i++)
		cadenamin[i] = tolower(cadena[i]);
}

void printerr(char *error)
{
	strcpy(respuesta, error);
}

void comando_incompleto(void)
{
	char temp[MAX_LONG_CONS] = "";
	char temp1[MAX_LONG_CONS] = "";
	
	saltar_espacios();
	strncat(temp, cadenamin, pos - 1);
	
	strcat(temp1, "No reconozco el comando [");
	strcat(temp1, temp);
	strcat(temp1, "]");
	printerr(temp1);
}
