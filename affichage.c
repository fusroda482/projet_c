#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 

#include "menu.h"

/* MENU */

// Display
void affiche_menu(int position, int taille, char * menu[]){
		
	for (int i = 0; i < taille; i++){
		
		if (i == position){
			printf("\033[4m%s\033[24m\n\n", menu[i]);		
		}
		else{
			printf("%s\n\n", menu[i]);
		}
	}
}

// Interaction
void move_menu(int *menu_position, char key, char up, char down, int menu_size){

	if (key == up){
		*menu_position = (*menu_position) - 1;
	}
	if (key == down){
		*menu_position = (*menu_position) + 1;
	}
	*menu_position = ((*menu_position)+ menu_size) % menu_size;
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
            if (i == HAUTEUR && (j >= p->position - p->size && (j <= p->position + p->size)){
                
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

void 
