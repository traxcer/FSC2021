//Mi primer nuevo programa en C
#include <stdio.h>
int main(){
    printf("Hola\n");
    printf("%s%c\n","Hol",'a');
    //Salida de datos
    int x = 5;
    char hexa=0xFF;
    char c= 'a';
    printf("Texto con comodines: %d %x %c \n",x, hexa,c);
    printf("%d %d\n", 35, x);
    char y= 0xff; //Notacion hexadecimal
    printf("%x\n",y);
    printf("%p\n", &x); /*Imprime direccion de memoria*/
    return 0;
}