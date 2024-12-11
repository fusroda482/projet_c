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

//#include "menu.h"
#include "game.h"
#include "material.h"
#include "gamemode.h"
#include "affichage.h"
#include "save.h"
#include "gestion_clavier.h"

#include "main.h"

//#define LARGEUR 10
//#define HAUTEUR 14

#define FRAME 5000

char get_key(){
    char key = '\0';
    read(STDIN_FILENO, &key, 1);
    return key;
}


// Partie Menu : 
void interactive_menu(struct menu *m){
	 
	char key = '\0';
	
	while(key != '\n'){

	    display_menu(m);

        key = get_key();
		
        if(key == 'a' || key == 'd'){
            move_menu(m, key, 'a', 'd');
        }

		//if(read(STDIN_FILENO, &key, 1) == 1){ 
		//	move_menu(m, key, 'a', 'd');
		//}
		
		usleep(FRAME*10);
		
		system("clear");
	}
}

// -- MAIN MENU SWITCH --
void menu_principal_switch(struct menu *m){

    struct menu *m_save = get_save_menu();

    if (m->position < 0 || m->position > 6){
        printf("Erreur : position de menu invalide\n");
    }

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

            //printf("On atteint le int slot_number = %d\n", slot_number); 
            //sleep(3);
			solo(slot_number + 1);// car savegarde 1, 2 ou 3
            //my_free_menu(m_save);
			break;

        //case 3 : // Skin
            

			
		case 5 : // Quitter
			break;
												
	}
}

// -- MENU PAUSE SWITCH --
char menu_pause_switch(struct menu *m, struct jeu *p){
	
	
    if (m->position < 0 || m->position > 2){
        printf("Erreur : position de menu invalide\n");
    }

    switch(m->position){

		case 0 : // Continuer
            break;

		case 1 : {// Sauvegarde

            struct menu *m_save = get_save_menu();
            interactive_menu(m_save);
            int slot_number = m_save->position + 1;
			save(*p, slot_number);
            //my_free_menu(m_save);
        }
            break;

			
		case 2 : // Retour menu principal
            printf("menu pause case 2 : q");
			return 'q';
	}
    return '\0';
}
// Partie Solo : 

void solo(int slot_number){
	       
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p; 
	
    printf("c'est probablement dans load que ça se passe !");
    sleep(3);


	if (slot_number == 0){init_jeu(&p);} // Initialiser
	else {p = load(slot_number);}
	
	//system("clear");
	
	//display_game(&p);
	
	char key = '\0';

	int frame_total = 0;
    int frame = 1e3;
    while(key != 'q' && p.score > -50){

        // Si Une touche est tapée deplacer le radeau
        
        key = get_key();

        if (key == 'a' || key == 'd'){
            move_raft(&p, key, 'a', 'd');
            usleep(frame);
         }

        usleep(frame*10); // Delais pour que les objets tombent (en microsecondes)


        int delta_t = frame*50;
        frame_total += frame;

        if (frame_total == delta_t){
            frame_total = 0;
            update_objects(&p);
        }

        system("clear");

        display_game(&p);

        printf("\n Score : %d\n", p.score); //Afficher le score de la partie
        // Pause
        if(key == 'p'){

            struct menu *m_pause = get_pause_menu();
            interactive_menu(m_pause);

            key = menu_pause_switch(m_pause, &p);

        }

    }

    //key = '\0';        
}

void multi(){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
    struct jeu p1;
    struct jeu p2;

	init_jeu(&p1);
	init_jeu(&p2);
	
	//system("clear");
	
	char key = '\0';

	int frame_total = 0;
    int frame = 1e3;
	
	while(key != 'q'){
        

        
		// Si Une touche est tapée déplacer le radeau

        key = get_key();
        
        if (key == 'a' || key == 'd' || key == '1' || key == '3'){
			move_raft(&p1, key, 'a', 'd');
			move_raft(&p2, key, '1', '3');

        }

		usleep(frame*10); // Delais pour que les objets tombent (en microsecondes)
		
		frame_total += frame;

	    int delta_t = frame * 50;	
		
        if (frame_total == delta_t){
			frame_total = 0;
			update_objects(&p1);
			update_objects(&p2);
		}
	
		system("clear");

		display_game_multi(&p1, &p2);
        // Pause
		if(key == 'p'){

            struct menu *m_pause = get_pause_menu();
            interactive_menu(m_pause);

            key = menu_pause_switch(m_pause, &p1);
		}
	}
}

// Programme principal
int main(){

    // initialisation des menus
    // -- MENUS --
    initialize_menus();

    struct menu *m_main = get_main_menu();

	config_terminal(); // Mode non canonique
	
	while(m_main->position != 5){
        
        interactive_menu(m_main);
        menu_principal_switch(m_main);

	}

    my_free_menu(m_main);
    //free_menu(m_pause);
    //free_menu(m_save);

	restaurer_terminal();
	
	return 1;
}
		
