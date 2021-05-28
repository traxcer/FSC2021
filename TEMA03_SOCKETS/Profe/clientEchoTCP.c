#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PUERTO 4950
#define MAXBUFFER 512

ssize_t read_n(int fd, void * mensaje, size_t longitud_mensaje);
ssize_t write_n(int fd, void * mensaje, size_t longitud_mensaje);

/**
 * Cliente TCP que envía peticiones ECHO a un servidor cuya IP se introduce
 * como argumento del main y que escucha en el puerto 4950. 
 * Para realizar dichas peticiones, el cliente 
 * solicita al usuario cadenas por teclado y envía una a una hasta que éste
 * introduce la cadena "fin". La cadena "fin" no se envía al servidor.
 * Entonces se desconecta y finaliza la conexión.
 */
int main(int argc, char * argv[]) {
	
	//1.- Procesamos los argumentos
	if (argc < 2) {
		printf("Uso: %s <IP>\n",argv[0]);
		exit(1);
	}
	
	//2.- Declaración de variables
	//descriptor de socket
	int sd;
	//buffer
	char buffer[MAXBUFFER];
	//dirección del servidor
	struct sockaddr_in serv_addr;
	//longitudes
	int longitud;
	uint32_t longBigEndian;
	
	//3.- Montamos la dirección del servidor
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port   = htons(PUERTO);
	uint32_t ip_servidor;
	if ((ip_servidor = inet_addr(argv[1])) < 0) {
		printf("Error al convertir la IP %s\n", argv[1]);
		exit(1);
	}
	memcpy(&serv_addr.sin_addr, &ip_servidor, sizeof(ip_servidor));
	//serv_addr.sin_addr.s_addr = ip_servidor;
	
	//4.- Creamos el socket
	if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket");
		exit(1);
	}	
	
	//5.- Abrimos la conexión con el servidor
	if (connect(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) {
		perror("connect");
		exit(1);
	}
	
	//6.- Iteramos: lectura adelantada + while
	printf("Introduzca una cadena: \n");
	int leidos = read(0,buffer, MAXBUFFER);
	buffer[leidos - 1] = '\0';
	
	while(strcmp(buffer, "fin") != 0) {
		//calculamos la longitud
		longitud = strlen(buffer);
		 
		 // convertimos a big endian
		 longBigEndian = htonl(longitud);
		 
		 //la envianos
		 if (write_n(sd, &longBigEndian, sizeof(longBigEndian)) != sizeof(longBigEndian)) {
			 perror("write longitud");
			 close(sd);
			 exit(1);
		 }
		 
		 //enviamos la cadena
		 if  (write_n(sd, buffer, longitud) != longitud) {
			 perror("write longitud");
			 close(sd);
			 exit(1);
		 }
		 
		 //esperamos respuesta del servidor
		 if (read_n(sd, &longBigEndian, sizeof(longBigEndian)) != sizeof(longBigEndian)) {
			 perror("read longitud");
			 close(sd);
			 exit(1);
		 }
		 
		 //convertimos de formato de red a formato de host
		 longitud = ntohl(longBigEndian);
		 printf("longitud recibida: %d\n", longitud);
		 
		 //leemos la cadena
		 if (read_n(sd, buffer, longitud) != longitud) {
			 perror("read buffer");
			 close(sd);
			 exit(1);
		 }
		 
		 buffer[longitud] = '\0';
		 printf("buffer = %s\n", buffer);
			 
			 
		 //volvemos a solicitar la cadena al cliente
		 printf("Introduzca otra cadena: \n");
		 leidos = read(0,buffer, MAXBUFFER);
		buffer[leidos - 1] = '\0';
	}
	
	// Cerramos
	if (close(sd) < 0) {
		perror("close");
		exit(1);
	}
	return 0;
}

/**
 * Funciones auxiliares
 */
ssize_t read_n(int fd, void * mensaje, size_t longitud_mensaje) {
  ssize_t a_leer = longitud_mensaje;
  ssize_t total_leido = 0;
  ssize_t leido;
  
  do {
    errno = 0;
    leido = read(fd, mensaje + total_leido, a_leer);
    if (leido >= 0) {
      total_leido += leido;
      a_leer -= leido;
    }
  } while((
      (leido > 0) && (total_leido < longitud_mensaje)) ||
      (errno == EINTR));
  
  if (total_leido > 0) {
    return total_leido;
  } else {
    /* Para permitir que devuelva un posible error en la llamada a read() */
    return leido;
  }
}

ssize_t write_n(int fd, void * mensaje, size_t longitud_mensaje) {
  ssize_t a_escribir = longitud_mensaje;
  ssize_t total_escrito = 0;
  ssize_t escrito;
  
  do {
    errno = 0;
    escrito = write(fd, mensaje + total_escrito, a_escribir);
    if (escrito >= 0) {
      total_escrito += escrito ;
      a_escribir -= escrito ;
    }
  } while(
        ((escrito > 0) && (total_escrito < longitud_mensaje)) ||
        (errno == EINTR));
  
  if (total_escrito > 0) {
    return total_escrito;
  } else {
    /* Para permitir que devuelva un posible error de la llamada a write */
    return escrito;
  }
}
