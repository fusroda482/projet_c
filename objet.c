//Fichier objets speciaux

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

// Affichage des objets
void affiche_objets(int objets){

	
	switch(objets){
		
		case -1 : 
			printf("\U0001F480 "); // Skull
			break;
			
		case 1 : 
			printf("O ");
			break;
			
		case 2 : 
			printf("2 ");
			break;
	}//fin switch
}

// Determiner l'objet qui va apparaitre et sa propabilité
int prob_apparition(void){

	int apparition = rand() % 30;
	
	// Propabilité de chaque objets : 
	
	if(apparition > 0 && apparition <= 10){return 1;}
	
	if(apparition > 10 && apparition <=11){return -1;}
	
	if(apparition >11 && apparition <= 12){return 2;}
	
	return 0;
}

// Objet Augmente taille de 1 (objet2)
void Augmente_taille(int * taille, int * position, int largeur, int taille_original) // Passer les carractéristique en pointeur pour les modifier
{
	if((*taille) > taille_original){return;} // Bonus non accumulable
	
	(*taille) = (*taille) + 1; // Augmante la taille de 1 seulement (ou sinon jeu beaucoup trop facile
	
	if((*position) + (*taille) > largeur){(*position) = (*position) - 1;}
	
	if((*position) - (*taille) < 0){(*position) = (*position) + 1;}
} 

// Objet Baisse taille de 1 (objet -1)
void Baisse_taille(int * taille, int * position, int largeur, int taille_original) // Passer les carractéristique en pointeur pour les modifier
{
	if((*taille) < taille_original){return;} // Non accumulable
	
	(*taille) = (*taille) -1; // Diminue la taille de 1 seulement (ou sinon jeu beaucoup trop dur)
} 


