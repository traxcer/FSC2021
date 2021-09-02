/* Ejemplo de Clase */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "read_n.c"
#include "write_n.c"

ssize_t read_n(int fd, void *mensaje, size_t longitud);
ssize_t write_n(int fd, void *mensaje, size_t longitud);

#define T 256

int main(int argc, char * argv[]){
pid_t pid;
int p[2];
char nombre[25],apellido[25];

/* 1. Creamos la pipe para compartir (padre/hijos) el descriptor */
if(pipe(p)<0){
    perror("pipe");
    exit (-1);
}
/* 2. Clonamos */
if ((pid=fork())<0){
    perror("fork");
    exit (-1);
} else if (pid==0){ /*Hijo*/
    /*Cierro extremo no usado (escritura)*/
    if (close (p[1])<0){
        perror("close");
        exit (-1);
    }
    /* Lee el nombre de la tuberia*/
    int longitud;
    int leidos;
    if((leidos= read_n(p[0],&longitud,sizeof(int)))!=sizeof(int)){
        perror("read long nombre");
        exit (-1);
    }
    
    if((leidos= read_n(p[0],nombre,longitud))!=longitud){
        perror("read nombre");
        exit (-1);
    }
    nombre[longitud]='\0';
    printf("(H) El nombre es:%s\n", nombre);
    /* Lee el apellido de la tuberia*/
    if((leidos= read_n(p[0],&longitud,sizeof(int)))!=sizeof(int)){
        perror("read long apellido");
        exit (-1);
    }
    if((leidos= read_n(p[0],apellido,longitud))!=longitud){
        perror("read apellido");
        exit (-1);
    }
    apellido[longitud]='\0';
    printf("(H) El apellido es:%s\n", apellido);
    /*Cierro la pipe (lectura)*/
    if (close (p[0])<0){
        perror("close");
        exit (-1);
    }
    exit(1);

} else { /*Padre*/
    /*El padre escribirá el nombre y apellido en la pipe*/
    /*Cierra extremo de la pipe no usado (lectura)*/
    if (close (p[0])<0){
        perror("close");
        exit (-1);
    }
    /*Pide datos por teclado, no se puede usar la lectura protegida
    pues no sabemos cuantos caracteres se van a introducir*/
    printf("(P) Introduzca el nombre:\n");
    int r1=read(0,nombre,T);
    printf("(P) Introduzca el apellido:\n");
    int r2=read(0,apellido,T);
    /*Enviamos a la pipe, junto a su tamaño*/
    int l=r1-1; /*tamaño leido de nombre*/
    if(write_n(p[1],&l,sizeof(int))!=sizeof(int)){
        perror("write_n tamaño nombre");
        exit (-1);
    }
    if(write_n(p[1],nombre,r1-1) != r1-1){
        perror("write_n nombre");
        exit (-1);
    }
    l=r2-1; /*tamaño leido de apellido*/
    if(write_n(p[1],&l,sizeof(int))!=sizeof(int)){
        perror("write_n tamaño apellido");
        exit (-1);
    }
    if(write_n(p[1],apellido,r2-1) != r2-1){
        perror("write_n apellido");
        exit (-1);
    }
    /*Cierro extremo de escritura*/
    if (close (p[1])<0){
        perror("close");
        exit (-1);
    }
    /*Espero a que acabe el hijo*/
    wait(0);
    }
}
