#include <stdio.h>

#include <utmp.h>

#define MAX 256
#define EQ(str1,str2) (strcmp(str1,str2)==0)

int fifo_12, fifo_21;
char nombre_fifo_12[MAX];nombre_fifo_21[MAX];
char mensaje[MAX];

int main(int argc, char * argv[]){
    int tty;
    char terminal[MAX];
    char *logname;
    char *getenv();
    struct utmp *utmp;
    struct utmp *getutent();
    void fin_de_trasmision();

    if (argc !=2){
        perror("Forma de uso: %s usuario \n",argv[0]);
        exit(-1);
    }


}