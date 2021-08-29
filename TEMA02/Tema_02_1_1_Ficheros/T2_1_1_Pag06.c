#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    //ruta absoluta
    int fd1 = open("/home/alumno/data.dat", O_RDONLY);
    if (fd1<0){
        perror("open");
    } else 
        printf("Apertura correcta\n");
    close (fd1);
    //ruta relativa, al directorio actual
    int fd2 = open("data.dat", O_RDONLY);
    if (fd2<0){
        perror("open");
    } else 
        printf("Apertura correcta\n");
    close (fd2);
}

/* Llamadas al sistema para Ficheros
    APERTURA: int open (const char *path, int oflag);
    CREAR: int open (const char *path,int oflag_mode_t mode);

    oflag: O_RDONLY, O_WRONLY, O_RDWR, O_APPEND, O_TRUNC, O_CREAT 
    para O_CREATE necesitamos de mode, permisos del fichero
*/