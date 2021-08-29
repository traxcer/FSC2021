#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/dir.h>

int estadof(char* fichero){
	
	struct stat sf;
	if(stat(fichero, &sf) < 0){
		return -1;
	}

	printf("Tipo de fichero:      \n");
	if(S_ISDIR(sf.st_mode)){
		printf("Es un directorio\n");
	}
	if (S_ISREG(sf.st_mode)) {
		printf("Es un fichero regular\n");
	}

	//%lld es el comodin para long long int (el entero mas largo en la plataforma)
	printf("Tamaño:  %lld bytes\n", (long long) sf.st_size);
	return 0;

}

int listdir(char* directorio){
    DIR* dir = opendir(directorio);
    if (!dir){
        printf("error al intentar abrir el directorio\n");
        return -1;
    }
    struct dirent* entrada;
    printf("El contenido del directorio:\n");
    while((entrada = readdir(dir))!=NULL){
        printf("-----------------------------------------\n");
        printf("Nombre del fichero: %s\n", entrada->d_name);
        //utiliza esta funcion de otro ejercicio
        estadof(entrada->d_name);
        printf("\n");
    }
    if (closedir(dir)==-1){
        printf("problemaal cerrar el directorio\n");
        return -1;
    }
    return 0;   
}

int main(int argc, char* argv[]){

	if (argc < 2) {
		printf("Necesito al menos un argumento: el nombre del directorio\n");
		return 1;
	}
	return (listdir(argv[1]));
}