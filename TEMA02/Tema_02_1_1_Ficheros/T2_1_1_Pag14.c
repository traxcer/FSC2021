#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define T 16

int main(){
    int fd1;
    int fd2;
    char b[T];
    ssize_t escrito;
    ssize_t leido;
    if((fd1= open("data.dat", O_WRONLY |O_APPEND))<0){
        perror("open");
    }
    if ((escrito=write(fd1,"123",3))==0){
        perror("write");
        exit(-1);
    }
   //abre para leer 
    if((fd2= open("data.dat", O_RDONLY))<0){
        perror("open");
    }
    if ((leido=read(fd2,b,T))==0){
        perror("read");
        exit(-1);
    }
    printf("Leidos %lu bytes:%s\n",leido,b);
}


