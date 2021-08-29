#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

//Envio de señales en C
int main(int argc, char * argv[]){
    if (argc<2){
        printf("Uso: %s <PID>\n",argv[0]);
        return 1;
    }
pid_t pid = atoi(argv[1]);
int retorno;
    if ((retorno = kill(pid, SIGTERM))<0){
        perror("kill");
        return 1;
    }
}
/*
Tipo de datos pid_t, identificadores de procesos
llamada al sistema kill()
#define POSIX SOURCE para evitar warning
señal: SIGTERM, señal de terminación
*/