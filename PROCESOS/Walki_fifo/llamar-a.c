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
    int tty;
    char terminal[MAX];
    char *logname;
    char *getenv();
    struct utmp *utmp;
    struct utmp *getutent();
    void fin_de_transmision();

    if (argc !=2){ //Comprobamos los parametros del programa
        printf("Forma de uso: %s usuario \n",argv[0]);
        exit(-1);
    }
    logname=getenv("LOGNAME");
    if EQ(logname,argv[1]){
        printf("Comunicación con uno mismo, no permitida.\n");
        exit(0);
    }
    while((utmp=getutent())!= NULL && strncmp(utmp->ut_user, argv[1], sizeof(utmp->ut_user))!=0);
    if(utmp==NULL){
        printf("El usuario %s no ha iniciado la sesión.\n", argv[1]);
        exit (-1);
    }
    sprintf(nombre_fifo_12,"/tmp/%s_%s", logname, argv[1]);
    sprintf(nombre_fifo_21,"/tmp/%s_%s", argv[1], logname);

    unlink (nombre_fifo_12);
    unlink (nombre_fifo_21);
    umask (~666); //Permisos por defecto para este proceso
    if (mkfifo(nombre_fifo_12,0666)==-1){
        perror("fifo");
        exit(-1);    
    }
    if (mkfifo(nombre_fifo_21,0666)==-1){
        perror("fifo");
        exit(-1);    
    }
    sprintf(terminal,"/dev/%s", utmp->ut_line);
    if ((tty=open(terminal,O_WRONLY))==-1){
        perror("open");
        exit(-1);
    }
    sprintf(mensaje,"\n\t\tLLAMADA PROCEDENTE DEL USUARIO %s\07\07\07\n"
                    "\t\tRESPONDER ESCRIBIENDO: responder-a %s\n\n",
                    logname,logname);
    write(tty,mensaje,strlen(mensaje)+1);
    close (tty);

    printf("Esperando respuesta...\n");

    if ((fifo_12=open(nombre_fifo_12,O_WRONLY))==-1 || (fifo_21=open(nombre_fifo_21,O_RDONLY))==-1){
        if (fifo_12==-1)
            perror(nombre_fifo_12);
        else
            perror(nombre_fifo_21);
        exit(-1);
    }
    printf("LLAMADA ATENDIDA. \07\07\07\n");

    signal(SIGINT, fin_de_transmision);//Armamos manejador para Ctrl+C salir

    do{ //Bucle de envio de mensajes
        printf("<==");
        fgets(mensaje, sizeof(mensaje),stdin);
        write (fifo_12, mensaje, strlen(mensaje)+1);
        if (EQ(mensaje,"cambio\n"))
            do{
                printf("==>");
                fflush(stdout);
                read(fifo_21,mensaje,MAX);
                printf("%s",mensaje);
            } while(!EQ(mensaje,"cambio\n")&& !EQ(mensaje,"corto\n"));
    } while(!EQ(mensaje,"corto\n"));
    printf("FIN DE TRANSMISIÓN.\n");
    close (fifo_12);
    close (fifo_21);
    exit(0);
}


void fin_de_transmision(int sig){
    sprintf(mensaje,"corto\n");
    write(fifo_12,mensaje,strlen(mensaje)+1);
    printf("FIN DE TRANSMISION.\n");
    close (fifo_12);
    close (fifo_21);
    exit(0);
}