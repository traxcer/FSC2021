/*
Escriba un programa en C que, implemente la función
   int checkMail(char * email, char * user, char * host); 
que devuelve
0: en caso de que email sea una dirección de correo electrónico bien formada. 
   En nuestro caso, una dirección de correo electrónico está bien formada si tiene 
   formato [user]@[host], donde user y host son dos cadenas de texto de longitud 
   mayor que cero.
-1: cuando en email no aparece el carácter @.
 1: cuando en email las cadenas user o host están vacías. Por ejemplo: @lcc.uma.es o flv@.

Implemente también el programa principal main() de forma que la dirección de correo 
electrónico se reciba como argumento de la función.
Prueba 1: Compilación
Prueba de funcionamiento
Varios ejemplos de ejecución de este programa, llamando a la función checkMail() serían:
              >./checkMail "flv@lcc.uma.es"
               Valor devuelto: 0
               user = flv
               host = lcc.uma.es
              >./checkMail "flv_lcc.uma.es"
               Valor devuelto: -1
              >./checkMail "flv@"
               Valor devuelto: 1
              >./checkMail "@lcc.uma.es"
               Valor devuelto: 1
Aunque se muestra la posible salida del programa, las pruebas se realizarán con llamadas a
la función checkMail(), que debe tener el prototipo indicado o, en otro caso, habrá un error 
de compilación.
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//Prototipo función
int checkMail(char * email, char * user, char * host); 

int main(int argc, char * argv[])
{
    if (argc<2){
        printf("Debe entrar: %s email@host.pp\n",argv[0]);
        return -1;
    }
    printf("Se han pasado %d parametros y el primer parametro es %s\n",argc,argv[1]);
    char * email = (char*)malloc(50*sizeof(char));
    strcpy(email,argv[1]);
    char * usuario = (char*)malloc(50*sizeof(char));
    char * hostname = (char*)malloc(50*sizeof(char));

    printf ("Estado del correo: %d\n",checkMail(argv[1],usuario,hostname));
    printf("Usuario: %s Hostname: %s\n ", usuario, hostname);
}

int checkMail(char * email, char * user, char * host)
{
    char* estado; //puntero con las posiciones
    estado = strchr(email,'@'); //localizo @
    if (estado == NULL ) return -1; //no existe @
    if (estado == email) return 1; //es la primera pos o sea ni hay nombre
    if (estado == email + strlen(email)) return 1;
    memcpy(user,email,estado-email);
    memcpy(host,estado+1,strlen(email));
    return 0;
}