/* ---- GAME.C ---- */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

#include "material.h"
#include "game.h"


//#define HAUTEUR 10
//#define LARGEUR 14

// La méthode pour initialiser la structure
// avec des paramètres par défaut

void init_jeu(struct jeu *p) {

	// Radeau et flotte
    p->position = LARGEUR / 2;
    p->fleet = default_fleet;
    p->index = 1;

    // Joueur
	p->score = 0;
	strcpy(p->pseudo, "Inconnu.e\n");// ??
    p->money = 0;

    // Map
    p->map = default_map;
    
    // Objets
    p->objects = default_objects;

    p->first = 0;
    p->N_objects = 0;
}


// Determiner l'objet qui va apparaitre en fonction de sa propabilité
int lottery(){

	int apparition = rand() % 30;
	
	// Propabilité de chaque objet : 
	
	if(apparition > 0 && apparition <= 10){return 1;}
	
	if(apparition == 11){return 2;}
	
	if(apparition == 12){return 3;}
	
	return 0;
}

// Objet Augmente taille de 1 (objet2)

// Update objets
void update_objects(struct jeu *p){
    
    for (int i = p->first; i < p->N_objects; i++){
        

        p->Is[i % HAUTEUR]++;

        if (p->Is[i % HAUTEUR] == HAUTEUR){
            
            // Collision radeau

            bool collision_left = p->Js[i%HAUTEUR] >= (p->position-p->fleet[p->index].size); 

            bool collision_right = p->Js[i%HAUTEUR] <= (p->position+p->fleet[p->index].size); 

            if (collision_left && collision_right){
                
                // Action d'objet
                p->objects[p->Ks[i + HAUTEUR]](p);

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

            p->first = (p->first + 1) % HAUTEUR;
            p->N_objects--;

        }

    }

    // Enfin, on tire aléatoirement un nouvel objet

    int lot = lottery();

    if (lot > 0){
        // C'est gagné !
        p->Is[(p->first + p->N_objects) % HAUTEUR] = 0;
        p->Js[(p->first + p->N_objects) % HAUTEUR] = rand() % LARGEUR;
        p->Ks[(p->first + p->N_objects) % HAUTEUR] = lot;
    }
    
}
