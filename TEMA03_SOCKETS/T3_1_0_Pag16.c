#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "rutinas.h"


#define T 256

//funciones
ssize_t write_n(int fd,void *mensaje, size_t longitud_mensaje);
ssize_t read_n(int fd,void *mensaje, size_t longitud_mensaje);

struct PDU{
    uint16_t size;
    char payload[T];
};

int main(){
    int p[2];
    int pid;
    if((pipe(p))<0){
        perror("fifo");
        exit (-1);
    }
    if ((pid=fork())<0){
        perror("fork");
        exit(-1);
    } else if (pid==0){ //proceso hijo
        struct PDU datos_recibidos;
        uint16_t dataBigEndiand;
        if (close(p[1])<0){ //cierro el extremo no usado
            perror("close");
            exit (-1);
        }
        if(read_n(p[0],&dataBigEndiand,sizeof(uint16_t))!=sizeof(uint16_t)){
            perror("read PDU.size");
            close(p[1]);
            exit (-1);
        }
        datos_recibidos.size=ntohs(dataBigEndiand);
        if(read_n(p[0],datos_recibidos.payload,datos_recibidos.size)!=datos_recibidos.size){
            perror("read PDU.payload");
            close(p[1]);
            exit (-1);
        }
        printf("[Rcve.Hijo]:%u - %s\n",datos_recibidos.size,datos_recibidos.payload);
        if (close (p[0])<0){
            perror("close");
            exit(-1);
        }
        exit (1);
    } else if (pid!=0){ //proceso padre (emisor)
        struct PDU data;
        memcpy (data.payload,"Hola esto es lo enviado",23);
        data.size = 23;
        if (close(p[0])<0){ //cierro el extremo no usado
            perror("close");
            exit (-1);
        }    
        uint16_t data_big_endian = htons(data.size);
        printf("[Padre] p[1]fd: %u data.size: %u  data.payload: %s\n",p[1],data.size,data.payload);
        if(write_n(p[1], &data_big_endian,sizeof(data_big_endian))!=sizeof(data_big_endian)){
            perror("write PDU.size");
            close(p[1]);
            exit (-1);
        }
        if(write_n(p[1], data.payload,data.size)!=data.size){
            perror("write PDU.payload");
            close(p[1]);
            exit (-1);
        }
        wait(0); //Espera a que el hijo imprima lo enviado
        if (close(p[0])<0){ //cierro el extremo no usado
            perror("close");
            exit (-1);
        }    
    }
    return 1;
}