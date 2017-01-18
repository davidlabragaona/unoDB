/*
Gramática libre de contexto (BNF)

accion:
	[listar] lista_select expresion_tabla

lista_select:
	[*] | sublista_select coma sublista_select
sublista_select -> campo
expresion_tabla -> de tabla
*/

typedef enum {
	false,
	true
} bool;

char respuesta[MAX_LONG_CONS];

enum { CORRECTO, ERROR };
enum { NO, LISTAR, BORRAR };

char cadena[MAX_LONG_CONS];
char cadenamin[MAX_LONG_CONS];
char campos[MAX_LONG_CONS];
char tabla[MAX_LONG_CONS];

int comando;
bool ej_bien;
bool todos;
int pos;
bool coincidir(char texto[]);
void leer(char texto[]);
void accion(void);
void lista_select(void);
int sublista_select(void);
int saltar_espacios(void);
int expresion_tabla(void);
void limpiar_variables(void);
int nombre_tabla(void);
void convertir_minuscula(void);
void comando_incompleto(void);
void printerr(char *);

