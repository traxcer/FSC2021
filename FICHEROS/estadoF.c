#include <stdio.h>
#include <sys/stat.h>

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

int main(int argc, char* argv[]){

	if (argc < 2) {
		printf("Necesito al menos un argumento: el nombre del fichero\n");
		return 1;
	}

	return (estadof(argv[1]));
}