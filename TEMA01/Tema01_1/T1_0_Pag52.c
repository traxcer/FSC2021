#include <stdio.h>

int main(){
printf("Ejemplos de scanf\n");
printf("-----------------\n");
printf("Introduce un numero y luego una cadena [enter]:");
int x;
scanf("%d", &x);

char cadena [512];
scanf("%s",cadena);

printf("Introduciste el numero %d y la cadena %s\n",x,cadena);

return 0;
}

/* Problemas de scanf()
Cuando encuentra un delimitador (espacio,tab,etc..), corta la cadena
Ej: Si el usuario escribe "hola y adios" en un scanf tomará solo "hola"
Solución: usar scanf("%[^\n]s", cadena);
Con eso acepta todo hasta \n

ALTERNATIVAS
============
fgets(cadena,MAXLINE,stdin)
    - Antidesbordamiento
    - No quita el \n del final
read(fd=0, cadena,MAXLINE)   <--  NOSOTROS USAREMOS ESTA
    - Llamada al sistema
    - No quita el \n del final
    - No pone el \0 final (no se consideraria cadena)

*/