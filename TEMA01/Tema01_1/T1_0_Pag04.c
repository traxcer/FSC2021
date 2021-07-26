#include <stdio.h>

int main(){
    char nombre[20];
    printf("Dime tu nombre: ");
    gets(nombre);
    printf("Hola %s!\n\n",nombre);
return 0;
}