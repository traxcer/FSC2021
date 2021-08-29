#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define T 40

int main(int argc, char * argv[]){
    if (argc<2){
        printf("USAR: %s <fichero>\n",argv[0]);
        exit(1);
    }

    //estructura para stat
    struct stat estado_fichero;
    //Consulto la info
    if((stat(argv[1], &estado_fichero))==0){ //todo ok
        if(S_ISDIR(estado_fichero.st_mode))
            printf("%s es un directorio\n",argv[1]);
        if(S_ISLNK(estado_fichero.st_mode))
            printf("%s es un enlace simbólico\n",argv[1]);
        //if(S_ISSOCK(estado_fichero.st_mode))
        //    printf("%s es un fichero SOCKET\n",argv[1]);
        if(S_ISREG(estado_fichero.st_mode)){
            printf("%s es un fichero regular (normal)\n",argv[1]);
            printf("Tamaño en bytes:%lu\n",estado_fichero.st_size);
        }
    } else {
        perror("stat");
        exit(1);
    }

}
/*
PROTOTIPO: int stat (const char *path,struct stat * buf);
Devuelve info sobre el fichero en la estructura pasada por referencia
Util para recorrer directorios
Campos de la estructura: (en <sys/stat.h>)
mode_t  st_mode     Modo de fichero, ver mknod(2)
ino_t   st_ino      Numero de Inode
dev_t   st_dev      ID del dispositivo conteniendo una entrada de directorio a este fichero
dev_t   st_rdev     ID del dispositivo
nlink_t st_nlink    Numero de enlaces
uid_t   st_uid      ID del usuario al que pertenece
gid_t   st_gid      ID del grupo al que pertenece
off_t   st_size     TAMAÑO DEL FICHERO EN BYTES
time_t  st_atime    Tiempo desde el ultimo acceso al fichero
time_t  st_mtime    Tiempo desde la ultima modificación del fichero
time_t  st_ctime    Tiempo desde el ultimo cambio de estado del fichero
long    st_blksize  Preferido I/O bloque de tamaño
blkcnt_t st_blocks  Numero de bloques de 512 bytes reservados
*/