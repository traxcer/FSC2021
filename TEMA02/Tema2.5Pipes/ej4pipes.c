/* Ejemplo 4 de los Apuntes del tema 2.5 

Ejercicio hecho por Eloy Gutiérrez
1 de Junio 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

# define T 256

int main(){
    pid_t pid;
    char* b[T];
    int p[2]; //tuberia
    int leidos;

    if(pipe(p)<0){
        perror("pipe");
        exit(-1);
    }
    if ((pid=fork())<0){
        perror("fork");
        exit(1);
    }
    else if (pid==0){ //Estamos en el proceso hijo
        if ((close (p[1]))<0){
            perror("close pipe");
            exit(-1);
        }
        while((leidos=read(p[0],b,T))>0){
            write(1,b,leidos);
        }
        if (leidos<0){
            perror("read");
            exit(-1);
        }
        if (close (p[0])<0){
            perror("close pipe");
            exit(-1);
        }
        exit(0);
    }
    else{ //Estamos en el padre
        if (close (p[0])<0){
            perror("close pipe");
            exit(-1);
        }
        if((write(p[1],"Hola!\n",6))!=6){
            perror("write");
            exit(-1);
        }
        if ((close (p[1]))<0){
            perror("close pipe");
            exit(-1);
        }
        wait(0); //espera al hijo;
    }
}
