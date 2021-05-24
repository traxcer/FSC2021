#include <stdio.h>
#include <signal.h>
#include <sys/select.h>

#define TAM_BUFFER 1024

struct DatosEsclavo{
    int pipe_padre_a_hijo[2];
    int pipe_hijo_a_padre[2];
};

int get_max_fd(int actual, nuevo){
    if (actual>=nuevo)
        return actual;
    else 
        return nuevo;
}


int main(){
    int i, max_descriptor;
    char buffer [TAM_BUFFER];
    fd_set cjto_descriptores, cjto_modificado;
    pid_t pid;
    struct DatosEsclavo esclavo;
    
    signal(SIGCHLD,SIG_IGN);
    
    pipe(esclavo.pipe_padre_a_hijo);
    pipe(esclavo.pipe_hijo_a_padre);

}