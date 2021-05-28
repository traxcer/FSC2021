/* Programa crono.c para probar el temporizador en c*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>



void m (int sig){
    write(1,"hola mundo\n",11);
    signal(SIGALRM,m);
}

int main(){
struct itimerval microno;
    microno.it_value.tv_sec=60; //tiempo de expiración 60 segundos
    microno.it_value.tv_usec=0;
    microno.it_interval.tv_sec=1; //intervalo
    microno.it_interval.tv_usec=0;
    printf("asigno la señal\n");
    setitimer(ITIMER_REAL,&microno,NULL);
    printf("ajusto temporizador\n");
    signal(SIGALRM,m);
    printf("valor de getitimer=%d\n",getitimer(ITIMER_REAL,&microno));
    getitimer(ITIMER_REAL,&microno);
    while (microno.it_value.tv_sec >0){
        printf("Estoy en el while y tv_sec=%d\n",(int)microno.it_value.tv_sec);
    }
    printf("se acabo el coronometro\n");
}