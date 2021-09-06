/* Server_fifo_select.c
Ejercicio de clase,m que ilustra el uso de select para 
de read para los servidores y que secuencializa la atención
a los clientes, lo cual no es para nada deseado
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include "write_n.c"

#define T 256

int max_fds(int actual, int nuevo){
    if (actual >= nuevo)
        return actual;
    return nuevo;
}

void copia_fdset(fd_set *destino, fd_set *origen, int maxfd_mas_uno){
    FD_ZERO(destino); /* Pone a cero destino */
    for(int i=0;i<maxfd_mas_uno;i++){
        if(FD_ISSET(i,origen))
            FD_SET(i,destino);
    }
}


int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usar: %s <fifo1> <fifo2>", argv[0]);
        exit(1);
    }

    int fd, fifo1,fifo2;
    if ( (fd=open("log.txt",O_WRONLY | O_APPEND | O_CREAT, 0644))<0){
        perror("open log");
        exit (-1);
    }
    int conectados=0; //incialmente nadie conectado
    printf("Esperando al cliente 1...\n");
    //abrimos fifos, se asumen creadas previamente en el SO
    if ( (fifo1=open(argv[1],O_RDONLY))<0){
        perror("open fifo1");
        exit (-1);
    }
    if ( (fifo2=open(argv[2],O_RDONLY))<0){
        perror("open fifo2");
        exit (-1);
    }
    /* Abiertas las fifos, crearé el conjunto para select*/
    fd_set rfd, activo_rfd;
    FD_ZERO(&rfd);
    FD_SET(fifo1, &rfd);
    FD_SET(fifo2, &rfd);

    printf("Guardando info de los logs...\n");
    conectados=2;

    /* Bucle de operación del servidor */
    char buffer[T];
    int leidos;
    while(conectados>0){
        copia_fdset(&activo_rfd, &rfd, max_fds(fifo1,fifo2)+1);
        /*Llamamos a select*/
        int rc = select(max_fds(fifo1,fifo2)+1, &rfd, NULL, NULL,NULL);
        /*chequeamos select*/
        if (rc<0){
            perror("select");

            close(fifo1);
            close(fifo2);
            exit(1);
        }

        if (FD_ISSET(fifo1, &activo_rfd)){
            if ((leidos=read(fifo1,buffer,T))<0){
            perror("read fifo1");
            exit(-1);
            } else if (leidos==0){ /*Cerrada conexion*/
                conectados --;
                if(close(fifo1)<0){
                    perror("close fifo1");
                    exit(-1);
                }
            } else { /*hay datos, grabo al log.txt */
                if (write_n(fd,buffer,leidos)!=leidos){
                    perror("white_n log.txt");
                    exit(-1);
                }
                FD_CLR(fifo1,&rfd);
            }
        }
        if (FD_ISSET(fifo2, &activo_rfd)){
            if ((leidos=read(fifo2,buffer,T))<0){
                perror("read fifo2");
                exit(-1);
            } else if (leidos==0){ /*Cerrada conexion*/
                conectados --;
                if(close(fifo2)<0){
                   perror("close fifo2");
                    exit(-1);
                }
                FD_CLR(fifo2,&rfd);
            } else { /*hay datos, grabo al log.txt */
                if (write_n(fd,buffer,leidos)!=leidos){
                    perror("white_n log.txt");
                    exit(-1);
                }
            }
        }
    }
       
    if(close(fd)<0){
        perror("close");
        exit(-1);
    }

}