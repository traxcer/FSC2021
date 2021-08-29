#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void manejador(int s){
    signal(SIGALRM, manejador);
    write(1, "ha llegado la señal\n",21);
}

int main(){
    struct itimerval timer;
    struct timeval valor;
    struct timeval temporizador;
    
    valor.tv_sec = 02;
    valor.tv_usec = 500000;
    temporizador.tv_sec = 1;
    temporizador.tv_usec = 0;

    timer.it_value = valor; //temporizador 1ª vez
    timer.it_interval=temporizador; //periodicidad

    signal(SIGALRM, manejador);
    setitimer(ITIMER_REAL, &timer, NULL);

    while(1);
    return 0;
}