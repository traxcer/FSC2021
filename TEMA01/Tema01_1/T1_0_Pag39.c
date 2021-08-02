#include <stdio.h>

int main(){
    int numbers[5];
    int *p;

    p= numbers; //puntero a la primera posición
    *p=10; //asigna al numbers[0]
    p++; //p incrementa una posición
    *p=20;//asigna a numbers[1]
    p= &numbers[2]; //asigna al puntero la direccion de numbers[2]
    *p=30; //asigna a numbers[2]
    p= numbers + 3; //asigna al puntero la direccion de numbers[3]
    *p=40; //asigna a numbers[3]
    p= numbers; //puntero a la primera posición
    *(p+4)=50; //escribe en la direccion numbers[4]

//cvhequeamos lo hecho
for(int i=0;i<5;i++)
    printf("%d, ",numbers[i]);
printf("\n");

}