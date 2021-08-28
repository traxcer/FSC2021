#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char buf[]="123453468368083080658309860389579275097505";
    
    char ** resto = malloc(sizeof(char)*25);
    unsigned long int arg;
    errno=0;
    arg= strtoul(buf, resto, 0);
    if (errno){
        perror("error en stroul");
        printf("Error en formato de caracteres:\n%s\n",strerror(errno));
    }
        
    printf("El numero obtenido es: %lu\ny el resto es: %s\n", arg, *resto);
}
/*
==========================================================
strtoul, Convierte una cadena a un entero largo sin signo
==========================================================
Nemotécnico: str to ul
=========
Prototipo
=========
unsigned long int strtoul (const char *nptr, char **endptr, int base);
==========================================================
En el MANUAL:
1 - Comandos Generales
2 - Llamadas al sistema
3 - Biblioteca C de funciones.
*/
