#include <stdio.h>
#include <stdlib.h>
void suma2 (int * n);
int main(){
    int *ptr=(int*)malloc(sizeof(int));
    *ptr=5;
    printf("===============================================\n");
    printf("VALORES EN EL MAIN\n");
    printf("===============================================\n");
    printf("Direccion de ptr en main, %x\n",&ptr);
    printf("Contenido de ptr en main, %x\n",ptr);
    printf("Contenido en la memoria donde apunta ptr en main, %x\n\n",*ptr);
    suma2(ptr);
    printf("Contenido en la memoria donde apunta ptr en main despues de sumar, %x\n\n",*ptr);
return 0;
}

void suma2 (int * ptr){
    *ptr=*ptr+2;
    printf("===============================================\n");
    printf("VALORES EN LA FUNCION\n");
    printf("===============================================\n");
    printf("Direcciones de la variable de puntero en suma2, %x\n",&ptr);
    printf("Contenido de la variable de puntero en suma2, %x\n",ptr);
    printf("Contenido en la memoria donde apunta ptr en suma2, %x\n\n\n",*ptr);
}