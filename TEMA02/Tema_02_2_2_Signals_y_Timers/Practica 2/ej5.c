#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void manejador(int s){
    signal(SIGALRM,manejador);
}

int read_n(int fd,char* b, ssize_t n){
    ssize_t aleer=n;
    ssize_t leido;
    ssize_t total_leido=0;
    do{
        errno=0;
        leido=read(fd,b+total_leido,aleer);
        if (leido>=0){
          total_leido += leido;
          aleer -= leido;
        }
    }while (((leido>0) && (total_leido<n) ) || (errno == EINTR));
    if (total_leido>0)
        return total_leido;
    else
        return leido;    
}

int main(){
    char b[25];
    /* Consultar en   el manual sobre cómo declarar y 
    asignar valores al campo it_interval */
    signal(SIGALRM,manejador);
    alarm(1);
    read(0,b,4);
    printf("leido:%s\n",b);

    read_n(0,b,4);
    printf("leido:%s\n",b);
return 0;
}