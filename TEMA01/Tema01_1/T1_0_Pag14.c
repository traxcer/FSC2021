#include <stdio.h>

//Define estructuras con los mismos datos pero orden distinto
struct X{
        short s;
        int i;
        char c;
    
};
struct Y{
        int i;
        char c;
        short s;
};
struct Z{
        int i;
        short s;
        char c;
    
};

int main(){
    struct X X;
    struct Y Y;
    struct Z Z;

    size_t sizeX= sizeof(X);
    size_t sizeY= sizeof(Y);
    size_t sizeZ= sizeof(Z);

    printf("X = %ld, Y = %ld, Z= %ld\n",sizeX,sizeY,sizeZ);
return 0;
}