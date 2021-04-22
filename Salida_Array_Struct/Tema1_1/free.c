//Test de malloc y free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char* p1;
    char* p2;
    p1=(char*)malloc(5*sizeof(char));
    strcpy(p1,"Hola");
    printf("El contenido de p1 es %s\n",p1);
    p2=p1;
    free(p2);
    printf("El contenido de p2 es %s\n",p1);
}

/* El programa devuelve por pantalla lo siguiente:

El contenido de p1 es Hola
El contenido de p2 es 

*/