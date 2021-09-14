/*------------------------------------------------------------------------
 * FICHERO:     cliente_ficheros.c
 * DESCRIPCION: cliente de transmisión de ficheros sobre TCP
 * SINTAXIS:    cliente_ficheros nombre_fichero [direccionIP]
 *              Si no se especifica la IP, se usa 127.0.0.1
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
#define TAM_BUFFER 512	/* Tamaño del buffer */

const char IP_SERVIDOR[] = "127.0.0.1"; /* IP del servidor por defecto */

int main(int argc, char **argv) {
  int sd, fd; /* Descriptores del socket y del fichero */
  ssize_t leidos, enviados; /* Contadores de bytes leídos y enviados */
  uint8_t longitud_nombre; /* Longitud del nombre del fichero */
  uint32_t direccion_IP; /* Dirección IP del servidor */
  char buffer[TAM_BUFFER]; /* Buffer de lectura y envío */
  struct sockaddr_in serv_addr; /* Dirección del servidor */

  /* Comprobamos que se ha indicado el nombre del fichero como argumento */
  if (argc < 2) {
    fprintf(stderr, "Sintaxis: %s nombre_fichero [direccionIP]\n", argv[0]);
    exit(1);
  }
  
  /* Comprobamos si se ha indicado una dirección IP como argumento */
  if (argc == 3) {
    direccion_IP = inet_addr(argv[2]);
    if (direccion_IP == -1) {
      printf("Error: inet_addr");
      exit(1);
    }
  } else {
    /* Se usa la dirección IP por defecto */
    direccion_IP = inet_addr(IP_SERVIDOR);
  }
  
  /* Creamos el socket */
  sd = socket(PF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    perror("socket");
    exit(1);
  }

  /* Rellenamos la estructura con la dirección del servidor */
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr=direccion_IP;
  //memcpy(&serv_addr.sin_addr, &direccion_IP, 4);
  serv_addr.sin_port = htons(PUERTO);
  
  /* Establecemos la conexión con el servidor */
  if (connect(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect");
    exit(1);
  }
  
  /* Abrimos el fichero para lectura */
  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    /* No se ha podido abrir el fichero. Se cierra la conexión. */
    perror("open");
    close(sd);
    exit(1);
  }

  /* Se va a enviar un mensaje al servidor con la siguiente forma:
   *
   *  -----------------------------------------------------------------
   * | longitud_nombre_fichero (1 byte) | nombre_fichero (sin el '\0') |
   *  -----------------------------------------------------------------
   */

  /* Enviamos el byte indicando la longitud del nombre del fichero */
  longitud_nombre = strlen(argv[1]);
  if (write_n(sd, &longitud_nombre, 1) != 1) {
    /* Error en el envío */
    perror("write_n longitud_nombre");
    close(sd);
    exit(1);
  }
  
  /* Enviamos el nombre del fichero */
  if (write_n(sd, argv[1], longitud_nombre) != longitud_nombre) {
    /* Error en el envío */
    perror("write_n nombre_fichero");
    close(sd);
    exit(1);
  }
  
  /* Enviamos el contenido del fichero */
  do {
    /* Leemos un bloque de datos del fichero y lo guardamos en el buffer */
    leidos = read_n(fd, buffer, TAM_BUFFER);
    if (leidos > 0) {
      /* Enviamos los bytes leídos al servidor */
      enviados = write_n(sd, buffer, leidos);
      if (enviados != leidos) {
        /* Fallo en el envío */
        perror("write_n datos fichero");
        close(fd);
        close(sd);
        exit(1);
      }
    } else if (leidos < 0) {
      /* Error en la lectura del fichero */
      perror("read_n");
      close(fd);
      close(sd);
      exit(1);
    }
  } while (leidos != 0); /* Leemos hasta llegar al final del fichero */
  
  /* Cerramos el fichero y la conexión con el servidor */
  close(fd);
  close(sd);
 
  printf("Fichero enviado con éxito: %s\n", argv[1]);
  return 0;
}
