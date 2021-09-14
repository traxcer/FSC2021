/* rutinas.h */

/* Función auxiliar para garantizar que se escriben exactamente los bytes
 * que se indican en el tercer parámetro */
ssize_t write_n(int fd,void *mensaje, size_t longitud_mensaje){
    ssize_t a_escribir = longitud_mensaje;
    ssize_t escrito=0;
    ssize_t total_escrito=0;
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

/* Función auxiliar para garantizar que se leen exactamente los bytes
 * que se indican en el tercer parámetro */
ssize_t read_n(int fd,void *mensaje, size_t longitud_mensaje){
    ssize_t a_leer = longitud_mensaje;
    ssize_t leido=0;
    ssize_t total_leido=0;
    do{
        errno=0;
        leido = read(fd,mensaje+total_leido,longitud_mensaje);
        if (leido>=0){
            total_leido+=leido;
            a_leer-=leido;
        }
    } while(((leido>0) && (total_leido<longitud_mensaje)) || errno==EINTR);
    if (total_leido>0)
        return total_leido;
    else
        return leido;
            
}
