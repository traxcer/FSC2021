#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "read_n.c"
#include "write_n.c"
#include <signal.h>
    
/* Definimos Estados y Eventos */

#define E1 0
#define E2 1

int p[2]; /* Variable Global */

 void m0(int signo){
     int e= E1;
     if (write_n(p[1], &e,sizeof(int)) != sizeof(char)){
         perror("write_n");
         exit (-1);
     };
     signal(SIGUSR1,m0);
 }
 
 void m1(int signo){
     int e= E2;
     if (write_n(p[1], &e,sizeof(int)) != sizeof(char)){
         perror("write_n");
         exit (-1);
     };
     signal(SIGUSR1,m1);
 }

 int espera_evento(){
    int ev;
    if(read_n(p[0], &ev,sizeof(int)) != sizeof(char)) {
        perror("read_n");
        exit (-1);
    }
    return ev;
}

int main(){
    int estado = E1; /* Estado inicial */    
    int evento = 0;
    if ((pipe(p)) < 0){ /* Crea una pipe en la var global p */
        perror("pipe");
        exit (-1);
    }
    signal(SIGUSR1,m0); /* arma la señal */
    signal(SIGUSR2,m1); /* arma la señal */
    signal(SIGINT, SIG_DFL);

    printf("Estoy en el estado %d inicialmente y espero un evento\n",estado);
    
    while (1){
    espera_evento();
    printf("Estoy en el estado %d y ha llegado el evento %d\n",estado, evento);
    }
}