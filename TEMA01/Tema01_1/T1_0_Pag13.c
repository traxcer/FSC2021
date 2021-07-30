#include <stdio.h>

int main(){
    int *puntero;
    long *punterolong;
    size_t tam_int = sizeof(int);
    int var_entera;
    size_t longitud = sizeof(var_entera);
    size_t tam_char = sizeof(char);
    size_t tam_short = sizeof(short);
    size_t tam_long = sizeof(long);
    size_t tam_punt = sizeof(puntero);
    size_t tam_punt_long = sizeof(punterolong);

    printf("Tamaño de variable int= %ld bytes\n",tam_int);
    printf("Tamaño de variable var_entera= %ld bytes\n",longitud);
    printf("Tamaño de variable char= %ld bytes\n",tam_char);
    printf("Tamaño de variable short= %ld bytes\n",tam_short);
    printf("Tamaño de variable long= %ld bytes\n",tam_long);
    printf("Tamaño de variable puntero a entero= %ld bytes\n",tam_punt);
    printf("Tamaño de variable puntero a long= %ld bytes\n",tam_punt_long);

}