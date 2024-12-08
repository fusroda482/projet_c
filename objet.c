//Fichier objets speciaux

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

#include "objet.h"


// La méthode pour initialiser la structure
// avec des paramètres par défaut
void initialiser_jeu(struct jeu *p) {

	p->position = LARGEUR / 2;
	p->score = 0;
	p->taille = 2;

    p->theme = emoji;

	strcpy(p->pseudo, "Inconnu.e\n");// ??
	p->argent = 0;
}


// Determiner l'objet qui va apparaitre en fonction de sa propabilité
int prob_apparition(void){

	int apparition = rand() % 30;
	
	// Propabilité de chaque objet : 
	
	if(apparition > 0 && apparition <= 10){return 1;}
	
	if(apparition == 11){return -1;}
	
	if(apparition == 12){return 2;}
	
	return 0;
}

// Objet Augmente taille de 1 (objet2)
void Augmente_taille(int * taille, int * position, int largeur, int taille_original) // Passer les caractéristiques en pointeur pour les modifier
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


