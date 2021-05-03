#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>


//Esta funcion utiliza llamadas al sistema operativo
int copiaFichero(char* source, char* target){
	
	int fd_origen, fd_destino;
	char bloque[512];

	if ((fd_origen = open(source, O_RDONLY)) < 0) {
		perror("ha fallado la apertura del fichero\n");
		return -1;
	}

	if ((fd_destino = creat(target, 0777)) < 0)
	{
		perror("ha fallado la creacion del fichero\n");
		return -1;
	}
	
	int bytesRead, bytesWritten;
	while ((bytesRead = read(fd_origen, bloque, 512)) > 0){
		//Ten en cuenta que si pones strlen(buffer) en write, estaría mal porque
		//vamos leyendo bytes, no cadenas de caracteres, las cuales deben terminar en '\0'
		//Tampoco vale escribir 512, porque puede que no se haya llenado el array al leer
		bytesWritten = write(fd_destino, bloque, bytesRead);
		if (bytesWritten < 0){
			perror("error en write\n");
			return -1;
		}
	}
	if(bytesRead == -1){
		perror("error en read\n");
		return -1;
	}

	if ((close(fd_origen) == -1) || (close(fd_destino) == -1)) {
		perror("error cerrando ficheros");
		return -1;
	}

	return 0;
}

int copiaFichero_C(char* source, char* target){
	
	char buffer[512];
	FILE* fd_source, *fd_destino; //en la libreria de C los descritores de fichero son punteros a una estructura FILE

	fd_source = fopen(source, "rb"); //abrir en modo lectura (r) de archivos binarios (b)
	if (fd_source == NULL){
		printf("problema abriendo %s\n", source); //NO pongo perror() puesto que NO es llamada al sistema
		return -1;
	}

	fd_destino = fopen(target, "wb"); //abrir en modo escritura (w) un archivo binario (b)
	if (fd_destino == NULL){
		printf("problema abriendo %s\n", target);
		return -1;
	}

	int bytesRead, bytesWritten;
	//fread: guarda en buffer, bloques de longitud 1 byte, 512 bloques, del fichero f1
	while((bytesRead = fread(buffer,1,512,fd_source)) > 0 ){	
		bytesWritten = fwrite(buffer, 1, bytesRead, fd_destino);
		if (bytesWritten < bytesRead) {
			printf("Error en write\n");
			return -1;
		}
	}
	//otra forma que utiliza la función que comprueba si se ha llegado a fin de fichero
	//feof() solo se puede utilizar si ANTES SE HA HECHO UNA LECTURA (por eso no se pone while(!feof(fd_source)){...})
	/*
	do{
		bytesRead = fread(buffer,1,512,fd_source);
		fwrite(buffer,1,bytesRead,fd_destino);
	}while(!feof(fd_source));
	*/

	fclose(fd_source); fclose(fd_destino);
	return 0;

}

int main(int argc, char* argv[]){
	if (argc < 3) {
		printf("Uso del programa: %s <origen> <destino>\n", argv[0]);
		return 1;
	}
	return copiaFichero(argv[1], argv[2]);
	//utilizando la version con las funciones de la biblioteca de C:
	//return copiaFichero_C(argv[1], argv[2]);
}