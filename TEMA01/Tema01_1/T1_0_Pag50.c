#include <stdio.h>
#include <string.h>

int main(){
    char linea[]= "usuario@password";
    char * puntero = strstr(linea,"@"); //busca subcadena en cadena
    printf("Ejemplo de strstr(cad1,cad2)\n");
    printf("--------------------------------------\n");
    printf("linea[]=\"usuario@password\"\n");
    printf("vamos a localizar @\n");
    printf("strstr(linea,\"@\")=devuelve un puntero con posicion\n");
    *puntero = '\0'; //cambia @ por \0
    //con eso tenemos dos cadenas en memoria
    printf("usuario:%s  contraseña:%s \n",linea,puntero+1);
    return 0;
}