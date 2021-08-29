/* Ejemplo de libro programación UNIX */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador_sigterm(int sig){
    printf("\nHA llegado la señal nº: %d\n",sig);
/* Ojo:
    Al compilar con std=c99, estamos en Linux System V, y una vez que se
    trata a la señal, esta se resetea al manejador por defecto, así que
    una vez invocada ya no la gestiona este manejador.
    Tendriamos que en el mismo manejador volver a registrar el manejador
    para gestionar esta interrupción con signal.
*/
}

int main(){
    if (signal(SIGINT,manejador_sigterm)==SIG_ERR){
        perror("Signal");
        exit (-1);
    }

    while(1){
        printf("\nEn espera de CTRL+C\n");
        pause();
    }
}