#include <signal.h>
#include <unistd.h>

void manejador (int num_signal){
    /* tratamiento de la señal */
    write (1,"\nCapturado CTRL+C: No!\n",22);
    return; //Retorna a la instrucción siguiente antes de la señal
}

int main(){
    signal(SIGINT, SIG_IGN); //Armamos el manejador
    while(1);
}
