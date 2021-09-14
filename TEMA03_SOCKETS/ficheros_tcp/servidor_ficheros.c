/*------------------------------------------------------------------------
 * FICHERO:     servidor_ficheros.c
 * DESCRIPCION: Servidor de recepción de ficheros sobre TCP
 * SINTAXIS:    servidor_ficheros
 *------------------------------------------------------------------------*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include "rutinas.h"

#define PUERTO 5200 /* Puerto del servidor */
#define TAM_BUFFER 512 /* Tamaño del buffer */

ssize_t write_n(int fd,void *mensaje, size_t longitud_mensaje);
ssize_t read_n(int fd,void *mensaje, size_t longitud_mensaje);


int main(int argc, char **argv) {
  int sd; /* Descriptor del socket pasivo */
  int n_sd; /* Descriptor del socket activo */
  int fd; /* Descriptor del fichero */
  ssize_t leidos, escritos; /* Contadores de bytes leídos y escritos */
  
  struct sockaddr_in cli_addr; /* Dirección del cliente */
  struct sockaddr_in serv_addr; /* Dirección del servidor */
  socklen_t addr_len; /* Longitud de la dirección del cliente */
  uint8_t longitud_nombre; /* Longitud del nombre del fichero */
  char buffer[TAM_BUFFER]; /* Buffer de lectura y envío */
  
  /* Creamos el socket */
  sd = socket(PF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    perror("socket");
    exit(1);
  }
  
  /* Rellenamos la estructura con la dirección del servidor */
  memset(&serv_addr, 0, sizeof(serv_addr)); //ponemos a 0
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PUERTO);
  
  
  /* Vinculamos el socket a la dirección del servidor */
  if (bind(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind");
    exit(1);
  }
  
  /* Convertimos el socket en pasivo, para poder aceptar conexiones */
  if (listen(sd, 5) < 0) {
    perror("listen");
    exit(1);
  }
  
  printf("Servidor en modo Listen (pasivo), esperando conexión cliente...\n");
  
  /* Bucle del servidor */
  
  while(1) {
    /* Aceptamos la solicitud de conexión de un cliente */
    addr_len = sizeof(cli_addr);
    n_sd = accept(sd, (struct sockaddr *) &cli_addr, &addr_len); //bloquea
    if (n_sd < 0) {
      if (errno==EINTR){ //protege de señales
        errno=0;
        continue;
      } else {
        /* Error aceptando la conexión */
        perror("Error en accept");
        close(sd);
        exit(1);
      }
    }
    /* Recibimos la longitud del nombre del fichero */
    if (read_n(n_sd, &longitud_nombre, 1) != 1) {
      /* Error en la recepción */
      perror("read_n longitud_nombre)");
      close(n_sd);
      close(sd);
      exit(1);
    }
    
    /* Recibimos el nombre del fichero */
    if (read_n(n_sd, buffer, longitud_nombre) != longitud_nombre) {
      perror("read_n nombre_fichero");
      close(n_sd);
      close(sd);
      exit(1);
    }
    
    /* Creamos el fichero para almacenar los datos que se reciban */
    buffer[longitud_nombre] = '\0'; //ponemos la cadena con el nombre del fichero
    fd = creat(buffer, 0644);
    if (fd < 0) {
      perror("creat");
      close(n_sd);
      close(sd);
      exit(1);
    }
    
    /* Recibimos el contenido del fichero */
    do {
      /* Recibe un bloque de datos y lo almacena en el buffer */
      leidos = read_n(n_sd, buffer, TAM_BUFFER);
      if (leidos > 0) {
        /* Guardamos los bytes en el fichero */
        escritos = write_n(fd, buffer, leidos);
        if (escritos < 0) {
          /* Error en la escritura en el fichero */
          perror("write_n");
          close(fd);
          close(n_sd);
          close(sd);
          exit(1);
        }
      } else if (leidos < 0) {
        /* Error en la recepción de datos */
        perror("read");
        close(fd);
        close(n_sd);
        close(sd);
        exit(1);
      }
    } while (leidos > 0); /* Recibimos datos hasta que finalice la conexión */
    
    printf("Fichero recibido correctamente\n");
    
    /* Cerramos el fichero y el socket activo */
    close(fd);
    close(n_sd);
  }
  
  /* Cerramos el socket pasivo */
  close(sd);
  return 0;
}
