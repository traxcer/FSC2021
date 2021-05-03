#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define T 10

void m (int sig){
    signal(SIGUSR1,m);
}

int main(int argc, char* argv[]){

    char b [T+1];
    printf("PID: %d\n",getpid());
    signal(SIGUSR1,m);
    printf("Introduce %d caracteres:\n",T);
    int leidos = read(0,b,T);
    int total_leidos=leidos;
    while (total_leidos){
        int por_leer=T-total_leidos;
        printf("leidos=%d\n", leidos);
        printf("faltan por leer %d\n",por_leer);
        leidos=read(0,b+total_leidos, por_leer);
        total_leidos+=leidos;
    }
    printf("Total leidos= %d\n", total_leidos);
    b[total_leidos+1]='\0';
    printf("b= %s\n",b);
}