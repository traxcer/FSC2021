#include <stdio.h>
#include <string.h>

int main(){
    char destino[512]=" Hola ";
    char origen[]= "que hay";
    strcat(destino, origen); //OJO: asegurar espacio en destino
    printf("El Resultado se strcat(o,d): %s\n", destino);
    return 0;
}