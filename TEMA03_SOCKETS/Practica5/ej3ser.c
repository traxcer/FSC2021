/* 
Práctica 5. Ejercicio 3
Crear un programa servidor para UDP 

Málaga a 12 de Mayo del 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PUERTO 4950 // Puerto para bind (emparejar)
#define MAXTAMBUFFER 100 // Tamaño del buffer


int main(){
    int descriptorSocket; // descriptor del socket
    struct sockaddr_in direccionServidor; //dirección del socket servidor
    struct sockaddr_in direccionCliente; //dirección del socket cliente
    socklen_t longitudDireccion; //longitud de la dirección
    int numerodeBytes; //numero de bytes leidos
    char buffer[MAXTAMBUFFER];  //buffer de recepción de datos

    /* creación del socket UDP */
    if ((descriptorSocket = socket(PF_INET, SOCK_DGRAM, 0))==-1){
        perror("socket");
        exit(-1);
    }
    memset (&direccionServidor,0,sizeof(direccionServidor)); //limpia el contenido
    direccionServidor.sin_family=AF_INET;
    direccionServidor.sin_port=htons(PUERTO); //pasa a bigEndian (red)
    direccionServidor.sin_addr.s_addr=INADDR_ANY; //Escucha por cualquier interfaz

    if (bind(descriptorSocket, (struct sockaddr*)&direccionServidor,sizeof(direccionServidor))==-1){
        perror("bind");
        exit(-1);
    }

    longitudDireccion = sizeof(direccionCliente);
    if ((numerodeBytes=recvfrom(descriptorSocket,buffer,MAXTAMBUFFER,0,(struct sockaddr *)&direccionCliente,(socklen_t *)&longitudDireccion))==-1) {
        perror("recvfrom");
        exit(-1);
    }
    printf("Paquete recibido de %s\n", inet_ntoa(direccionCliente.sin_addr));
    printf("El paquete tiene %d bytes de longitud\n", numerodeBytes);
    close(descriptorSocket);
    return 0;
}
