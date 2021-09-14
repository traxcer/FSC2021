/*--------------------------------------------------------------------------
 * FICHERO:     cliente_ficheros_udp.c
 * DESCRIPCION: cliente de transmisión de ficheros por UDP
 * SINTAXIS:    cliente_ficheros_udp nombre_fichero [ip_servidor]
 *              Si no se especifica la IP, se usa 127.0.0.1
 *--------------------------------------------------------------------------
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>    
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <fcntl.h>

#define PUERTO 5100 /* Puerto en el que escucha el servidor */
#define TAM_BUFFER 512 /* Tamaño de buffer */

const char IP_SERVIDOR[] = "127.0.0.1"; /* IP del servidor por defecto */

int main(int argc, char ** argv) {
  int sd; /* Descriptor de socket */
  int fd; /* Descriptor de fichero */
  int bytes_leidos; /* Bytes leídos del fichero */
  int bytes_enviados; /* Bytes enviados */
  
  
  uint32_t ip_servidor; /* IP del servidor */
  
  
  char buffer[TAM_BUFFER]; /* Buffer */

  /* Obtenemos la dirección IP del servidor */
  if (argc < 2) {
    printf("Uso: %s nombre_fichero [ip_servidor]\n", argv[0]);
    exit(1);
  } else if (argc == 2) {
    /*
      No se ha indicado la IP del servidor como argumento.
      Se usa la IP por defecto.
    */
    ip_servidor = inet_addr(IP_SERVIDOR);
  } else {
    ip_servidor = inet_addr(argv[2]);
  }
  
  /* Comprobamos que la IP del servidor es válida */
  if (ip_servidor == -1) {
    printf("Error en inet_addr");
    exit(1);
  }
  
  /* Creamos el socket UDP */
  sd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    perror("socket");
    exit(1);
  }
  
  /* Inicializar la estructura con la dirección del servidor */
  struct sockaddr_in serv_addr; /* Dirección del servidor */
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PUERTO);
  //socklen_t serv_len; /* Longitud de la dirección del servidor */
  //memcpy(&serv_addr.sin_addr, &ip_servidor, 4);
  serv_addr.sin_addr.s_addr= ip_servidor;
  
  /* Abrimos el fichero que se va a transmitir */
  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(1);
  }
  
  printf("Enviando fichero...\n");
  while ((bytes_leidos = read(fd, buffer, TAM_BUFFER)) > 0) {
    /* Enviamos el siguiente bloque de datos */
    bytes_enviados = sendto(
      sd,
      buffer,
      bytes_leidos,
      0,
      (struct sockaddr *) &serv_addr,
      sizeof(serv_addr)
    );
    
    /* Comprobamos que no haya habido error */
    if (bytes_enviados < 0) {
      perror("sendto");
      close(fd);
      close(sd);
      exit(1);
    }
  }
  
  /*
    Enviamos un datagrama vacío para indicar que ha terminado la
    transmisión del fichero.
    */
  bytes_enviados = sendto(
    sd,
    NULL,
    0,
    0,
    (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)
  );
  
  if (bytes_enviados < 0) {
    /* Error en la transmisión */
    perror("sendto");
    close(fd);
    close(sd);
    exit(1);
  }
  
  printf("Fichero enviado!\n");
  
  /* Cerramos los descriptores */
  close(fd);
  close(sd);
  
  return 0;
}
