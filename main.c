/* ------ MAIN.C ------ */
// Groupe G6 B
// FOUINE Geoffrey
// SEGHIR Wassim 

#include <stdio.h>
#include <stdlib.h> 
//#include <math.h> 
#include <stdbool.h> 
#include <time.h> 
#include <unistd.h>
//#include <string.h>

/*
#include "gestion_clavier.c"
#include "objet.c"
#include "menu.c"
#include "skin.c"
#include "material.c"
#include "gamemode.c"
*/

#include "menu.h"
#include "material.h"
#include "gamemode.h"
#include "affichage.h"
#include "save.h"
#include "gestion_clavier.h"// à remplacer par config_terminal.h

#include "main.h"

//#define LARGEUR 10
//#define HAUTEUR 14

#define frame 5e4

// -- DROP OBJECTS --
bool drop(int delta_t, int *frame_tot){

	if (*(frame_tot) == delta_t){
	    *frame_tot = 0; // Réinitialiser la variable
	    return true;
	}
	return false;
}


// -- MAIN MENU SWITCH --
void menu_principal_switch(struct menu *m){
	

    struct menu *m_save = get_save_menu();
	
    switch(m->position){

		case 0 : // Pour jouer seul (le jeu classique)
			solo(0);			
			break;
		
		case 1 : // Pour jouer à deux
			multi();
			break;
			
		case 2 : // Pour charger une partie solo (pas possible pour le multi)
            interactive_menu(m_save);
            int slot_number = m_save->position;
			solo(slot_number + 1);// car savegarde 1, 2 ou 3
			break;

        //case 3 : // Skin
            

			
		case 5 : 
			break;
												
	}//fin switch
}

// -- MENU PAUSE SWITCH --
char menu_pause_switch(struct menu *m, struct jeu *p){
	
    struct menu *m_save = get_save_menu();
	
    switch(m->position){

		case 0 : // Continuer
			return 'c';

		case 1 : // Sauvegarde
            interactive_menu(m_save);
            int slot_number = m_save->position + 1;
			save(*p, slot_number);
			return 'c';
			
		case 2 : // Retour menu principal
			return 'q';
	}
    return 'q';
}

// Partie Menu : 
void interactive_menu(struct menu *m){
	 
	char key;
	
	while(key != '\n'){
	
	    display_menu(m);
		
		if(read(STDIN_FILENO, &key, 1) == 1){ 
			move_menu(m, key, 'a', 'd');
		}
		
		usleep(frame*10);
		
		system("clear");
	}
    
    //m->actions[m->position];
    
	//key = 't';// WHY ??
}

// Programme principal
int main(){

    // initialisation des menus
    // -- MENUS --
    initialize_menus();

    struct menu *m_main = get_main_menu();
    //struct menu *m_pause = get_pause_menu();

	config_terminal(); // Mode non canonique
    
    display_menu(m_main);
	
	while(m_main->position != 5){
        
        interactive_menu(m_main);
		
	}

    my_free_menu(m_main);
    //free_menu(m_pause);
    //free_menu(m_save);

	restaurer_terminal();
	
	return 1;
}
		
