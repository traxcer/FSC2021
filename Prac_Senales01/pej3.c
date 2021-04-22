/* Implementaun programa inmune al Ctrl-C durante los segundos que
 se introduzcan como argumento. Transcurridos éstos, se volverá a 
 habilitarla posibilidad de que se cierre el programa con Ctrl-C.*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

 void manejador(int s){
     write(1,"Ya no ignoramos Ctrl+C\n",22);
     signal(SIGINT,SIG_DFL);
 }
 
 int main(int argc, char * argv[]){
    signal(SIGINT,SIG_IGN);
    signal(SIGALRM,manejador);

    if(argc<2)
        printf("Uso: %s <segundos>",argv[0]);
    
    alarm(atoi(argv[1]));
    while(1){
        pause();
    }
    printf("Programa terminado");
 }