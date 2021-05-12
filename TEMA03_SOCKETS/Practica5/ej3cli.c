/* 
Práctica 5. Ejercicio 3
Crear un programa cliente para UDP 

Málaga a 12 de Mayo del 2021
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define PUERTO 4950    // puerto donde escucha del receptor

int main(int argc, char *argv[]){
    int descriptorSocket; /* descriptor del socket   */
    struct sockaddr_in direccionServidor; /* dirección del servidor  */
    int numeroDeBytes; /* número de bytes leidos*/
    if(argc!= 3) {
        fprintf(stderr,"uso: emisor dir_ip mensaje\n");
        exit(1);}
    /* para obtener la IP del receptor */
    uint32_t ip_servidor= inet_addr(argv[1]);
    if(ip_servidor== -1){
        perror("inet_addr");
        exit(1);
        }
    /* creaciondel socket UDP */
    descriptorSocket= socket(PF_INET, SOCK_DGRAM, 0);
    if(descriptorSocket== -1) {
        perror("socket");
        exit(1);
        } 
    memset(&direccionServidor, 0, sizeof(direccionServidor));  
    direccionServidor.sin_family= AF_INET;     
    direccionServidor.sin_port= htons(PUERTO); 
    memcpy(&direccionServidor.sin_addr,&ip_servidor, 4);
    numeroDeBytes= sendto(descriptorSocket, argv[2], strlen(argv[2]),0,(struct sockaddr*)&direccionServidor, sizeof(direccionServidor));
    if(numeroDeBytes== -1){
        perror("sendto");
        exit(1);
        }
    printf("Enviados %d bytes a %s\n", numeroDeBytes, inet_ntoa(direccionServidor.sin_addr));
    close(descriptorSocket);
    return 0;
}