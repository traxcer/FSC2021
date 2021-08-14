#include <stdio.h>
#include <string.h>

int main(){
    char cad1[]= "Uno";
    char cad2[]= "Dos";
    printf("--------------------------------------\n");
    printf("Ejemplo strcmp(cad1,cad2)\n");
    printf("devuelve 0 si las cadenas son iguales,\n");
    printf("u otro valor si son distintos\n");
    printf("--------------------------------------\n");
    printf("cad1: %s\n",cad1);
    printf("cad2: %s\n",cad2);
    printf("strcmp(cad1,cad2) = %i\n",strcmp(cad1,cad2));
    if(strcmp(cad1, cad2) ==0){
        printf("Las cadenas son iguales\n");
    } else {
        printf("Las cadenas son distintas pues el resultado es:%d\n",strcmp(cad1,cad2));
    }
    printf("--------------------------------------\n");
    strcpy(cad2,"Uno");
    printf("cad1: %s\n",cad1);
    printf("cad2: %s\n",cad2);
    printf("strcmp(cad1,cad2) = %i\n",strcmp(cad1,cad2));
    if(strcmp(cad1, cad2) ==0){
        printf("Las cadenas son iguales\n");
    } else {
        printf("Las cadenas son distintas pues el resultado es:%d\n",strcmp(cad1,cad2));
    }
    return 0;
}