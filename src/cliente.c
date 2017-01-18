/*
*   Cliente unoDb
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
#include "../include/cliente.h"
#include "../include/general.h"
#include <netdb.h> 

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char consulta[MAX_LONG_CONS];
    char respuesta[MAX_LONG_CONS];  

    if (argc < 2) {
       fprintf(stderr,"ejecutar %s nombre_servidor_o_IP \n", argv[0]);
       exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no encuentro el nombre del servidor, use su IP directamente\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(PUERTO_TCP);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
       error("ERROR no puede conectar");
       exit(0);
    } 
    printf("Bienvenido a cliente unoDb\n");
    printf("Conectado a servidor %s\n",argv[1]);
    printf("Server version: 2.0.0\n\n");
    while((strcmp(consulta,"salir"))&&(strcmp(consulta,"bajarservidor"))){
       printf("unoDb>");
       gets(consulta);
       fflush(stdin);
       if(strcmp(consulta,"salir")){
           if(strlen(consulta)){//no puede enviar una cadena vacia
               n = write(sockfd,consulta,strlen(consulta));
               if (n < 0) 
                   error("ERROR de escritura en el servidor");
               bzero(respuesta,256);
               n = read(sockfd,respuesta,255);
               if (n < 0) 
                   error("ERROR leyendo del servidor");
               printf("%s\n",respuesta);
           }
       }
       else{
              n = write(sockfd,"saliocliente",12);  
              printf("Chau\n");
       }
    }
    close(sockfd);
    return 0;
}
