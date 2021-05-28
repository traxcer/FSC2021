/****************************************************************/
/* FICHERO: cliente.c */
/* DESCRIPCION: cliente hace uso del servidor de fechas */
/****************************************************************/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

int main() {
    struct sockaddr_in direccionServidor ;
    int descSocket; /* descriptor del socket */
    int codigoOperacion ;
    struct FechaYHora fecha;
    memset(&direccionServidor, 0, sizeof(direccionServidor)); /*la pone a cero*/
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = inet_addr(direccion_ip);
    direccionServidor.sin_port = htons(atoi(puerto_tcp));
    /*creacion del socket TCP*/
    if ((descSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cliente: no se ha podido abrir el socket") ;
        exit(1);
    } 
    /*conexion al servidor*/
    if (connect(descSocket,(struct sockaddr *) &direccionServidor,
        sizeof(direccionServidor)) < 0) {
        perror("no se ha podido conectar con servidor") ;
        exit(1) ;
    }
    printf("Cliente: conexion establecida\n") ;
    codigoOperacion = SOLICITUD_FECHA ;
    /*solicita la fecha al servidor*/
    send(descSocket, &codigoOperacion, sizeof(codigoOperacion),0) ;
    /*espera respuesta*/
    recv(descSocket, &codigoOperacion, sizeof(codigoOperacion),0) ;
    if (codigoOperacion == RESPUESTA_FECHA) {
        /*recibe la fecha*/
        recv(descSocket, &fecha, sizeof(fecha),0) ;
        printf("Fecha: %d-%d-%d ", fecha.dia , fecha.mes , fecha.anno ) ;
        printf("Hora:%d-%d-%d\n", fecha.hora, fecha.minuto, fecha.segundo) ;
    }
    else {
        fprintf(stderr, "CLIENTE: Error al recibir->") ;
        fprintf(stderr, "mensaje desconocido: %d\n", codigoOperacion) ;
        exit(1) ;
    }
    return 0;
} /* main */