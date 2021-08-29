#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/* Def de tipo puntero a funcion, devuelve void y recibe entero*/
typedef void (*sighandler_t)(int);
/* Variable global de este tipo*/
sighandler_t puntero_a_funcion;

/*Prototipo para que no se queje el compilador*/
void manejador2(int s); 

void manejador1(int s){
    write(1,"manejador1\n",11);
    /* 2. Registra el manejador 2 para SIGINT (Ctrl+C)*/
    puntero_a_funcion=signal(SIGINT,manejador2);
    /*Guarda en la variable puntero_a_funcion lo que devuelve signal*/
}   
void manejador2(int s){
    write(1,"manejador2\n",11);
    /* 3. Registra el manejador 2 para SIGINT (Ctrl+C)*/
    signal(SIGINT,manejador1);

}   

int main(){
    /* 1. Registra el manejador1 para que atienda s SIGINT (Ctrl+C)*/
    signal(SIGINT, manejador1);
    while(1){
      pause();  
    }; /* poner mejor un pause dentro del cuerpo del while menos recursos*/
    return 0;
}