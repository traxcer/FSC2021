/*EJEMPLO: ARGUMENTOS PASADOS POR REFERENCIA 
  CON ASIGNACION DINAMICA DE MEMORIA*/

#include <stdio.h>
#include <stdlib.h>

void nuevoValor (int *i) {
    i= (int*) malloc (sizeof(int));
    /* El puntero que llega es una copia del original, el valor 
    de i se machaca con el nuevo asignado, entonces el i usado
    en la función no es el mismo que el usado en el programa */
    *i=7;
}

int main(){
    int x=5;
    nuevoValor(&x);
    printf("%d\n",x);  //resulta 5
    
return 0;
}