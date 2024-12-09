// Groupe G6 B
// FOUINE Geoffrey
// SEGHIR Wassim 

#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <stdbool.h> 
#include <time.h> 
#include <string.h>
#include "gestion_clavier.c"
#include "objet.c"
#include "menu.c"
#include "skin.c"
#include "material.c"


#define LARGEUR 10
#define HAUTEUR 14

#define frame 5e4

// -- DROP OBJECTS --
bool drop(int delta_t, int * frame_tot){

	if (*(frame_tot) == delta_t){
	    *frame_tot = 0; // Renitialiser la variable
	    return true;
	}
	return false;
}

// -- MAIN MENU --
void menu_principal(struct menu *m){
	
	switch(m->position){

		case 0 : // Pour jouer seul (le jeu classique)
			solo(0);			
			return;
		
		case 1 : // Pour jouer à deux
			multi();
			break;
			
		case 2 : // Pour charger une partie solo (pas possible pour le multi)
		
			int slot_number = menu(taille_s, s);
			solo(slot_number + 1);// car savegarde1 2 ou 3
			break;
			
		case 5 : 
			break;
												
	}//fin switch
}

// -- PAUSE --
char menu_pause(int position, struct jeu p){
	
	switch(position){
		case 0 :
			return 'c';

		case 1 :
			int sauvegarde = menu(taille_s, s);
			sauve_partie(p, sauvegarde + 1);
			return 'c';
			
		case 2 :
			return 'c';
			
		case 3 : 
			return 'q';
			
	}//fin switch
}

// Partie Menu : 
void menu(struct menu *m){
	 
	char key;
	
	while(key != '\n'){
	
	    display_menu(m);
		
		if(read(STDIN_FILENO, &touche, 1) == 1){ 
			move_menu(m, key, 'a', 'd');
		}
		
		usleep(frame*10);
		
		system("clear");
	}

	//key = 't';// WHY ??
}

// Programme principal
int main(void){

	config_terminal(); // Mode non canonique
    
    display_menu(&m_main);
	
	while(m_main.position != 5){
        
        menu(&m_main);
		
	}
	
	restaurer_terminal();
	
	return 1;
}
		
