#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <stdbool.h> 
#include <time.h> 
#include "gestion_clavier.c"

int main()
{
	int g = time(NULL);
	
	sleep(5);
	
	int f = time(NULL);
	
	printf("%d\n", f -g); 
	
    return 1;
}
