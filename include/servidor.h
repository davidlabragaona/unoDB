/*
*    Info/funciones usada por el servidor
*
*
*
*
*
*/


//va acumulando la cantidad de procesos que se van abriendo para manejar las conexiones concurrentes
int cantidad_de_clientes;

//se ejecuta cuando en el cliente corro el comando "bajarservidor"
//capturando ctrl+c
void bajarServidor();

void bannerDeBienvenida();

void *recibeConexion(void *socket_desc);

/* estructura que se le pasa como argumento al crear el thread de conexion entrante*/
typedef struct argumentos_thread_conexion {
        char ip_cliente[INET_ADDRSTRLEN]; /* Ip del cliente que abre el thread*/
        int socket_asociado;               /* Socket asociado al cliente del thread*/ 
}argumentos_thread_conexion;
