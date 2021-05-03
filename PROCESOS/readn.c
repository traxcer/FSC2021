#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

ssize_t read_n(int fd, char * b,size_t n){
    ssize_t a_leer=n;
    ssize_t total_leidos=0;
    ssize_t leidos;

    do {
        errno=0; //ojo, hay que inicializar
        leidos = read(fd , b + total_leidos, a_leer);
        if (leidos >= 0) {
            total_leidos += leidos;
            a_leer -= leidos;
        }
} while (((leidos>0) && (total_leidos <n)) || (errno == EINTR)); //Ojo desbalanceo parentesis

if (total_leidos > 0 ) {
    return total_leidos;
} else {
    return leidos;
}
