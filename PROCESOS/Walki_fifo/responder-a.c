#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>
#include <signal.h>
#include <string.h>

#define MAX 256
#define EQ(str1,str2) (strcmp(str1,str2)==0)

int fifo_12;
int fifo_21;
char nombre_fifo_12[MAX];
char nombre_fifo_21[MAX];
char mensaje[MAX];

int main(int argc, char * argv[]){
    char *logname;
    char *getenv();
    void fin_de_transmision(int sig);

    if (argc !=2){ //Comprobamos los parametros del programa
        printf("Forma de uso: %s usuario \n",argv[0]);
        exit(-1);
    }

    logname=getenv("LOGNAME");
    if EQ(logname,argv[1]){
        printf("Comunicación con uno mismo, no permitida.\n");
        exit(0);
    }

    sprintf(nombre_fifo_12,"/tmp/%s_%s", argv[1], logname);
    sprintf(nombre_fifo_21,"/tmp/%s_%s", logname, argv[1]);
    
    if ((fifo_12=open(nombre_fifo_12,O_RDONLY))==-1 || (fifo_21=open(nombre_fifo_21,O_WRONLY))==-1){
        perror(nombre_fifo_21);
        exit(-1);
    }
    
    signal(SIGINT, fin_de_transmision);//Armamos manejador para Ctrl+C salir

    do{ //Bucle de recepcion de mensajes
        printf("==>");
        fflush(stdout);
        read(fifo_12,mensaje, MAX);
        printf("%s",mensaje);
        if (EQ(mensaje,"cambio\n"))
            do{
                printf("<==");
                fgets(mensaje, sizeof(mensaje),stdin);
                write (fifo_21, mensaje, strlen(mensaje)+1);                
            } while(!EQ(mensaje,"cambio\n")&& !EQ(mensaje,"corto\n"));
    } while(!EQ(mensaje,"corto\n"));
    printf("FIN DE TRANSMISIÓN.\n");
    close (fifo_12);
    close (fifo_21);
    exit(0);
}
    void fin_de_transmision(int sig){
        sprintf(mensaje,"corto\n");
        write(fifo_21,mensaje,strlen(mensaje)+1);
        printf("FIN DE TRANSMISION.\n");
        close (fifo_12);
        close (fifo_21);
        exit(0);
    }