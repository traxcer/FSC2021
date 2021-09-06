/* Server_fifo_sec.c
Ejercicio de clase,m que ilustra el problema de el bloqueo
de read para los servidores y que secuencializa la atención
a los clientes, lo cual no es para nada deseado
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "write_n.c"

#define T 256

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usar: %s <fifo1> <fifo2>", argv[0]);
        exit(1);
    }

    int fd, fifo1,fifo2;
    if ( (fd=open("log.txt",O_WRONLY | O_APPEND | O_CREAT, 0644))<0){
        perror("open");
        exit (-1);
    }
    int conectados=0; //incialmente nadie conectado
    printf("Esperando al cliente 1...\n");
    //abrimos fifos, se asumen creadas previamente en el SO
    if ( (fifo1=open(argv[1],O_RDONLY))<0){
        perror("open");
        exit (-1);
    }
    if ( (fifo2=open(argv[2],O_RDONLY))<0){
        perror("open");
        exit (-1);
    }
    /* Abiertas las fifos, grabará sus logs
    Primer problema de la secuencialización,
    deben estar abiertas las dos fifos para 
    llegar aqui y grabar los logs.
    POSTERIORMENTE SE SOLVENTARA CON:
    select()
    */

    printf("Guardando info de los logs...\n");
    conectados=2;

    /* Bucle de operación del servidor */
    char buffer[T];
    int leidos;
    while(conectados>0){
        if ((leidos=read(fifo1,buffer,T))<0){
            perror("read fifo1");
            exit(-1);
        } else if (leidos==0){ /*Cerrada conexion*/
            conectados --;
        } else { /*hay datos, grabo al log.txt */
            if (write_n(fd,buffer,leidos)!=leidos){
                perror("white_n log.txt");
                exit(-1);
            }
        }
        if ((leidos=read(fifo2,buffer,T))<0){
            perror("read fifo2");
            exit(-1);
        } else if (leidos==0){ /*Cerrada conexion*/
            conectados --;
        } else { /*hay datos, grabo al log.txt */
            if (write_n(fd,buffer,leidos)!=leidos){
                perror("white_n log.txt");
                exit(-1);
            }
        }
    }
    if(close(fifo1)<0){
        perror("close fifo1");
        exit(-1);
    }
    if(close(fifo2)<0){
        perror("close fifo2");
        exit(-1);
    }
    if(close(fd)<0){
        perror("close");
        exit(-1);
    }

}