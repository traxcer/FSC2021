/*
FICHERO: emisorUDP

Descripción: Envia un datagrama al puerto 4950

Fecha: 25 Mayo 2021
Programador: Manuel Eloy Gutiérrez Oñate
*/

#define PUERTO 4950
#define MAX_TAM_BUFFER 100

int main(){
    int descriptorSocket;
    struct sockaddr_in direccionReceptor;
    struct sockaddr_in direccionEmisor;
    int longitudDireccion;
    int numeroDeBytes[MAX_TAM_BUFFER];

    //Creación del Socket UDP
    if((descriptorSocket=socket(PF_INET,SOCK_DGRAM,0))==-1){
        perror("socket");
        exit(-1);
    }
    //parametros del receptor
    direccionReceptor.sin_family= AF_INET; 
    direccionReceptor.port = hton(PUERTO); //puerto
    direccionReceptor.sin_addr.s_addr = INADDR_ANY; //escucha cualquiera
    memset(&(direccionReceptor.sin_zero,'\0',8)); // pone a 0 el campo no usado

    if(bind(descriptorSocket,(struct sockaddr*)&direccionReceptor, sizeof(struct sockaddr))==-1){
        perror("bind");
        exit(-1);
    }

}