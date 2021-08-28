#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h> //para funciones de directorios
#include <stdlib.h> 

int listdir(char* directorio){ 
	
	DIR* dir = opendir(directorio);
	if (!dir){
		printf("error al intentar abrir directorio\n");
		return -1;
	}

	struct dirent* entry;
	printf("Contenidos del directorio:\n");
	while ((entry = readdir(dir)) != NULL) {//va leyendo entradas a medida que se llama
		printf("Nombre de fichero: %s\n", entry->d_name);
		//utiliza esta funcion de otro ejercicio:
		//estadof(entry->d_name);
		printf("\n\n");
	}

	if (closedir(dir) == -1){
		printf("problema al cerrar directorio\n");
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[]){

	if (argc < 2){
		printf("Necesito al menos un argumento: el nombre del fichero\n");
		return -1;
	}
	listdir(argv[1]); //con funciones de libreria de C
	return 0;
}