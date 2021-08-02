/* PUNTEROS Y CADENAS DE CARACTERES */

/* Hay que tener precaución porque en C/C++ dicha inicialización 
   declara un stringliteral
   Según el manual, intentar modificar el contenido de cadena, 
   e.g., cadena[0] = ‘H’, resulta en un comportamiento indeterminadon
   En el sistema de nuestra máquina virtual, y para el estándar C99, 
   el siguiente código termina con una violación de segmento.*/
#include <stdio.h> 
int main(){
    char cadenabien[]="hola";
    char * cadenamal="hola";
    cadenabien[0]='H';
    printf("puntero cadenabiencadenabien=%s\n",cadenabien);
    cadenamal[0]='H';
}

