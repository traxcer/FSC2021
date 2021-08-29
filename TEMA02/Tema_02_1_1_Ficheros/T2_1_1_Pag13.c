#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define T 16

int main(){
    int fd;
    char b[T];
    ssize_t leido;
    if((fd= open("data.dat", O_RDONLY))<0){
        perror("open");
    }
    if ((leido=read(fd,b,4))==0){
        perror("read");
        exit(-1);
    }
    printf("Leidos %lu bytes:%s\n",leido,b);
    if ((leido=read(fd,b,T))==0){
        perror("read");
        exit(-1);
    }
    printf("Leidos %lu bytes:%s\n",leido,b);
    if ((leido=read(fd,b,4))==0){
        perror("read");
        exit(-1);
    }
    printf("Leidos %lu bytes:%s\n",leido,b);
}


