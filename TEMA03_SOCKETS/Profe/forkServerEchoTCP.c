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
#include <sys/wait.h>
#include <signal.h>

#define PUERTO 4950
#define T 512

ssize_t read_n(int fd, void *mensaje, size_t longitud_mensaje);
ssize_t write_n(int fd, void *mensaje, size_t longitud_mensaje);

void espera_hijo(int signo) {
  printf("Hijo terminado\n");
  wait(0);
  signal(SIGCHLD, espera_hijo);
}

/**
 * Servidor TCP que atiende peticiones ECHO de clientes, uno a uno, es decir, 
 * recibe cadenas de texto que son enviadas de vuelta al cliente. El intercambio
 * de cadenas entre ambos se realiza asegurando que se lee/escribe lo esperado.
 * El servidor atiende al cliente hasta que este se desconecta, 
 * y después atiende a otro cliente.
 */
int main(int argc, char *argv[])
{

  if (signal(SIGCHLD, espera_hijo) == SIG_ERR) {

  }

  char b[T];
  int longitud;
  //direcciones de socket
  struct sockaddr_in serv_addr;
  struct sockaddr_in cli_addr;

  //2.- Creamos la dirección del servidor
  //2.1.- Inicializamos
  memset(&serv_addr, 0, sizeof(serv_addr));
  //2.2.- Rellenamos campos
  //2.2.1.- Familia de direcciones
  serv_addr.sin_family = AF_INET;
  //2.2.2.- Puerto
  serv_addr.sin_port = htons(PUERTO);
  //2.2.3.- Dirección IP
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  //1.- Crear el canal
  int sd;

  sd = socket(PF_INET, SOCK_STREAM, 0);
  if (sd < 0)
  {
    perror("socket");
    exit(1);
  }

  //2.- Lo vinculamos
  if (bind(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("bind");
    exit(1);
  }

  //3.- Ponemos el servidor en modo escucha (pasivo)
  ///   sd = canal de conexiiones
  if (listen(sd, 10) < 0)
  {
    perror("listen");
    exit(1);
  }

  int sd_datos; //socket activo para el intercambio de datos con el cliente
  socklen_t long_cli_addr = sizeof(cli_addr);
  int leidos;
  pid_t pid;
  uint32_t longBE;
  while (1)
  {
    //atiende a un cliente en cada iteración
    printf("Servidor esperando conexión... \n");
    sd_datos = accept(sd, (struct sockaddr *)&cli_addr, &long_cli_addr);
    if (sd_datos < 0)
    {
      /*if (errno == EINTR)
      {
        errno = 0;
        continue;
      }
      else
      {//*/
        perror("accept");
        close(sd_datos);
        close(sd);
        exit(1);
      //}
    }

    //aquí ya sé que te tengo un cliente conectado
    pid = fork();

    if (pid < 0)
    {
      perror("fork");
      close(sd);
      close(sd_datos);
      exit(1);
    }
    if (pid > 0)
    {
      //código del padre
      if (close(sd_datos) < 0)
      {
        perror("close sd_datos");
        exit(1);
      }
      //wait(0);
    }
    else
    {
      //código de hijo
      //ya tengo conexiíon con el cliente...
      //leemos cabecera +  mensaje hasta que el cliente se deconecte
      //  lectura adelantada + while;
      //recibo la longitud en big endian
      leidos = read_n(sd_datos, &longBE, sizeof(longBE));
      while (leidos > 0)
      {
        //proceso
        if (leidos != sizeof(longBE))
        {
          perror("read_n lonBE");
          close(sd_datos);
          close(sd);
          exit(1);
        }

        //ya tenemos la longitud en big endian -> convertirla a formato de host
        longitud = ntohl(longBE);
        printf("longitud mensaje = %d\n", longitud);

        //recibimos el mensaje
        if (read_n(sd_datos, b, longitud) != longitud)
        {
          perror("read_n mensaje");
          close(sd_datos);
          close(sd);
          exit(1);
        }

        //devolvemos el mensaje al cliente
        //primero, cabecera
        longBE = htonl(longitud);
        if (write_n(sd_datos, &longBE, sizeof(longBE)) != sizeof(longBE))
        {
          perror("write_n longBE");
          close(sd_datos);
          close(sd);
          exit(1);
        }

        //enviamos los datos
        if (write_n(sd_datos, b, longitud) != longitud)
        {
          perror("write_n mensaje");
          close(sd_datos);
          close(sd);
          exit(1);
        }

        leidos = read_n(sd_datos, &longBE, sizeof(longBE));
      }

      if (leidos == 0)
      {
        if (close(sd_datos) < 0)
        {
          perror("close sd_datos");
          exit(1);
        }
      }
      else
      { //leidos < 0 ... leidos != sizeof(longBE)
        perror("read_n lonBE");
        exit(1);
      }

      //salida ordenada
      exit(0);
    } // else fork

  } //while(1)

  return 0;
}

/**
 * Funciones auxiliares
 */
ssize_t read_n(int fd, void *mensaje, size_t longitud_mensaje)
{
  ssize_t a_leer = longitud_mensaje;
  ssize_t total_leido = 0;
  ssize_t leido;

  do
  {
    errno = 0;
    leido = read(fd, mensaje + total_leido, a_leer);
    if (leido >= 0)
    {
      total_leido += leido;
      a_leer -= leido;
    }
  } while ((
               (leido > 0) && (total_leido < longitud_mensaje)) ||
           (errno == EINTR));

  if (total_leido > 0)
  {
    return total_leido;
  }
  else
  {
    /* Para permitir que devuelva un posible error en la llamada a read() */
    return leido;
  }
}

ssize_t write_n(int fd, void *mensaje, size_t longitud_mensaje)
{
  ssize_t a_escribir = longitud_mensaje;
  ssize_t total_escrito = 0;
  ssize_t escrito;

  do
  {
    errno = 0;
    escrito = write(fd, mensaje + total_escrito, a_escribir);
    if (escrito >= 0)
    {
      total_escrito += escrito;
      a_escribir -= escrito;
    }
  } while (
      ((escrito > 0) && (total_escrito < longitud_mensaje)) ||
      (errno == EINTR));

  if (total_escrito > 0)
  {
    return total_escrito;
  }
  else
  {
    /* Para permitir que devuelva un posible error de la llamada a write */
    return escrito;
  }
}
