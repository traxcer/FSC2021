/* PUNTERO A FUNCIONES */
#include <stdio.h>

int f(){ //puntero a funcion que devuelve un entero
    printf("Todo OK...\n");
    return 0;
}

int main(){
    int (*pf)();
    pf=f;
    pf();
}