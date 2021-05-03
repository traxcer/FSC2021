/*
Desarrolle un programa que lea de teclado una cierta cantidad de segundos y muestre su equivalente en semanas, 
días, horas, minutos y segundos, según el siguiente formato

9127145 segundos equivalen a [ 15] semanas, 0 dias, 15:19:05 

2178585 segundos equivalen a [ 3] semanas, 4 dias, 05:09:45 


Prueba 1: Compilación
Prueba de funcionamiento

Varios ejemplos de ejecución de este programa serían:
              >./conversorTemporal
               Introduce un número de segundos: -4
               Se espera un número mayor o igual a cero
              >./conversorTemporal
               Introduce un número de segundos: 2178585
               2178585 segundos equivalen a [  3] semanas, 4 dias, 05:09:45
              >./conversorTemporal
               Introduce un número de segundos: 9127145
               9127145 segundos equivalen a [ 15] semanas, 0 dias, 15:19:05
en donde las partes que aparecen en rojo, son las que escribe el programa y el resto, lo que escribe el usuario. 
Obsérvese que en el formato de salida:
El número de meses aparece entre corchetes y precedido por un espacio en blanco. Ejemplos: [ 3], [ 12], [ 22],
Las horas, minutos y segundos aparecen en el formato hh:mm:ss. 
Ejemplos: 23:04:12, 04:59:59, 12:10:25, etc. (El número de horas nunca será mayor de 23 y el número de minutos y 
segundos nunca será mayor de 59).
El número de días nunca podrá ser mayor que 6 (dado que 7 días constituyen 1 semana)

Para el correcto funcionamiento de las pruebas automáticas, se han de utilizar las funciones printf() y scanf() 
para imprimir por pantalla y leer de teclado, respectivamente.
*/


int main(){
 int iSeg;
 int segEnSemana;
 int semanas;
 int dias;
 int horas;
 int minutos;
 int segundos;
 int resto;


 scanf("Introduce un número de segundos: %d",iSeg);
    if (segundos <=0){
        printf("Se espera un número mayor o igual a cero\n");
        exit (-1);
    }
    segEnSemana=7*24*60*60;

    semanas=(iSeg % segEnSemana);
    resto=iSeg-(semanas*segEnSemana);
    dias= resto % (3600*24));
    
    


    printf("d% segundos equivalen a [%d] semanas, %d días, %2d:%2d:%2d", semanas, dias,horas,minutos,segundos);

}