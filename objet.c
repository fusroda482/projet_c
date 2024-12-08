//Fichier objets speciaux

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

#include "objet.h"

#define PMOD(a,b) ( ( (a) + (b) ) % b )


// La méthode pour initialiser la structure
// avec des paramètres par défaut
void initialiser_jeu(struct jeu *p) {

	// Radeau et flotte
    p->position = LARGEUR / 2;
    p->feet = {default};
    p->raft = 1;

    // Joueur
	p->score = 0;
	strcpy(p->pseudo, "Inconnu.e\n");// ??
    p->money = 0;

    p->theme = emoji;

    // Map
    p->map = default map;
    
    // Objets
    p->objets = default objets

	p->argent = 0;
}


// Determiner l'objet qui va apparaitre en fonction de sa propabilité
int lottery(void){

	int apparition = rand() % 30;
	
	// Propabilité de chaque objet : 
	
	if(apparition > 0 && apparition <= 10){return 1;}
	
	if(apparition == 11){return 2;}
	
	if(apparition == 12){return 3;}
	
	return 0;
}

// Objet Augmente taille de 1 (objet2)
//void bigger(int * size, int * position, int largeur, int taille_original){

void bigger(struct jeu *p){

    p->raft = (p->raft + 1) % 3; // 3 tailles disponibles

    // Gestion collision en cas d'agrandissement
    // 1. se cogne contre le mur de droite
	if (p->position + p->fleet[p->raft].size > largeur){p->position--;}
    // 2. se cogne contre le mur de gauche	
	if (p->position - p->fleet[p->raft].size < 0){p->position++;}; 


// Objet Baisse taille de 1 (objet -1)
void smaller(struct jeu *p){

    p->raft = PMOD(p->raft - 1, 3);	
} 

// Update objets
void update_objets(struct jeu *p){
    
    for (int i = p->first; i < p->N_objects; i++){
        
        p->Is[i % HAUTEUR]++;

        if (p->Is[i % HAUTEUR] == HAUTEUR){
            
            // Collision radeau
            bool collision = (p->Js[i % HAUTEUR] >= (p->position-p->size) && p->Js[i % HAUTEUR] <= (p->position+p->size));
            bool collision_right (p->Js[i % ])
            if (collision){
                
                // Actions d'objet
                p->objets[p->Ks[i + HAUTEUR]];

            }
            else{
                // Loupé : -1 point si ce n'est pas un bonus
                if (p->Ks[i % HAUTEUR] == 1){

                    p->score--;
                }
            }

            // On supprime l'objet
            p->Is[i % HAUTEUR] = 0;
            p->Js[i % HAUTEUR] = 0;
            p->Ks[i % HAUTEUR] = 0;

            p->first = (first + 1) % HAUTEUR;
            p->N_objets--;

        }

    }

    // Enfin, on tire aléatoirement un nouvel objet

    int lot = lottery();

    if (lot > 0){
        // C'est gagné !
        ps->Is[(ps->first + ps->length) % HAUTEUR] = 0;
        ps->Js[(ps->first + ps->length) % HAUTEUR] = rand() % LARGEUR;
        ps->Js[(ps->first + ps->length) % HAUTEUR] = lot;
    }
    

}


