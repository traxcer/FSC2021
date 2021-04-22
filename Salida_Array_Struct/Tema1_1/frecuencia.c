#include <stdio.h>

int cuenta (int *array, int n );

int main(){
	int array [100],i;
	
    printf("Introduzca una secuencia de números entre 0 y 9 terminada en número negativo: ");
    do {
		scanf("%d",&array[i]);
        i++;
    } while(array[i-1]>=0);
    i--;
    for (int n=0;n<i;n++){
        printf("\n");
        printf("%d ",n);
        for (int a=0;a<cuenta(array,n);a++){
            printf("*");
        }
        printf("\n");
    }
}

int cuenta (int *array, int n ) {
    int contador=0;
    for (int i=0; i<100; i++){
		if (n == array[i]) 
        contador++;
    }
    return contador;
}