/*EJEMPLO: ARGUMENTOS PASADOS POR VALOR */

#include <stdio.h>

void doble (int i) {
    i= i+i;
}

int main(){
    int x=5;
    doble(x);
    printf("%d\n",x);  //resulta 5
    /* Resulta 5 pues lo que se hace es envia una copia de la
    variable x a la función, y no se modifica el valor original.*/
return 0;
}