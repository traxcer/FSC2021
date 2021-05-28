#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>

#define TAM_BUFFER 1024
#define RESPUESTA_OK 0
#define RESPUESTA_ERR 1
#define SUM 0
#define RES 1
#define MUL 3
#define DIV 4

struct DatosEsclavo{
    int pipe_padre_a_hijo[2];
    int pipe_hijo_a_padre[2];
};

int get_max_fd(int actual, int nuevo){
    if (actual>=nuevo)
        return actual;
    else 
        return nuevo;
}

int traduce_a_binario(char *input,char*output){
    //int resultado=0;
    if (strncmp(input,"SUM",3))
        output[0]=SUM;
    else if(!strncmp(input,"RES",3))
        output[0]=RES;
    else if(!strncmp(input,"MUL",3))
        output[0]=MUL;
    else if(!strncmp(input,"DIV",3))
        output[0]=DIV;
    else
        return -1;
    
    char * posicion_espacio1=strstr(input," ");
    char * posicion_espacio2=strstr(posicion_espacio1+1," ");
    if (posicion_espacio1==NULL || posicion_espacio2==NULL)
        return -1;
    
    uint16_t x = (uint8_t)atoi(posicion_espacio1+1);
    uint16_t y = (uint8_t)atoi(posicion_espacio2+1);
    output[1]=x;
    output[2]=y;
    return 0;
}



int main(){
    int max_descriptor;
    char buffer [TAM_BUFFER];
    fd_set cjto_descriptores, cjto_modificado;
    pid_t pid;
    struct DatosEsclavo esclavo;
    
    signal(SIGCHLD,SIG_IGN);
    
    pipe(esclavo.pipe_padre_a_hijo);
    pipe(esclavo.pipe_hijo_a_padre);

    if ((pid=fork())==-1){
        perror ("fork");
        exit(-1);
    }
    if (pid > 0){  //Proceso PADRE
        FD_ZERO(&cjto_descriptores);
        FD_SET (esclavo.pipe_padre_a_hijo[0],&cjto_descriptores);
        FD_SET (esclavo.pipe_hijo_a_padre[0],&cjto_descriptores);
        FD_SET (0,&cjto_descriptores);

        max_descriptor=get_max_fd(esclavo.pipe_hijo_a_padre[0],esclavo.pipe_padre_a_hijo[0]);

        printf("operación->\n");

        while(1){  //Bucle sin fin
            int n;
            //int proximo_hijo=0;
            memcpy (&cjto_modificado,&cjto_descriptores,sizeof(fd_set));
            int resultado=select(max_descriptor+1,&cjto_modificado,NULL,NULL,NULL);
            if (resultado <0){
                perror("select");
                exit(-1);
            }
            if(FD_ISSET(esclavo.pipe_hijo_a_padre[0],&cjto_modificado)){ //hay datos del hijo
                n= read(esclavo.pipe_hijo_a_padre[0],buffer,1);
                if (buffer[0] == RESPUESTA_OK){
                    read(esclavo.pipe_hijo_a_padre[0],&resultado,2);
                    printf("El resultado es: %d\n", resultado);
                }
                else
                    printf("La operación no es válida\n");
            }
            if(FD_ISSET(0,&cjto_modificado)){ //hay datos del teclado
                n= read(0,buffer,TAM_BUFFER);
                if(n>0){
                    buffer[n-1]='\0';
                    printf("buffer inicial: %s\n", buffer);
                    char out[3];
                    if(traduce_a_binario(buffer,out)<0)
                        continue; //sale del bucle
                    printf("out inicial: %s\n", out);
                    write(esclavo.pipe_padre_a_hijo[1],out,3);
                }
                printf("operación:>\n");
            }
        } //fin while
    } //fin del padre
    else if (pid==0){  //proceso del hijo
        uint16_t resultado;
        uint8_t code;
        while(1){
            code= RESPUESTA_OK;
            read(esclavo.pipe_padre_a_hijo[0],buffer,1);
            switch (buffer[0])
            {
            case SUM/* constant-expression */:
                /* code */
                resultado= buffer[1]+buffer[2];
                break;
            case RES/* constant-expression */:
                /* code */
                resultado= buffer[1]-buffer[2];
                break;
            case MUL/* constant-expression */:
                /* code */
                resultado= buffer[1]*buffer[2];
                break;
            case DIV/* constant-expression */:
                /* code */
                resultado= buffer[1]/buffer[2];
                break;
            default:
                code= RESPUESTA_ERR;
                break;
            }
            write(esclavo.pipe_hijo_a_padre[1],&code,1);
            if (code==RESPUESTA_OK)
                write(esclavo.pipe_hijo_a_padre[1],&resultado,2);
        }
        
    }//fin del hijo
    else {
        close (esclavo.pipe_padre_a_hijo[0]);
        close (esclavo.pipe_hijo_a_padre[0]);
        close (esclavo.pipe_padre_a_hijo[1]);
        close (esclavo.pipe_hijo_a_padre[1]);
        perror("fork");
        exit(-1);
    }
}