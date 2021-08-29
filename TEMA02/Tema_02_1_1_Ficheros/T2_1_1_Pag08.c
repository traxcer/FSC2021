#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd, fd2;
    //Abre un fichero que ya existe, para lectura
    if ((fd = open("data.dat", O_RDONLY)) < 0){
        perror("OPEN");
        exit(1);
    }
    //Crea un fichero, para Escritura y trunca permiso para propietario
    if ((fd2 = open("ejemplo.dat", O_WRONLY | O_TRUNC |O_CREAT, 0600)) < 0){
        perror("OPEN");
        exit(1);
    }
    printf("Hemos creado exitosamente el fichero \'ejemplo.dat\'\n");
}