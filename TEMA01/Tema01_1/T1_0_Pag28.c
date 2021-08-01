#include <stdio.h>
#include <stdlib.h>

    struct MisDatos{
    int dato1;
    int dato2;
    };

int main(){

    struct MisDatos *p = (struct MisDatos *) malloc (sizeof(struct MisDatos));
    (*p).dato1=5;
    printf("\n(*p).dato1=%d\n", (*p).dato1);
    p->dato1=5;
    printf("\np->dato1=%d\n", p->dato1);
}