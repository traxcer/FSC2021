#include <stdio.h>

int main(){
    const int TAM_ARRAY=10;
    int arr[TAM_ARRAY];
    int i; 
    int j;
    int numero;

    for (i=0; i<TAM_ARRAY;i++)
        arr[i]=i;

    for (i=0; i<TAM_ARRAY;i++)
        printf("%d ", arr[i]);
    
    printf("\n");
    printf("\nIntroduce el numero de buscar: ");
    scanf("%d",&numero);
    printf("\nBuscando el numero %d en el array\n",numero);
    j=0;
    while((j<TAM_ARRAY) && (arr[j]!=numero)){
        j++;
    }
    if (j== TAM_ARRAY)
        printf("El numero %d no está en el array\n",numero);
    else
        printf("El numero %d, está en la posición del array %d\n",numero,j);
    
return 0;
}