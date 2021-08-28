#include <stdio.h>

int main(int argc, char *argv[]){
    for(int i=0;i<argc;++i)
        printf("%s\n", argv[i]);
}

/*  argc: Numero de argumentos (palabras) que se pasan.
    argv: Array de Cadenas de Caracteres.
    
    En el argv[0] está el nombre del programa

*/