#include <stdio.h>
#include <errno.h>

// Mi version de writen

writen(fd, b, n) {
    
    ssize_t a_escribir=n;
    ssize_t escritos=n;
    ssize_t total_escritos;
    

    do{
        errno = 0; //importante inicializar
        escritos=write(fd, b + total_escritos, a_escribir);
        if (escritos >=0){
            total_escritos += escritos;
            a_escribir -=escritos;
        }
    } while (((escritos>0) && (total_escritos<n)) || (errno = EINTR));

    if (total_escritos >0){
        return total_escritos;
    } else { 
        //Para permitir un posible error en la llamada a read.
        return escritos;
    }

}