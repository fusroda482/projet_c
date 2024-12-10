/* ------- AFFICHAGE.C -------- */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 

#include "menu.c"


/* --- MENU --- */

// Display
void display_menu(struct menu *m){ 
		
	for (int i = 0; i < m->size; i++){
		
		if (i == m->position){
			printf("\033[4m%s\033[24m\n\n", menu[i]);		
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
    int index = p->first;

    
    for (int i = -1; i < HAUTEUR+2; i++){

        // Mur gauche
        print("%s", p->theme.border);
        
        for (int j = 0; j < LARGEUR; j++){
        
            if (i == -1 || i == HAUTEUR+1){

                // Plafond et plancher
                printf("%s", p->theme.border);
            }

            // Radeau
            if (i == HAUTEUR && (j >= p->position - p->size) && (j <= p->position + p->size)){
                
                printf("- ");
            } 

            // Objets
            if (p->Is[index] == i && p->Js[index] == j){
                
                printf("%s", p->theme.objets[p->Ks[index]]);

            }

            else{print(" ");}

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


