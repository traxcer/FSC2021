#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

void manejador(int s){
    signal(SIGALRM,manejador);
    write(1,".",1);
}

int main(){
    struct itimerval timer;
    struct timeval valor;
    valor.tv_sec = 3; 
    valor.tv_usec = 3000; 
    
    timer.it_value = valor;
    timer.it_interval = valor;  
    
    /* Consultar en   el manual sobre cómo declarar y 
    asignar valores al campo it_interval */
    signal(SIGINT, SIG_IGN);
    signal(SIGALRM,manejador);
    setitimer(ITIMER_REAL, &timer, NULL);
    while(1);
    return 0;
}