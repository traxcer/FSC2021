#include <stdio.h>

int main(){
    const int TAM_ARRAY=3; 
    int mi_array[TAM_ARRAY]={1,2,3}; //inicia todas las casillas

    int mi_array2[]={1,2,3,4};//resuelve tamaño el compilador

    mi_array[0]=0;

    typedef int TipoArray[TAM_ARRAY];
    TipoArray otro_array;
    
return 0;
}
