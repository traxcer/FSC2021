/*
Implemente un programa que genere un proceso hijo encargado de mostrar por 
pantalla la información que le suministra su padre. 
El padre obtiene la información del usuario por teclado. 
Los procesos terminan cuando se introduce por teclado la cadena "fin\n" 
(es decir, "fin" más la pulsación de la tecla INTRO). 
Esta cadena de finalización no debe enviarse al hijo. 
Utilice una pipe para el trasiego de información entre padre e hijo.
*/

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
        while (read(tuberia[0],mensaje,MAX) && strcmp(mensaje,"fin\n")!=0)
            printf("Proceso %d Receptor, mensaje: %s\n",getpid(),mensaje);
        close (tuberia[0]);
        close (tuberia[1]);
    } else {
        //Proceso padre
        while (printf("Proceso %d Emision, mensaje: ",getpid()) !=0 &&
            fgets(mensaje, sizeof(mensaje),stdin) != NULL &&
            write(tuberia[1],mensaje,strlen(mensaje)+1) &&
            strcmp(mensaje, "fin\n")!=0);
        close (tuberia[0]);
        close (tuberia[1]);
        exit(0);
    }
}