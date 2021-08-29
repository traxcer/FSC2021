#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void m(int signo){
    char texto[25];
    int n= sprintf(texto,"Señal %d Capturada\n", signo);
    write(1,texto,n);
    exit (1);
}

void alarma(int signo){
    char texto[50];
    int n= sprintf(texto,"Alarma (señal %d) antes de capturar una señal\n", signo);
    write(1,texto,n);
    exit (1);
}

int main(){
    
    signal(SIGUSR1,m); //registra el manejador, nunca dispara
    signal(SIGALRM,alarma);
    alarm(10);
    write(1,"Esperando 10 segundos a que llegue una señal...\n",49);
    pause(); //proceso dormido hasta que llegue una señal
}

/*
pause()   Hace que el proceso se duerma hasta que reciba una señal
raise(signal_id) Envia una señal al proceso en ejecución
kill (pid_dest_signal_ signal_id)  Envia señal
*/