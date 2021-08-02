/*EJEMPLO: ARGUMENTOS PASADOS POR REFERENCIA 
  CON ASIGNACION DINAMICA DE MEMORIA, BIEN*/

#include <stdio.h>
#include <stdlib.h>

void nuevoValor (int **i) {
    *i= (int*) malloc (sizeof(int));
    /* El puntero que llega es una copia del original, y es un puntero
    a un puntero. **i
    Asigno la direccion de memoria a ese puntero *i (desreferencio)
    Y a su contenido le asigno el valor 7 i**=7 */
    **i=7;
}

int main(){
    int *x;
    nuevoValor(&x);
    printf("%d\n",*x);  //resulta 5
    
return 0;
}