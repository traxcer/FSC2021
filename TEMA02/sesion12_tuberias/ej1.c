/* 
 



El hijo, por su parte, recibe la información del padre y, análogamente, filtra el 
contenido que le llega y escribe una copia modificada con el contenido filtrado. 
El filtro que aplica cada proceso es el siguiente:
Padre: convierte todas los caracteres a minúscula (ver la función tolower() en el manual)
Hijo: sustituye dígitos por una secuencia de caracteres conformada de la siguiente manera:

Cadena origen: “a2b”
Cadena filtrada: “a|**|b”

Es decir, cada dígito se sustituye por dos barras verticales que hacen de delimitador, y 
tantos asteriscos como valor tenga el dígito. Use la función void sustituir(char * input, 
char ** output); pedida como tarea de seguimiento de la Sesión 3, y recuerde liberar 
adecuadamente los recursos que emplea.
El nombre de los ficheros temporales que escribe cada proceso se generará usando el nombre 
recibido como argumento, y concatenándole “.f1” o “.f2” en el proceso padre e hijo, 
respectivamente. Es decir:

Padre:
Nombre origen (que llega como argumento): “data.txt”
Nombre destino (con el contenido filtrado en el padre): “data.txt.f1”

Hijo
Nombre origen (que llega como argumento): “data.txt”
Nombre destino (con el contenido filtrado en el padre y en el hijo): “data.txt.f2”

Notas:
Nótese que tendrá que implementar algún mecanismo que permita distinguir al proceso hijo cuándo termina un fichero y empieza el siguiente.
El hijo ha de finalizar su ejecución cuando el padre se desconecta de la pipe. En ningún caso deberá utilizar la información contenida en argc/argv a tal efecto (sólo para generar el nombre de los ficheros de salida).
Se debe garantizar que se lee y escribe lo esperado.

Prueba 1: Compilación
Prueba de funcionamiento

Si tenemos dos ficheros data1.txt y data2.txt con el siguiente contenido:
### data1.txt ###
Hola12
### data2.txt ###
a2B
la llamada ./filtrar data1.txt data2.txt deberá generar los cuatro ficheros siguientes:
### data1.txt.f1 ###
hola12
### data1.txt.f2 ###
hola|*||**|
### data2.txt.f1 ###
a2b
### data2.txt.f2 ###
a|**|b
*/

#include <stdio.h>
/*
Escriba un programa en C que reciba como argumento una lista de ficheros de texto, 
y que filtre su contenido de usando para ello dos procesos, padre e hijo, comunicados 
por una pipe.
*/
int main(int argc, char * argv[]){
    if (argv<3){
        fprint("Uso: %d <listaFicheros>",argv[0]);
        exit (-1);
    }

    size_t pid_id;
    

    if (pid_id=(fork())==-1){
        perror("fork");
        exit(-1);
    }
    if(pid_id==0){ // Estamos en hijo

    } else { // Estamos en el padre
        fd= open(argv[1])
    }
/*El padre se encarga de abrir los ficheros, aplicar el primer filtro, guardar una copia 
modificada del fichero con el contenido filtrado y pasarlo al hijo para que aplique el 
segundo filtro.*/

    
}