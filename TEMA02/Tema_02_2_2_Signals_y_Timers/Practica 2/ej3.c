#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>


void manejador(int s){
    write(1,"manejador: Activado Ctrl+C\n",27);
    /* 2. Registra el manejador por defecto para SIGINT (Ctrl+C)*/
    signal(SIGINT,SIG_DFL);
}   

int main(int argc, char* argv[]){
    if (argc!=2){
        printf("Uso de %s: %s <segundos>\n",argv[0],argv[0]);
        exit(1);
    }
    signal(SIGINT,SIG_IGN);
    signal(SIGALRM, manejador);
    alarm(atoi(argv[1]));
    
    while(1){
        pause();
    }
}