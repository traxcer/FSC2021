/* Programa ls_fsc que acepte la opción -l y que muestre el directorio en curso
empleando el ejecutable original ls del sistema y la función system.
Consultar system() en el man.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char comando[255]="ls ";  
    if (argc>2)
    {
        fprintf(stderr,"Solo admite el argumento: %s -l\n",argv[0]);
        exit(-1);
    }
    if (argc==2)strcpy
        (comando+3,argv[1]);
    printf("Comando=%s\n\n",comando);
    if((system(comando))==-1){
        fprintf(stderr,"Error en system\n");
        exit (-1);
    }
return 0;
}