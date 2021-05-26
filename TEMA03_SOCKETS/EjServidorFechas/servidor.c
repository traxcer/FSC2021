/****************************************************************/
/* FICHERO: servidor.c */
/* DESCRIPCION: codigo de un servidor de fechas */
/****************************************************************/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "defs.h"

int main() {
    struct sockaddr_in direccionServidor, direccionCliente ;
    int descSocket, nuevoDescSocket ;
    socklen_t longDirCliente;//longitud de la direccion del cliente
    int codigoOperacion ;
    /* creacion del socket TCP */
    descSocket = socket(PF_INET, SOCK_STREAM, 0) ;
    if (descSocket < 0) {
        perror("no se ha podido abrir el socket") ;
        exit(1) ;
    }
    /* se pone a cero la direccion del servidor */
    memset(&direccionServidor, 0, sizeof(direccionServidor));
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    direccionServidor.sin_port = htons(atoi(puerto_tcp));
    /*vincula el proceso con el puerto de escucha indicado en la var. direccionServidor */
    if (bind(descSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor))< 0) {
        perror(" error al vincular la direccion local") ;
        exit(1) ;
    }
    /* pone el socket en modo pasivo (ahora puede aceptar conexiones) */
    listen(descSocket, 5); /*cinco clientes pueden esperar su turno en cola*/
    while(1){
        printf("Servidor esperando conexion ...\n");
        /* espera una conexion del cliente, devuelve dicha conexion en nuevoDescSocket */
        longDirCliente=sizeof(direccionCliente);/* longitud de la direccion del cliente */
        nuevoDescSocket = accept(descSocket, (struct sockaddr *) &direccionCliente ,&longDirCliente);
        if(nuevoDescSocket < 0) {
            fprintf(stderr, "SERVIDOR: error al aceptar nueva conexion \n") ;
            exit(1) ;
        }
        recv(nuevoDescSocket, &codigoOperacion, sizeof(codigoOperacion),0) ;
        switch(codigoOperacion) {
        case SOLICITUD_FECHA : {
            time_t fechaActual = time(0) ; /*obtiene el tiempo*/
            struct tm * fechaPtr = gmtime(&fechaActual); /*se convierte a una estructura tm*/
            struct FechaYHora fecha ;
            fecha.dia = fechaPtr->tm_mday ;
            fecha.mes = fechaPtr->tm_mon + 1 ; /* porque devuelve de 0 a 11 */
            fecha.anno = fechaPtr->tm_year + 1900;/*devuelve el transcurrido desde 1900 */
            fecha.hora = fechaPtr->tm_hour ;
            fecha.minuto = fechaPtr->tm_min ;
            fecha.segundo = fechaPtr->tm_sec ;
            codigoOperacion = RESPUESTA_FECHA ;
            send(nuevoDescSocket, &codigoOperacion, sizeof(codigoOperacion),0) ;
            send(nuevoDescSocket, &fecha , sizeof(fecha),0) ;
        break ;
        }
        default: {
            fprintf(stderr, "SERVIDOR: mensaje no valido: %d\n", codigoOperacion);
            exit(1) ;
        }
        } /* fin del switch */
    } /* fin del while */
} /* fin del main */