#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p =(int*)malloc (sizeof(int));
    *p=7;
    printf("p = %p, *p = %d ",p,*p);
    free(p);
    //PELIGRO, deje de reservar esa posición y puede machacarse
    printf("p = %p, *p = %d \n\n",p,*p);
    *p=7;
    printf("p = %p, *p = %d \n\n",p,*p);
return 0;
}

/* Traducción mia de man malloc(3) y free(3)

Incluido junto a malloc en <stdlib.h>
==================================================================
Prototipo: void * malloc(size_t tamaño);
==================================================================
*Asigna tamaño bytes y devuelve un puntero a la memoria asignada.
*Ojo, la memoria no es inicializada.
*Si el tamaño es 0, devuelve NULL o un valor unico de puntero que 
 posteriormente puede ser liberado por free().
*En caso de error tambien devuelve NULL
NOTAS: Se usa asignación optimista, no se garantiza que la memoria
esté disponible.
==================================================================
Prototipo: void free(void *puntero);
==================================================================
* Libera el espacio de memoria apuntado por puntero, el cual debe 
 haber sido devuelto por una llamada anterior a malloc(), en otro
 caso, o si se ha llamado antes a free() que a mallos, se daría un
 comportamiento inesperado.
*Si puntero es NULL no se efectua ninguna operación.
*No vevuelve ningun valor
*/
