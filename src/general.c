/*
*    Funciones usadas por cliente y servidor
*
*    Jose Julian Buda
*    David Labra Gaona 
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/general.h"

void error(const char *msg){
    perror(msg);
    exit(0);
}


