#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
    
/* Definimos Estados y Eventos */

#define estadoA 0
#define estadoB 1
#define evento0 0
#define evento1 1

int espera_evento(){
    write(1,"Esperando que introduzcas un evento [0,1]: ",43);
    int b=0;
    int leido=0;
    if ((leido = read(0,&b,sizeof(char)))<0){
        perror("read");
        exit (1);
        }
    return (b-'0');
}

int main(){
    int fin =0;
    int estado = estadoA; /* Estado inicial */
    int evento;
    printf("Estoy en el estado %d inicialmente y espero un evento\n",estado);
    while (!fin){
        evento = espera_evento();
        printf("Estoy en el estado %d y ha llegado el evento %d\n",estado, evento);
        switch (estado)
        {
        case estadoA:
            switch (evento){
                case evento0:
                    printf("conmuta A->B\n");
                    estado = estadoB;
                    break;
                case evento1:
                    printf("fin\n");
                    fin=1;
                    break;
            }
        break;
        case estadoB:
            switch (evento){
                case evento1:
                    printf("conmuta B->A\n");
                    estado = estadoB;
                    break;
                case evento0:
                    printf("fin\n");
                    fin=1;
                    break;
            }
        break;
        default:
            printf("Estasdo no reconocido\n");
            fin=1;
            break;
       }

    }
}