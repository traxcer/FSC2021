/* 
Ej: Manejo de cadenas.
   Copia una cadena de caracteres origen en otra destino
   Esto hace los mismo que la funcion de libreria:
   strcpy(destino,origen) de <string.h>
*/
#include <stdio.h>

void copia(char destino[], const char origen[]){
    int i=0;
    while (origen[i] != '\0'){
        destino[i]=origen[i];
        i++;
    }
    destino[i]='\0';
}


int main(){
    //prueba
    char origen[]="eloy gutiérrez";
    char destino[25];
    copia (destino, origen);
    printf("destino= %s\n", destino);
}

/* Funciones de manejo de cadenas en <string.h>
strlen(cadena)         -> Tamaño de la cadena
strcpy(destino,origen) -> Copia una cadena en otra
strcat(cad1,cad2)      -> Concatena una cadena tras otra
strcmp(cad1,cad2)      -> Compara cadenas
strstr(cad1,cad2)      -> Busca una cadena dentro de otra
*/