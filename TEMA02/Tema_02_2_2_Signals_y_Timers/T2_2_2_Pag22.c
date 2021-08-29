#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

void manejador(int s){
    write(1,"alarma!\n",8);
    signal(SIGALRM,manejador); //Ojo hay que volver a asignar manejador
    alarm(3); //vuelve a activarla
}

int main(){
    signal(SIGALRM,manejador);
    alarm(3); //primera alarma a los 3 segundos
    while(1); //bucle infinito
    return 0;
}