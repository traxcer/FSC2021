/*EJEMPLO: ARGUMENTOS PASADOS POR REFERENCIA */

#include <stdio.h>

void doble (int *i) {
    *i= (*i)+(*i);
}

int main(){
    int x=5;
    doble(&x);
    printf("%d\n",x);  //resulta 10 CORRECTO
    /* Resulta 10 pues lo que se hace es envia la dirección de la
    variable a una copia del puntero de la función, y se modifica 
    el valor de la direccion de memoria original.*/
return 0;
}