/*---------------------------------------------------------------
 * FICHERO:     servidor_ficheros_udp.c
 * DESCRIPCION: servidor de transmisión de ficheros por UDP
 * SINTAXIS:    servidor_ficheros_udp
 *--------------------------------------------------------------------------
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <fcntl.h>

#define PUERTO 5100 /* Puerto del servidor */
#define TAM_BUFFER 512  /* Tamaño de buffer */

int main(int argc, char ** argv) {
  int sd; /* Descriptor de socket */
  int fd; /* Descriptor de fichero */
  int bytes_recibidos; /* Bytes recibidos */
  int bytes_escritos; /* Bytes escritos en el fichero */
  char buffer[TAM_BUFFER]; /* Buffer */
  
  /* 1. Creación del socket UDP */
  sd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    perror("socket");
    exit(1);
  }
  
  /* Inicializar la estructura con la dirección del servidor */
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PUERTO);
  serv_addr.sin_addr.s_addr = INADDR_ANY; /* Escucha por cualquier interfaz */
  
  struct sockaddr_in cli_addr; /* Direccion del cliente */
  socklen_t cli_len; /* Longitud de la dirección del cliente */

  /* 2. Vincula el socket al puerto asignado */
  if (bind(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind");
    exit(1);
  }
  
  /* Abrimos el fichero para escritura */
  fd = open("fichero_recibido", O_WRONLY | O_CREAT, 0666 | O_TRUNC);
  if (fd < 0) {
    perror("open");
    exit(1);
  }

  printf("Esperando transmisión de fichero...\n");
  
  /* Recibimos los datagramas con los datos del fichero */
  do {
    /* Recibe datos del cliente, obteniendo también su IP y puerto */
    cli_len = sizeof(cli_addr);
    bytes_recibidos = recvfrom(sd,
      buffer,
      TAM_BUFFER,
      0,
      (struct sockaddr *) &cli_addr,
      &cli_len
      );

    if (bytes_recibidos < 0) {
      /* Error en la recepción */
      perror("recvfrom");
      close(fd);
      close(sd);
      exit(1);
    } else if (bytes_recibidos > 0) {
      /* Escribir los datos en el fichero */
      bytes_escritos = write(fd, buffer, bytes_recibidos);
      if (bytes_escritos != bytes_recibidos) {
        perror("write");
      }
    }    
  } while (bytes_recibidos > 0);
 
  printf("Fichero recibido!\n");
  
  /* Cerramos los descriptores */
  close(fd);
  close(sd);
  
  return 0;
}
