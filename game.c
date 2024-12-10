/* ---- GAME.C ---- */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <unistd.h>

#include "material.h"
#include "game.h"


//#define HAUTEUR 10
//#define LARGEUR 14

// La méthode pour initialiser la structure
// avec des paramètres par défaut

void init_jeu(struct jeu *p) {

	// Radeau et flotte
    p->position = LARGEUR / 2;
    p->index = 1;
    p->index_fleet = 0;
    p->index_map = 0;

    // Joueur
	p->score = 0;
	strcpy(p->pseudo, "Inconnu.e\n");// ??
    p->money = 0;
    
    // Objets
    p->first = -1;
    p->N_objects = 0;
}


// Determiner l'objet qui va apparaitre en fonction de sa propabilité
int lottery(){

	int apparition = rand() % 30;
	
	// Propabilité de chaque objet : 
	
	if(apparition > 0 && apparition <= 10){return 0;}
	
	if(apparition == 11){return 1;}
	
	if(apparition == 12){return 2;}
	
	return -1;
}

// Objet Augmente taille de 1 (objet2)

// Update objets
void update_objects(struct jeu *p){

    //sleep(2);
    //printf("on va dans l'update!");
    // -- OBJETS --
    struct object *objects = get_objects();

    int i;

    for (int k = 0; k < p->N_objects; k++){
        
        i = (p->first+k) % HAUTEUR;
        //sleep(5);
        //printf("le petit i d'update objects : %d",i);

        p->Is[i]++;

        if (p->Is[i] == HAUTEUR){
            
            // Collision radeau

            bool collision_left = p->Js[i] >= (p->position-fleet[p->index_fleet][p->index].size); 

            bool collision_right = p->Js[i] <= (p->position+fleet[p->index_fleet][p->index].size); 

            if (collision_left && collision_right){
                
                // Action d'objet
                objects[p->Ks[i]].action(p);

            }
            else{
                // Loupé : -1 point si ce n'est pas un bonus
                if (p->Ks[i] == 1){

                    p->score--;
                }
            }

            // On supprime l'objet
            p->Is[i] = 0;
            p->Js[i] = 0;
            p->Ks[i] = 0;

            p->first = (p->first + 1) % HAUTEUR;
            p->N_objects--;
        }
    }

    // Enfin, on tire aléatoirement un nouvel objet

    int lot = lottery();

    if (lot >= 0){
        //printf("le fameux lot : %d", lot);
        //sleep(5);

        // C'est gagné !
        

        int new_index;
        if (p->first == -1){
            new_index = 0;
            p->first++;
        }
        else {new_index = (p->first + p->N_objects) % HAUTEUR;}

        p->N_objects++;
        p->Is[new_index] = 0;
        p->Js[new_index] = rand() % LARGEUR;
        p->Ks[new_index] = lot;
    }
    
}
