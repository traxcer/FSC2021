#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define T 40

int main(){
    int fd;
    char b[T];
    ssize_t r;
    ssize_t w;
    //abro para escribirlo
    if((fd= open("data.dat", O_WRONLY | O_APPEND))<0){
        perror("open");
    }
    if ((w=write(fd,"hello world\n",strlen("hello world\n")))<0){
        perror("write");
        exit(1);
    }
    else
        printf("Se escribieron %lu bytes en \'data.dat\'\n",w);
    if (close (fd)<0){
        perror("close");
        exit(1);
    }
    //abro para leerlo
    if((fd= open("data.dat", O_RDONLY))<0){
        perror("open");
    }
    if ((r=read(fd,b,T))==0)
        printf("Fin del fichero\n");
    else if (r<0){
        perror("read");
        exit(1);
    } 
    else
        printf("Leidos %lu bytes:%s\n",r,b);
    if (close (fd)<0){
        perror("close");
        exit(1);
    }
}


