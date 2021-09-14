/* Ejemplo de clase */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include "rutinas.h"

#define T 16

/*Prototipo de funciones*/
void copia_fdset(fd_set * destino, fd_set *origen, int maxfdmasuno);
void print_fdset(char * nombre, fd_set *fds, int maxfdmasuno);
ssize_t write_n(int fd,void *mensaje, size_t longitud_mensaje);

int main(int argc, char * argv[]){
    /*1.Control de argumentos de entrada*/
    if (argc<3){
        printf("Uso: %s <f1> <f2>\n",argv[0]);
        return -1;
    }
    /*2.Descriptores para fifos y fichero*/
    int f1,f2;

    /*3.Apertura de fifos. Se asumen creadas en el SO*/
    printf("Esperando la apertura de la f1...\n");
    if((f1=open(argv[1],O_RDONLY))<0){
        perror("open f1");
        exit (-1);
    } else
        printf("f1 abierta, esperando datos...\n");
    
    if((f2=open(argv[2],O_RDONLY))<0){
        perror("open f2");
        exit (-1);
    } else 
        printf("f2 abierta, esperando datos...\n");

    int leidos, r;
    char b[T];
    /*Estructuras de datos*/
    fd_set rfd, rfd_a;
    FD_ZERO(&rfd); //inicializa
    FD_SET(f1,&rfd); //asigna descriptores
    FD_SET(f2,&rfd);
    int maximo= f1 > f2 ? f1:f2; //calcula el máximo
    printf("Descriptores: f1[%u], f2[%u], el máximo [%u]\n", f1,f2,maximo);
    struct timeval t,t_a;
    t.tv_sec=15;
    t.tv_usec= 750000;
    int conectados=2;

    /*Bucle del servidor*/
    while (conectados >0){
        errno=0;
        printf("Esperando los datos de los clientes...\n");
        copia_fdset(&rfd_a,&rfd,maximo+1);
        t_a = t;
        if((r=select(maximo+1, &rfd_a,NULL,NULL,&t_a))<0){
            if (errno=EINTR){
                errno=0;
                continue;
            } else {
                perror("select");
                close (f2);
                close (f1);
                exit (-1);
            }
        }
        //Para inspección
        print_fdset("Modificado", &rfd_a, maximo+1);

        if (r==0){ //ha saltado el timer
            printf("Temporizador expirado\n");
        }
        if (FD_ISSET(f1,&rfd_a)){ //hay datos en f1
            leidos=read(f1,b,T);
            if (leidos<0){ //error en read
                perror("read f1");
                close(f1);
                close(f2);
                exit(-1);
            } else if (leidos==0){ //descriptor cerrado
                conectados --;
                FD_CLR(f1,&rfd);
            } else { //ha leido cosas
                b[leidos-1]='\0';
                printf("fifo1: %s (%d)\n",b, leidos);
            }
        }
        if (FD_ISSET(f2,&rfd_a)){ //hay datos en f1
            leidos=read(f2,b,T);
            if (leidos<0){ //error en read
                perror("read f2");
                close(f1);
                close(f2);
                exit(-1);
            } else if (leidos==0){ //descriptor cerrado
                conectados --;
                FD_CLR(f2,&rfd);
            } else { //ha leido cosas
                b[leidos-1]='\0';
                printf("fifo2: %s (%d)\n",b, leidos);
            }
        }

    } //fin del bucle del servidor

    if(close(f1)<0){
        perror("close f1");
        close(f2);
        exit (-1);
    }
    if(close(f2)<0){
        perror("close f2");
        close(f1);
        exit (-1);
    }

}//fin main
