#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

ssize_t write_n(int fd, void * buf, size_t n){ //funcion read_n()
    ssize_t a_escribir = n; //lo que queremos leer
    ssize_t total_escrito = 0 ; //por ahora no ha leido nada
    ssize_t escrito=0; //leido en una tacada

    do{
        errno=0; //pone 0 los errores
        escrito=write(fd,buf+total_escrito, a_escribir);
        //desplaza el puntero del buffer pare no sobre-escribir
        if (escrito>=0){
            total_escrito += escrito;
            a_escribir -= escrito;
            //actualiza lo leido (+) y lo que queda por leer (-)
        }
    } while (((escrito >0) && (total_escrito < n)) || (errno == EINTR));
    //mientra lea algo, quede por leer, o se ha interrumpido por señal
    if (total_escrito>0)
        return total_escrito;
    else
        return escrito;    
}    