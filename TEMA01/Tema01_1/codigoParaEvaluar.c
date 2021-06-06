#include <stdio.h>
#include <stdlib.h>

// Escriba un programa en C que, da la siguiente definición de datos:
struct BMP {
	int x, y;
	char ** imagen;
};
//implemente las siguientes funciones:
void inicializar(struct BMP * inimagen, int x, int y); 
int aplicarMascara(struct BMP * m, struct BMP * img);
void imprimir(struct BMP *mimagen);
void asignoencruz (struct BMP *mimagen);
void error (char *str, int nro, char *err);

int main(){
    //Pruebas
    struct BMP mimagen;
    inicializar (&mimagen,10,15);
    imprimir (&mimagen);
    printf("\nImagen asignada una cruz\n");
    asignoencruz (&mimagen);
    imprimir (&mimagen);
return 0;
}

void inicializar (struct BMP *inimagen, int x,int y){
    inimagen->x=x; //Guarda el tamaño de la imagen
    inimagen->y=y;
    // Resrvamos memoria para imagen
    if ((inimagen->imagen=(char **)malloc(x*sizeof(char*)))==NULL)
        error (__FILE__, __LINE__, "Error asignando memoria");
    for (int i=0; i < x; i++)
        if ((inimagen->imagen[i]=(char *)malloc(y*sizeof(char)))==NULL)
            error (__FILE__, __LINE__, "Error asignando memoria");
    
    //Recorro matriz y asigno valores
    for (int xfila=0;xfila<x;xfila++){ //Recorro filas
        for(int ycol=0;ycol<y;ycol++){  //Recorro columnas
                inimagen->imagen[xfila][ycol]='0';
        }
    }
}
void asignoencruz (struct BMP *mimagen)
    {//Recorro matriz y asigno valores
    for (int xfila=0;xfila<mimagen->x;xfila++){ //Recorro filas
        for(int ycol=0;ycol<mimagen->y;ycol++){  //Recorro columnas
            if (xfila==ycol || ycol+1== mimagen->y-xfila) //Asigno a uno en forma de aspa
                mimagen->imagen[xfila][ycol]='1';
            else
                mimagen->imagen[xfila][ycol]='0'; //Asigno a 0 el resto
        }
    }
    }

void imprimir(struct BMP *mimagen)
{
    for (int i=0;i < mimagen->x ;i++)
    { //Recorro filas
        for(int j=0;j < mimagen->y ;j++)
        { //Recorro columnas
            printf("%c",(char) mimagen->imagen[i][j]); //Asigno a 0
        }
        printf("\n"); //salta de fila
    }
}
int aplicarMascara(struct BMP * m, struct BMP * img){
    //Dimesiones distintas
    if (m->x != img->x || m->y != img->y){
        printf("ERROR: Dimensiones de la matriz y mazcara no coinciden.\n");
        return -1;
    }
    //Aplico mascara a la imagen
    for (int xfila=0;xfila<img->x;xfila++){ //Recorro filas
        for(int ycol=0;ycol<img->y;ycol++){  //Recorro columnas
            if (img->imagen[xfila][ycol]=='1' && m->imagen[xfila][ycol]== '0')
                img->imagen[xfila][ycol]= '0';//Aplica mascara
        }
    }
return 0;
}

void error (char *str, int nro, char *err){
    fprintf(stderr, "\n%s (%d). ERROR: %s. \n",str, nro, err);
    exit (-1);
}