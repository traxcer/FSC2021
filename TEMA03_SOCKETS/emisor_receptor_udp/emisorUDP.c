/*
FICHERO: emisorUDP

Descripción: Envia un datagrama al puerto 4950

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
#include <netinet/in.h>

#define PUERTO 4950
#define MAX_TAM_BUFFER 100

int main(int argc, char * argv[]){    
    int ds;
    struct sockaddr_in direccionReceptor; //servidor
    int numeroDeBytes; //bytes leidos

    if (argc!=3){
        fprintf(stderr,"uso: dir_ip mensaje\n");
        exit (-1);
    }
    //Creación del Socket UDP
    if((ds=socket(PF_INET,SOCK_DGRAM,0))<0){
        perror("socket");
        exit(-1);
    }
    //Obtenemos la ip del servidor
    uint32_t ip_servidor=inet_addr(argv[1]); //convertimos a red
    if (ip_servidor<0){
        perror("inet_addr");
        exit (-1);
    }
    //rellenamos estructura para el servidor
    memset((&direccionReceptor),0,sizeof(direccionReceptor)); //limpia
    direccionReceptor.sin_family=AF_INET;
    direccionReceptor.sin_port = htons(PUERTO); //puerto
    direccionReceptor.sin_addr.s_addr=ip_servidor;
    
    //enviamos
    numeroDeBytes=sendto(ds, 
        argv[2],
        strlen(argv[2]),
        0, 
        (struct sockaddr *) &direccionReceptor, 
        sizeof(direccionReceptor));
    if (numeroDeBytes<0){
        perror("sendto");
        exit(-1);
    }
    printf("Enviados %d bytes a %s\n",numeroDeBytes,inet_ntoa(direccionReceptor.sin_addr));
    
    if ((close (ds))<0){
        perror("close");
        exit (-1);
    }
    return 0;
}