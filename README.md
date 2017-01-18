# unoDB
unoDB Server
************

Proyecto perteneciente a la catedra de Sistemas Operativos 1 de la 
Universidad Nacional del Oeste.

En el se trata de reflejar la teoria vista en la materia, de manejo de
procesos,los distintos mecanismos de IPC y señalizacion y la aquitectura
cliente-servidor, asi como tambien en lo referente a la logica del parser
que procesa las consultas y el manejo de las estructuras en memoria necesarias
en un gestor de base de datos(listas enlazadas,arboles, etc).

Basicamente es un gestor de base de datos "todo en memoria".

Va a soportar por ahora 2 tipos de datos, cadena y entero.

Consta de un servidor escuchando en el puerto 2006 (include/servidor.h)
y clientes(remotos o no) que envian consultas y reciben la respuesta.

En particular la primera version(0) utilizo pipes para comunicar el 
cliente con el servidor, y fue migrando a la version actual que 
implementa sockets para permitir comunicacion bidireccional en 
maquinas remotas.

La rama de la version actual(2) maneja la concurrencia con threads, la
 version 1 lo hacia con fork().
El manejo compartido de las estructuras de datos es mas simple en la version 2,
con procesos se complica reservar areas de memoria compartida entre los clientes.
Se debera usar semaforos para sincronizar la insercion/modificacion de datos.

Al momento de entrega,no se requiere autenticacion ni autorizacion
para conectarse al servidor desde el cliente, deberia tenerlo en el
futuro.

Tambien deberia poder parametrizarse(tanto cliente como servidor) por
archivo de configuracion, no hardcodedo en fuente como ahora.

Para salir del cliente ejecutr "salir"

Instalacion
Ver archivo INSTALL

Versiones
Ver archivo CHANGELOG

Idea / Desarroladores : 
 		Jose Julian Buda <julytoccr@yahoo.com>
		David Labra Gaona <davidlabragaona@gmail.com>

Colaboradores (esperemos que aumente la cantidad):
		Matias Noriega
		Marcelo Cuello
