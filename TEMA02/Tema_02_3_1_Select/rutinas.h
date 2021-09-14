/* rutinas.h */

void copia_fdset(fd_set * destino, fd_set *origen, int maxfdmasuno){
    for(int i=0;i<maxfdmasuno;i++){
        if(FD_ISSET(i,origen))
            FD_SET(i,destino);
    }
}
void print_fdset(char * nombre, fd_set *fds, int maxfdmasuno){
    printf("fdSet: %s Patron:[",nombre);
    for (int i=0;i<maxfdmasuno;i++)
        printf("[%d:%d]",i, FD_ISSET(i,fds));
    printf("\n");
}
ssize_t write_n(int fd,void *mensaje, size_t longitud_mensaje){
    ssize_t a_escribir = longitud_mensaje;
    ssize_t escrito;
    ssize_t total_escrito;
    do{
        errno=0;
        escrito = write(fd,mensaje+total_escrito,longitud_mensaje);
        if (escrito>=0){
            total_escrito+=escrito;
            a_escribir-=escrito;
        }
    } while(((escrito>0)&&(total_escrito<longitud_mensaje)) || errno==EINTR);
    if (total_escrito>0)
        return total_escrito;
    else
        return escrito;
            
}
