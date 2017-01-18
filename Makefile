#    Makefile perteneciente al proyecto unoDb
#    
#    Jose Julian Buda
#    David Labra Gaona
#
#

CC = gcc
DIR_SRC = src/

#compila todo y guarda ejecutables en ./
todo:
	$(CC) $(DIR_SRC)servidor.c $(DIR_SRC)general.c $(DIR_SRC)tablas.c $(DIR_SRC)parser.c -o servidor -lpthread
	$(CC) $(DIR_SRC)cliente.c $(DIR_SRC)general.c -o cliente

#compila servidor y guarda ejecutable en ./
servidor:
	$(CC) $(DIR_SRC)servidor.c $(DIR_SRC)general.c $(DIR_SRC)tablas.c $(DIR_SRC)parser.c -o servidor -lpthread

#borra los ejecutables anteriores
clean:
	rm -f servidor cliente

#compila cliente y guarda ejecutable en ./
cliente:
	$(CC) $(DIR_SRC)cliente.c $(DIR_SRC)general.c -o cliente
