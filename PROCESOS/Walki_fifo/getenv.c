#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("PATH: %s\n",getenv("PATH"));
    printf("LOGNAME: %s\n",getenv("LOGNAME"));
}