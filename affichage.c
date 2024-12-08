#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 

char * mprincipale[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter" };
const int taille_menu_principale = 6;

char * mpause [4]= {"Continuer", "Sauvegarder", "Réglage", "Quitter"};
const int taille_menu_pause = 4;


char* s [3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};
const int taille_s = 3; 

		
	


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


void deplacer_curseur(int *menu_position, char touche, char up, char down, int taille){

	if (touche == up){
		*menu_position = (*menu_position) - 1;
	}
	if (touche == down){
		*menu_position = (*menu_position) + 1;
	}
	*menu_position = ((*menu_position)+ taille) % taille;
}
