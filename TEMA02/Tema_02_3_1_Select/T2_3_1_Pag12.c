/* Ejemplo con select() de los apuntes*/
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
/*abrimos las fifo*/
    int fifo1,fifo2;
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
    fd_set rfd, rfd_a;
    FD_ZERO(&rfd); /*vacio*/
    FD_SET(fifo1, &rfd);
    FD_SET(fifo2, &rfd);

    int maximo = fifo1>fifo2 ? fifo1:fifo2; /*si se cumple fifo1*/

    struct timeval t,t_a; /*vamos a usar un timer*/
    t.tv_sec=2;
    t.tv_usec=750000;
    
    int r, leidos;
    char b[T];
    
    while(1){
        /*copia de rfd y del timeval*/
        copia_fdset(&rfd_a,&rfd,maximo+1);
        t_a=t;

        if((r=select(maximo+1,&rfd_a,NULL,NULL,&t_a))<0){ /*error en select*/
            perror("select");
            close(fifo1);
            close(fifo2);
            exit(-1);
        }
        if (r==0){ /*Salto el timer*/
            /*se haría algo especifico, ojo: read bloquearia*/
            printf("Se pasó el timers sin datos que leer, sigo escuchando...\n");
        }
        if (FD_ISSET(fifo1,&rfd_a)){
            leidos= read(fifo1,b,T);
            /*info recibida del proceso
            El read al tener datos, no se bloquea
            */
           if (leidos<0){
               perror("leidos");
               exit (-1);
           } else if (leidos==0){ /*se cerró el descriptor*/
                printf("Se cerró [fifo1]\n");
                FD_CLR(fifo1,&rfd);
           } else{
               printf("[fifo1] leido: %s\n",b);
           }
        }
        if (FD_ISSET(fifo1,&rfd_a)){
            leidos= read(fifo2,b,T);
            /*info recibida del proceso
            El read al tener datos, no se bloquea
            */
            if (leidos<0){
               perror("leidos");
               exit (-1);
           } else if (leidos==0){ /*se cerró el descriptor*/
                printf("Se cerró [fifo2]\n");
                FD_CLR(fifo2,&rfd);
           } else{
                printf("[fifo2] leido: %s\n",b);
           }
        }
    }
}