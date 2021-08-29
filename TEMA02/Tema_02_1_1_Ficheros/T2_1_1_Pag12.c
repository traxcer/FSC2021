#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    // Abre el fichero /etc/passwd en modo lectura y lo lee
    int fd_read;
    char ficheroread[]="/etc/passwd";
    ssize_t leidos;
    if ((fd_read = open(ficheroread, O_RDONLY)) < 0){
        perror("OPEN");
        exit(1);
    }
    char buffer[255];
    if ((leidos=read(fd_read, buffer, sizeof(buffer)))<0){
        perror("Leyendo:");
        exit (-1);
    }
    printf("Fichero \'%s\' leidos %lu bytes:\n%s\n",ficheroread,leidos, buffer);
    close (fd_read);

    // Ahora pruebo a escribir y leer en ejemplo.dat
    int fd_write;
    char ficherowrite[]="ejemplo12.dat";
    ssize_t escrito;
    strcpy(buffer,"Esto es una prueba de escritura");
    if((fd_write=creat(ficherowrite, 0644))<0){
        perror("CREAT");
        exit(-1);
    }
    if((escrito=write(fd_write, buffer,32))==0){
        perror("WRITE");
        exit(-1);
    }
    close (fd_write);
    // Leo lo escrito
    if ((fd_read = open(ficherowrite, O_RDONLY)) < 0){
        perror("OPEN");
        exit(1);
    }
    char buffer2[255];
    if ((leidos=read(fd_read, buffer2, sizeof(buffer2)))<0){
        perror("Leyendo:");
        exit (-1);
    }
    printf("Fichero \'%s\' leidos %lu bytes:\n%s\n",ficherowrite,leidos, buffer);
    close (fd_read);



}

/*

*/