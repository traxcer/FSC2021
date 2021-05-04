#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 256

int main(){
    int tuberia[2];
    int pid;
    char mensaje[MAX];

    if (pipe(tuberia)==-1){
        perror("pipe: ");
        exit (-1);
    }
    if ((pid=fork())==-1){ //Fallo al crear fork
        perror("fork: ");
        exit(-1);
    } else if (pid==0) {
        //Proceso hijo
        while (read(tuberia[0],mensaje,MAX) && strcmp(mensaje,"FIN\n")!=0)
            printf("Proceso %d Receptor, mensaje: %s\n",getpid(),mensaje);
        close (tuberia[0]);
        close (tuberia[1]);
    } else {
        //Proceso padre
        while (printf("Proceso %d Emision, mensaje: ",getpid()) !=0 &&
            fgets(mensaje, sizeof(mensaje),stdin) != NULL &&
            write(tuberia[1],mensaje,strlen(mensaje)+1) &&
            strcmp(mensaje, "FIN\n")!=0);
        close (tuberia[0]);
        close (tuberia[1]);
        exit(0);
    }
}