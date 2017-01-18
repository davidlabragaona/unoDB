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
 *    David Labra Gaona
 *
 *
 *****************************************************************************/


typedef struct campo {
        char * nombre_campo;            /* nombre de campo */
        int tipo_de_dato;               /* tipo de dato almacenado */
        struct campo * siguiente;       /* puntero a siguiente, para la lista de campos */
}campo;

struct tabla {
	char * nombre_tabla; 			/* Nombre de la tabla */
	campo * lista_de_campos;	/* puntero a la lista de campos	*/
	int cantidad_de_campos;		/* cantidad de campos de la tabla */
	int cantidad_de_registros;	/* cantidad de resgistros actuales en la tabla, para estadisticas */
	union dato * datos;		/* puntero al inicio de datos */
	struct tabla * siguiente;	/* puntero a siguiente, para la lista de tablas */
};

typedef union dato{
	int dato_entero;		/* se almacena el dato entero */
        char * dato_cadena;		/* se almacena el dato cadena */
        union dato * siguiente;		/* puntero a siguiente */
}dato;

typedef struct comienzo_registro { 
        union dato * datos_registro;			/* puntero al comienzo de la lista de datos del registro*/
        struct comienzo_registro * registro_anterior;	/* puntero al siguiente registro de la tabla */
        struct comienzo_registro * registro_siguiente;	/* puntero al registro anterior */
}comienzo_registro;

struct tabla * primero, * ultimo , * nuevo ,  * temporal;

/* Ubicacion del listado de tablas*/
#define ARCHIVO_TABLAS "tablas/tablas.dat"

/* Definimos las funciones a usar */

/* lee el archivo tablas.dat y va cargando la lista de tablas */
int leerListaDeTablas();

/* leer el archivo en tablas/nombre_de_tabla.dat y cargo registro por registro y todo los campos */
void cargarTabla(comienzo_registro *);

/* Empieza la inicializacion de definicion de tablas y de ahi se dispara toda la carga de datos */
void inicializaTodo();


