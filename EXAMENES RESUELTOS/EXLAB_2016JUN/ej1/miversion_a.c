#include <stdio.h>
#include <sys/time.h>


//Defino los estados
#define LISTO            0
#define RETRASO_TX       1
#define ESPERA_CTS       2
#define ESPERA_TX_FINISH 3
#define RETRASO_RTS_OFF  4
#define ESPERA_CTS_OFF   5
#define ERROR            6
//Defino los eventos
#define MANDA_MENSAJE    0

int espera_evento(){
    return -1;
}

main(){

int estado= LISTO; //comenzamos en el estado inicial
int fin=0;

struct timeval valor; //asigno valores al temporizador
struct timeval intervalo_cero;

intervalo_cero.tv_sec=0;
intervalo_cero.tv_usec=0;
struct itimerval timerval;
timerval.it_interval=intervalo_cero;

while (!fin){ //Bucla hasta que se active fin (fin!=0)
    int evento=espera_evento(); //inicia en -1 (espera de eventos)
    switch (estado)
    {
    case LISTO:
        if (evento==MANDA_MENSAJE)
            valor.tv_sec=1;
            valor.tv_usec=500000;//(0,5s)
            timerval.it_value = valor;
	        setitimer(ITIMER_REAL, &timerval, NULL);
	        estado = RETRASO_TX;
        
        break;
    
    default:
        break;
    }
}


}