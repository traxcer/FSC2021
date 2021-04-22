//Ejemplos de arrays en C++

#include<iostream>
using namespace std;

int main(){
    const int TAM_ARRAY = 10;
    int arr[TAM_ARRAY];
    int in;
    for (int i=0; i <TAM_ARRAY;i++)
        arr[i]=i; //inicia valores del array 
    for (int i=0; i <TAM_ARRAY;i++)
        cout << arr[i]; //muestra valores arr
    cout << "<\nIntroduce un numero a buscar: " << endl;
    cin  >> in;

    int j=0;
    while (j< TAM_ARRAY && arr[j] != in){
        j++;
    }
    if (j== TAM_ARRAY)
        cout << "El numero " << in << " no está en el array" << endl;
    else
        cout << "El numero " << in << " está en la posición " << j << endl;
    return 0;
}