#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

ssize_t read_n(int fd, char *buf, ssize_t n){ //funcion read_n()
    ssize_t a_leer = n; //lo que queremos leer
    ssize_t total_leido = 0 ; //por ahora no ha leido nada
    ssize_t leido=0; //leido en una tacada

    do{
        errno=0; //pone 0 los errores
        leido=read(fd,buf+total_leido, a_leer);
        //desplaza el puntero del buffer pare no sobre-escribir
        if (leido>=0){
            total_leido += leido;
            a_leer -= leido;
            //actualiza lo leido (+) y lo que queda por leer (-)
        }
    } while (((leido >0) && (total_leido < n)) || (errno == EINTR));
    //mientra lea algo, quede por leer, o se ha interrumpido por señal
    if (total_leido>0)
        return total_leido;
    else
        return leido;    
}    