#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    char cad[]="a35";
    if(isupper(cad[0]))
        printf("%c es mayuscula\n",cad[0]);
    else if(islower(cad[0]))
        printf("%c es minuscula\n",cad[0]);
    if(isdigit(cad[1]))
        printf("En la primera posición está el digito %c\n", cad[1]);

    char str[]="Texto Prueba.\n";
    for (int i=0; i< strlen(str); i++){
        printf("%c", tolower(str[i]));
    }
    printf("\n");
}