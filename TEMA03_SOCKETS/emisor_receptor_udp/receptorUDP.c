/*
FICHERO: receptorUDP

Descripción:    Servidor que espera un paquete en el puerto 4950 
                y muestra contenido

Fecha: 25 Mayo 2021
Programador: Manuel Eloy Gutiérrez Oñate
*/

#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4950
#define T 256



int main(){

int sd;
char buffer[T];
//1. Abrimos el socket
sd=socket(AF_INET,SOCK_DGRAM,0);
if (sd<0){
    perror("socket");
    exit(-1);
}

//2. Vinculamos a dirección y puerto

struct sockaddr_in servidor;
memset(&servidor,0,sizeof(servidor)); //limpiamos estructura
servidor.sin_family = AF_INET;
servidor.sin_port = htons (PORT);
servidor.sin_addr.s_addr = INADDR_ANY; //cualquier tarjeta de red

int r;
r = bind(sd, (struct sockaddr *) &servidor, sizeof(servidor));
if (r<0){
    perror("bind");
    exit(-1);
}

struct sockaddr_in cliente;
memset (&cliente,0,sizeof(cliente)); //limpia
//los datos del cliente se rellenan al llegar el paquete
socklen_t longitudDireccion= sizeof(cliente);

while(1){ //bucle del servidor
    int recibe;
    printf("Esperando un paquete de cualquier cliente....\n");
    recibe = recvfrom(sd,
                    buffer,
                    T, 
                    0, 
                    (struct sockaddr*)&cliente,
                    (socklen_t*)&longitudDireccion);
    if (recibe<0){
        perror("recvfrom");
        exit(-1);
    }   
    printf("Paquete recibido de %s\n", inet_ntoa(cliente.sin_addr));
    printf("El paquete tiene %d bytes de longitud\n", recibe);
    buffer[recibe]='\0'; //convierte a cadena
    printf("El paquete contiene la cadena: %s\n", buffer);
}

r=close (sd);
    if (r<0){
        perror("close");
        exit(-1);
    }   
return 0;
}