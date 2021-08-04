#include <stdio.h>
#include <string.h>

int main(){
    char destino[512];
    char origen[]="Hola que hay";
    strcpy(destino,origen);
    printf("Las cadenas son: %s y %s\n", origen, destino);
return 0;
}