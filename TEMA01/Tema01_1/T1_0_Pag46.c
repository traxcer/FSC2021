#include <stdio.h>
#include <string.h>

int main(){
    char cadena[] = "Hola mundo";
    printf ("La cadena tiene %li caracteres\n", strlen(cadena));
    // no incluye '\0'
    return 0;
}