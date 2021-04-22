/*codigoParaEvaluar.c
Evaluación automática: Siette
Málaga a 1 de Marzo del 2021
-------------
DESCRIPCIÓN
-------------
Las pruebas se realizan mediante la invocación de la función mediana(), 
que deben tener el prototipo indicado o, en otro caso, habrá un error 
de compilación. 
Imprima por pantalla el valor del array y de la mediana al terminar la 
función.
*/

#include <stdio.h>
#define T 21
int mediana(int a[T], int size); 

int main()
{
    int a[T] = {7, 17, 205, 92, 130, 198, 189, 55, 107, 4, 194, 78, 193, 190, 204, 176, 46, 175, 118, 17, 80};
    //int a[T] = {201, 77, 62, 87, 42, 202, 176, 151, 170, 146, 181, 105, 209, 34, 29, 40, 129, 171, 67, 87,  11};
    int m = mediana(a,21);
    printf("la mediana de a es %d\n",m);
    // se espera que m = 105
    int b[T] = {201, 77, 62, 87, 42, 202, 176, -76, 170, 146, 181, 105, 209, 34, 29, 40, 129, 171, 67, 87,  11};
    m = mediana(b,21);
    printf("la mediana de b es %d\n",m);
    // se espera que m = -1
}

int mediana(int a[], int size){
        int i,j;
        int aux, posmediana, mediana;
        // Primero ordenamos el array
        for(i = 0; i < size; i++)
            {if (a[i]<0) return -1;
            for(j = 0; j < 5; j++)
                {
                if(a[j] > a[j + 1])
                    {
                    aux = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = aux;
                    }
                }
            }//ya tengo el array ordenado
        posmediana=(size+1)/2;
        if (size%2!=0) //si el numero de elementos es impar
            mediana=a[posmediana];
        else //si es par hago la media de los dos elementos centrales
            mediana=(a[posmediana-1]+a[posmediana+1])/2;
        
return mediana;
}