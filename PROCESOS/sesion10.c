/*
Implemente un programa C con tres procesos que ejecutan concurrentemente: 
    un padre y dos hijos de forma indefinida. 
        -El proceso hijo1, cada 2 segundos, hace dos cosas: 
        envía la señal SIGUSR1 al proceso padre y muestra la cadena 
        Soy el proceso hijo1 con pid = 7763: papá, despierta a mi hermano. 

        -El proceso padre atiende SIGUSR1 enviando esta señal al hijo2 e imprimiendo por pantalla: 
        Soy el proceso padre con pid = 7760: ya voy!. 
    El proceso hijo2, al recibir la señal, muestra la cadena: 
    Soy el proceso hijo2 con pid = 7764: ya estoy despierto. Los pid mostrados 
    en el ejemplo son arbitrarios, y se deben obtener usando la función getpid().

Nota 1: por razones "ajenas a mi voluntad", las pruebas no funcionan cuando se usa printf(). 
Para que se pasen correctamente, hay que usar la función write() para escribir por pantalla. 
Así, el equivalente de:
printf("Soy proceso hijo1 con PID=%d: papá, despierta a mi hermano\n",getpid());
sería:
#define T 256
char msg[T];
sprintf(msg,"Soy proceso hijo1 con PID=%d: papá, despierta a mi hermano\n",getpid());
write(1,msg,strlen(msg));

Nota 2: El uso de la función kill(pid_t pid, int signo) saca un warning, independientemente 
de las librerías incluidas. Hay dos formas de solucionarlo: compilar sin -std=c99, que es lo 
que se hace en Siette, o bien incluir el siguiente #define _POSIX_SOURCE al principio del código.

Prueba 1: Compilación
Prueba de funcionamiento
Un ejemplo de ejecución sería:
#Transcurren 2 segundos 
Soy el proceso hijo1 con PID=1303: papá, despierta a mi hermano
Soy el proceso padre con PID=1301: ya voy!
Soy el proceso hijo2 con PID=1304: ya estoy despierto
#Transcurren 2 segundos 
Soy el proceso hijo1 con PID=1303: papá, despierta a mi hermano
Soy el proceso padre con PID=1301: ya voy!
Soy el proceso hijo2 con PID=1304: ya estoy despierto
#Transcurren 2 segundos 
Soy el proceso hijo1 con PID=1303: papá, despierta a mi hermano
Soy el proceso padre con PID=1301: ya voy!
Soy el proceso hijo2 con PID=1304: ya estoy despierto
#Transcurren 2 segundos 
Soy el proceso hijo1 con PID=1303: papá, despierta a mi hermano
Soy el proceso padre con PID=1301: ya voy!
Soy el proceso hijo2 con PID=1304: ya estoy despierto
#Transcurren 2 segundos 
...
donde, lo que aparece en rojo, es el tiempo que el programa está a la espera de que ocurra algún 
evento.*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define T 256

void manejador_SIGUSR1(int sig){
    signal(SIGUSR1,manejador_SIGUSR1);

}

int main(){
int i;
int pid_hijo1;
int pid_hijo2;
int pid_padre=getpid(); //Aqui guardo el pid del padre
char msg[T];

signal(SIGUSR1,manejador_SIGUSR1);

    /* El padre crea dos procesos hijos */
    for (i=0;i<2;i++){
    if((pid_hijo1 = fork())<0){
        perror("fork");
        exit (-1);
    }
    if (pid_hijo1 == 0){ //Estoy en el hijo1
    //lo enclaustro para que no se lie con el siguiente
        while(1){ //iteración infinita
            kill(pid_padre, SIGUSR1);
            // printf("Soy el proceso hijo con pid = %d: papá, despierta a mi hermano.\n",getpid());
            sprintf(msg,"Soy proceso hijo1 con PID=%d: papá, despierta a mi hermano\n",getpid());
            write(1,msg,strlen(msg));
            sleep(2); //espero 2 segundos para repetir
        }
    }
    if((pid_hijo2 = fork())<0){
        perror("fork");
        exit (-1);
    }
    if (pid_hijo2 == 0){ //Estoy en el hijo2

    }
    if (pid_hijo !=0){ //Estoy en el padre
        signal(SIGUSR1,manejador_SIGUSR1); //armo el manejador

    }
    }
}

