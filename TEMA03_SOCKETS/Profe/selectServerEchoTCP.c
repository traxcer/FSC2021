#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
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
void copia_fdset(fd_set *dst, fd_set *origen, int maxfd_mas_uno);
int maximo(int max, int n);

/**
 * Servidor TCP que atiende peticiones ECHO de clientes, uno a uno, es decir, 
 * recibe cadenas de texto que son enviadas de vuelta al cliente. El intercambio
 * de cadenas entre ambos se realiza enviando primero la longitud y después la 
 * cadena en sí. El servidor atiende al cliente hasta que este se desconecta, 
 * y después atiende a otro cliente.
 */
int main(int argc, char * argv[]) {
	//1.- Declaramos variables
	//2.- Creamos la dirección del servidor
	//3.- Creamos el socket
	//4.- Asociamos el socket al puerto: bind()
	//5.- Ponemos el socket en escucha (modo pasivo): listen()
	//6.- Creamos las estructuras de datos para select
	//		6.1.- El único descriptor es el socket pasivo por el que se conectan clientes
	//7.- Iteramos
	//		7.1.- Copiamos el conjunto de descriptores
	//		7.2.- Llamamos a select()
	//		7.3.- Si se desbloquea, hay que distingir si es:
	//			7.3.1.- El socket pasivo, en cuyo caso se acepta al cliente y se
	//				    añade el nuevo socket activo al cjto_descriptores
	//			7.3.2.- Un socket activo, es que un cliente ha escrito y, por tanto,
	//                  hay que atenderlo según la especificación
	//7.- Close
	
	
	//1.- Declaramos variables
	int sd; //descriptores de socket
	char buffer[MAXBUFFER];
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
	 
	//3.- Creamos el socket
	if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket");
		exit(1);
	}
	
	//4.- Asociamos el socket al puerto: bind()
	if (bind(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) {
		perror("bind");
		exit(1);
	}
	
	//5.- Ponemos el socket en escucha (modo pasivo): listen()
	if (listen(sd, 5) < 0)  {
		perror("listen");
		exit(1);
	}
	
	//6.- Creamos las estructuras de datos para select: cjts descriptores
	fd_set cjto_descriptores, cjto_modificado;
	int maxDescriptor;
	FD_ZERO(&cjto_descriptores);
	FD_SET(sd,&cjto_descriptores);
	maxDescriptor = sd;
	
	//7.- Iteramos
	
	socklen_t addr_len = sizeof(cli_addr);
	uint32_t longBigEndian;
	int leidos;
	while(1) {
		printf("Servidor esperando conexión...\n");
		
		//7.1.- Select modifica los parámetros, por lo que copiamos aquí siempre el conjunto original
		copia_fdset(&cjto_modificado,&cjto_descriptores,maxDescriptor+1);

		//7.2.- Llamamos a select
		if (select(maxDescriptor+1,&cjto_modificado, NULL, NULL, NULL) < 0) {
			perror("select");
			exit(1);
		}
		
		//iteramos sobre todos los posibles descriptores abiertos
		for (int d = 0; d < maxDescriptor+1; d++) {
			if (FD_ISSET(d,&cjto_modificado)) {
				//el descriptor d está preparado para lectura
				//tenemos que comprobar si es el socket pasivo, 
				//para hacer un accept
				if (d == sd) { 
					//ahora que sabemos que hay un cliente esperando,
					//hacemos el accept, que no bloqueará
					int n_sd = accept(sd, (struct sockaddr *) &cli_addr, &addr_len);
					if(n_sd < 0) {
						perror("error al aceptar nueva conexión");
						exit(1);
					}
					
					//este nuevo descriptor hay que incluirlo
					//en el conjunto de descriptores original, para que 
					//en la siguiente iteración del select, ya se chequee
					FD_SET(n_sd, &cjto_descriptores);
					
					//miramos si es el mayor, para hacer la llamada correctamente
					maxDescriptor = maximo(maxDescriptor,n_sd);
					
					printf("Nuevo cliente desde %s en el socket %d\n",
						inet_ntoa(cli_addr.sin_addr), n_sd
					);
				} else {
					//es un descriptor de socket activo de un cliente
					// podemos empezar a proveer el servicio al cliente
					//6.2.- Leemos longitud + cadena del cliente
					//OJO: AHORA EL SOCKET ACTIVO ES "d", no n_sd
					leidos = read_n(d, &longBigEndian, sizeof(longBigEndian));
					if (leidos > 0) {
						if (leidos != sizeof(longBigEndian)) {
							perror("read_n longBigEndian");
							close(sd);
							close(d);
							exit(1);
						}
						//ya tenemos la longitud en big endian
						longitud = ntohl(longBigEndian);
						printf("longitud recibida:  %d\n", longitud);
						
						//leemos la cadena
						if (read_n(d, buffer, longitud) != longitud) {
							perror("read_n buffer");
							close(sd);
							close(d);
							exit(1);
						}
						
						buffer[longitud] = '\0';
						printf("buffer = %s\n", buffer);
						
						//enviamos longitud y cadena al cliente
						longBigEndian = htonl(longitud);
						if (write_n(d, &longBigEndian, sizeof(longBigEndian)) != sizeof(longBigEndian)) {
							perror("write_n longitud");
							close(sd);
							close(d);
							exit(1);
						}
						if (write_n(d, buffer, longitud) != longitud) {
							perror("write_n buffer");
							close(sd);
							close(d);
							exit(1);
						}
					} else if (leidos < 0) {
						perror("read_n longBigEndian");
						close(sd);
						close(d);
						exit(1);
					} else  {
						//leidos == 0
						if (close(d) <0 ) {
							perror("close");
							close(sd);
							exit(1);
						}
						
						//sacamos del conjunto de descriptores
						FD_CLR(d, &cjto_descriptores);
					}
				}
			}
		}
	}
	
	//7.- Close
	if (close(sd) < 0) {
		perror("close");
		exit(1);
	}
		
	
	return 0;
}

/**
 * Funciones auxiliares
 */

int maximo(int max, int n)
{
	if (n > max)
		return n;
	else
		return max;
}

void copia_fdset(fd_set *dst, fd_set *origen, int maxfd_mas_uno){
	FD_ZERO(dst);
	for(int i=0;i<maxfd_mas_uno;i++) {
		if(FD_ISSET(i,origen)) 
			FD_SET(i,dst);
	} 
}



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
