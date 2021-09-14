/*--------------------------------------------------------------------------
 * FICHERO:     cliente_eco.c
 * DESCRIPCION: cliente que hace uso del servidor de eco
 * SINTAXIS:    cliente_eco [direccionIP]
 *              Si no se especifica la IP, se usa 127.0.0.1
 *--------------------------------------------------------------------------*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

#define PUERTO 5200 /* Puerto del servidor */
#define TAM_BUFFER 1024 /* Tamaño del buffer */

const char IP_SERVIDOR[] = "127.0.0.1"; /* IP del servidor por defecto */

int main(int argc, char ** argv) {
  int sd; /* Descriptor de socket */
  int leidos, enviados; /* Número de bytes recibidos y enviados */
  uint32_t direccion_IP; /* Dirección IP del servidor */
  char buffer[TAM_BUFFER]; /* Buffer de envío y recepción */
  struct sockaddr_in serv_addr; /* Dirección del servidor */
  
  /* Comprobamos si se ha indicado una IP como parámetro */
  if (argc == 1) {
    direccion_IP = inet_addr(IP_SERVIDOR);
  } else {
    direccion_IP = inet_addr(argv[1]);
    if (direccion_IP == -1) {
      perror("inet_addr");
      exit(1);
    }
  }
  
  /* Creamos el socket para conectarnos al servidor */
  sd = socket(PF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    perror("socket");
    exit(1);
  }
  
  /* Rellenamos la estructura con la dirección del servidor */
  memset(&serv_addr, 0, sizeof(serv_addr)); /* Se inicializa a 0 */
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr, &direccion_IP, 4);
  serv_addr.sin_port = htons(PUERTO);
  
  /* Establecemos la conexión con el servidor */
  if (connect(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect");
    exit(1);
  }
  
  printf("Bienvenido al cliente de eco TCP\n\n");
  /* Bucle del cliente */
  while (1) {
    /* Leemos una cadena por teclado */
    printf("Introduzca una cadena cualquiera: ");
    fgets(buffer, TAM_BUFFER, stdin);
    
    /* Enviamos la cadena al servidor */
    enviados = send(sd, buffer, strlen(buffer), 0);
    if (enviados < 0) {
      perror("send");
      close(sd);
      exit(1);
    }
    
    /* Esperamos la respuesta (eco) del servidor */
    leidos = recv(sd, buffer, TAM_BUFFER, 0);
    if (leidos == 0) {
      /* Se ha cerrado la conexión */
      close(sd);
      break; /* Salimos del bucle */
    } else if (leidos < 0) {
      /* Error en la recepción de datos */
      perror("recv");
      close(sd);
      exit(1);
    }
    
    buffer[leidos] = '\0';
    printf("Recibido eco: %s\n\n", buffer);
  }
  
  return 0;
}