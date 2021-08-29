#include <signal.h>
#include <stdio.h>
#include <unistd.h>


void manejador(int num_signal){
    signal(SIGINT, manejador);
    if (num_signal != 0)
        write(1,"No!\n",4);
    return;
}

int main(){
    signal(SIGINT, manejador);
    while(1);
    return 0;
}