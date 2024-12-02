#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <stdbool.h> 
#include <time.h> 
#include "gestion_clavier.c"
#include "gestion_temps.c"

void Augmente_taille(int * taille, int * position, int largeur, int taille_original)
{
	if((*taille) > taille_original){return;} // Bonus non accumulable
	
	(*taille) = (*taille) + 1;
	
	if((*position) + (*taille) > largeur){(*position) = (*position) - 1;}
	
	if((*position) - (*taille) < 0){(*position) = (*position) + 1;}
} 

int main()
{ 
	int g =7; //position
	int j = 5; //taille
	int l = 12; 
	int o = 5;
	
	Augmente_taille(&j, &g, l, o);
	
	printf("taille : %d\nposition : %d\n", j, g);
   

    return 1;
}
