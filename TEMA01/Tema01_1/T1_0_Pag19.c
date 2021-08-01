#include <stdio.h>

int main(){
    int x=10;
    int *p;
    p=&x;
    *p=20;

    printf("p = %p, x = %d, *p= %d\n",p,x,*p);
return 0;
}