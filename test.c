#include <stdio.h>
//#include <stdlib.h> 
//#include <math.h> 
//#include <stdbool.h> 
//#include <time.h> 
//#include "gestion_clavier.c"
//#include "menu.c"

void plus_un(int * a){
    (*a)++;

}

int main()
{ 

    int a = 10;
    int *ptr = &a;
    plus_un(ptr);
    printf("adresse de la variable int : %p\n", &a);
    printf("valeur stockée par le pointeur : %d\n", *ptr);
    printf("adresse stockée par le pointeur : %p\n", ptr);
    printf("adresse du ptr : %p\n", &ptr);
    return 1;
}
