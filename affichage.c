/* ------- AFFICHAGE.C -------- */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 

#include "material.h"
#include "affichage.h"

#define PMOD(a,b) ( ( (a) + (b) ) % b )

/* --- MENU --- */
// MENUS TEXTES
// Principal
char *main_menu_options[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter"};

// Pause
char *pause_menu_options[4] = {"Continuer", "Sauvegarder", "Réglage", "Quitter"};

// Sauvegarde
char *save_menu_options[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

// MENUS STRUCTURES
struct menu m_main = {
    main_menu_options,
    6,
    0
};

struct menu m_pause = {
    pause_menu_options,
    4,
    0
};

struct menu m_save = {
    save_menu_options,
    3,
    0
};


// Display
void display_menu(struct menu *m){ 
		
	for (int i = 0; i < m->size; i++){
		
		if (i == m->position){
			printf("\033[4m%s\033[24m\n\n", m->options[i]);		
		}
		else{
			printf("%s\n\n", m->options[i]);
		}
	}
}

// Interaction
void update_position(struct menu *m, char key, char up, char down){

	if (key == up){
		m->position = PMOD(m->position - 1, m->size);
	}
	if (key == down){
		m->position ++; 
	}
}


/* --- GAME --- */

void display_game(struct jeu *p){

    // Informations pour les objets
    // on commence par le plus haut sur la
    // map donc le dernier de la file
    int index = (p->first + p->N_objects) % HAUTEUR;
    
    for (int i = -1; i < HAUTEUR+2; i++){

        // Mur gauche
        printf("%s", p->map.border);
        
        for (int j = 0; j < LARGEUR; j++){
        
            if (i == -1 || i == HAUTEUR+1){

                // Plafond et plancher
                printf("%s", p->map.border);
            }

            // Radeau
            if (i == HAUTEUR && (j >= p->position - p->fleet[p->index].size) && (j <= p->position + p->fleet[p->index].size)){
                
                printf("- ");
            } 

            // Objets
            if (p->Is[index] == i && p->Js[index] == j){
                
                printf("%s", p->objects[p->Ks[index]]);

                index = PMOD(index-1, HAUTEUR);

            }

            else{printf(" ");}

        }
    
    }   
}

// Partie Multijouer :
void display_game_multi(struct jeu *p1, struct jeu *p2){
	
    display_game(p1);
	printf("\n Score : %d\n", p1->score);
	printf("\n\n\n");

	display_game(p2);
	printf("\n Score : %d\n", p2->score);
}


