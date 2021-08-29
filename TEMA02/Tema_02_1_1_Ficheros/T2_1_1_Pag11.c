#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd_creat;
    char fichero[]="creat.dat";

    // Crea un fichero con unos permisos determinados
    if ((fd_creat = creat(fichero, 0644)) < 0){
        perror("OPEN");
        exit(1);
    }
}

/* 
PROTOTIPO: int creat(consta char *path. mode_t mode)

Es quivalente a open() con los flags, O_WRONLY | O_TRUNC | O_CREAT
*/