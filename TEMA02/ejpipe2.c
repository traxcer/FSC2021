/* Ejemplo 2 de Pipes para comunicacion bidireccional */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>



#define SIZE 256

int main(int argc, char * argv[]){

    pid_t pid;
    int a[2], b[2], readbytes;
    char buffer[SIZE];
    pipe(a);
    pipe(b);
    if ((pid=fork())<0){
        perror("fork");
        exit(-1);
    } else if (pid==0){ //Hijo
        close(a[1]);
        close(b[0]);
        while ((readbytes = read(a[0], buffer,SIZE))>0)
            write(1,buffer,readbytes);
        close(a[0]);
        strcpy(buffer,"Soy tu hijo hablandote por la otra tuberia\n");
        write(b[1],buffer,strlen(buffer));
        close(b[1]);
        exit(0);
    } else { //Padre
        close(a[0]);
        close(b[1]);
        strcpy(buffer,"Soy tu padre hablandote de una tuberia\n");
        write(a[1],buffer,strlen(buffer));
        close(a[1]);
        while((readbytes=read(b[0],buffer,SIZE))>0){
            write(1,buffer,readbytes);
        close(b[0]);
        wait(0);
        }
    } 
}