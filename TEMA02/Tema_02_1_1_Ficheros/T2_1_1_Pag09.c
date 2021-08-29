#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd_read;
    int fd_write;
    int fd_readwrite;
    int fd_append;

    // Abre el fichero /etc/passwd en modo lectura
    if ((fd_read = open("/etc/passwd", O_RDONLY)) < 0){
        perror("OPEN");
        exit(1);
    }
    // Abre el fichero run.log en el dir actual en modo ESCRITURA 
    // y lo trunca si contiene algo (borra)
    if ((fd_write = open("run.log", O_WRONLY | O_TRUNC)) < 0){
        perror("OPEN");
        exit(1);
    }
    // Abre el fichero /var/data/food.db en modo LECTURA/ESCRITURA 
    if ((fd_readwrite = open("run.log", O_RDWR)) < 0){
        perror("OPEN");
        exit(1);
    }
    // Abre el fichero /var/log/messages en modo ESCRITURA para
    //añadir datos a los comtenidos existentes
    if ((fd_append = open("var/log/messages", O_WRONLY, O_APPEND)) < 0){
        perror("OPEN");
        exit(1);
    }
    
}