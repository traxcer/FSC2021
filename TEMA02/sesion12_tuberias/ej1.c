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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

# define T 255

/*
Escriba un programa en C que reciba como argumento una lista de ficheros de texto, 
y que filtre su contenido de usando para ello dos procesos, padre e hijo, comunicados 
por una pipe.
*/
int main(int argc, char * argv[]){
    if (argc<2){
        printf("Uso: %s <listaFicheros>\n",argv[0]);
        exit (-1);
    }
    char buffer[T];
    char filtro[T];
    char fichero[25];
    int leidos;
    int escritos;
    size_t pid_id;
    int tuberia[2];
    if (pipe(tuberia)==-1){ //abro tuberia
        perror("pipe: ");
        exit (-1);
    }
    if ((pid_id=(fork()))==-1){
        perror("fork");
        exit(-1);
    }
    if(pid_id==0){ // Estamos en hijo
        close (tuberia[1]); //cierra tuberia que no usa
        while ((read(tuberia[0],fichero,25))==0){
            printf("Proceso %d Receptor, esperando mensaje...\n",getpid());
            }
            printf("Proceso %d Receptor, mensaje: %s\n",getpid(),fichero);
            if (strcmp(fichero,"fin")){
                printf("Llego el mensaje de fin...Termino el hijo\n");
                close (tuberia[0]);
                exit(0);
            }
    } 
    else { // Estamos en el padre
        close (tuberia[0]); //cierra tuberia que no usa
        for(int i=1;i<argc;i++){ //bucle que lee la lista de ficheros
            int fdl= open(argv[i],O_RDONLY);
            if (fdl==-1){
                perror("Error abriendo el fichero");
                exit(-1);
            }
            sprintf(fichero,"%s.f1",argv[i]);
            int fde= open(fichero,O_WRONLY|O_CREAT, 0666);
            if (fde==-1){
                perror("Error creando el fichero");
                exit(-1);
            }
            leidos=read(fdl,buffer,T);
            do {
                //pasa a minusculas lo leido
                for (int i=0;i<leidos+1;i++)
                    filtro[i]=tolower((unsigned char)buffer[i]);
                escritos=write(fde,filtro,leidos);
                if (escritos<0){
                    perror("Error write padre");
                    exit(-1);
                }
            } while ((leidos=read(fdl,buffer,T))>0);
        close(fdl);
        close(fde);
        write(tuberia[1],fichero,strlen(fichero)); //manda el fichero al hijo

        }   //fin bucle for de ficheros
        write(tuberia[1],"fin",3); //manda el fichero al hijo
    wait(0); //Espera que termine el hijo
    }
}
/*El padre se encarga de abrir los ficheros, aplicar el primer filtro, guardar una copia 
modificada del fichero con el contenido filtrado y pasarlo al hijo para que aplique el 
segundo filtro.*/

    
