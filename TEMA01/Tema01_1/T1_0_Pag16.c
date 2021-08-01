#include <stdio.h>

//Define estructuras con los mismos datos pero orden distinto
struct Datos1{
        short s; // short 2 bytes
        char c;  // char  1 byte
        //Se alinea con 2, o sea ocupa: [ssc*] 4 bytes
    
};
struct Datos2{
        long l; // long 8 bytes
        char c; // char 1 byte
        //Se alinea con 8, o sea ocupa: [llll][llll][c***][****] 16 bytes

};

int main(){
    struct Datos1 X;
    struct Datos2 Y;


    size_t sizeX= sizeof(X);
    size_t sizeY= sizeof(Y);


    printf("X = %ld, Y = %ld\n",sizeX,sizeY);
return 0;
}