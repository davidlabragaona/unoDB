/*
*    Headers usadas por cliente y servidor
*
*    Jose Julian Buda
*    David Labra Gaona 
*
*/

/*maxima longitud de un comando/sentencia/consulta*/
#define MAX_LONG_CONS 256

/*puerto tcp que escuah el servidor y al cual se conecta el cliente*/
#define PUERTO_TCP 2006

/*Numero de version del servidor*/
#define VERSION "2.0.0"

void error(const char *msg);
