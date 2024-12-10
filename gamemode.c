/* -------- GAMEMODE.C -------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "gestion_clavier.h"

#include "material.h"
#include "game.h"
#include "affichage.h"
#include "save.h"
#include "main.h"

#include "gamemode.h"

// Partie Solo : 

void solo(int slot_number){
	       
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p; 
	
	if (slot_number == 0){init_jeu(&p);} // Initialiser
	else {p = load(slot_number);}
	
	//system("clear");
	
	//display_game(&p);
	
	char key;

	int frame_total = 0;
    int frame = 1e3;
	
	while(key != 'q' && p.score > -50){
	
		// Pause
		if(key == 'p'){

            struct menu *m_pause = get_pause_menu();
            interactive_menu(m_pause);

            if (m_pause->position == 2){
                break;
            }
		}
		
		// Si Une touche est tapée deplacer le radeau
		if (read(STDIN_FILENO, &key, 1) == 1){
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
		
	}
	
	//key = 'r';// Pourquoi ?
	//restaurer_terminal();
}

void multi(){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
    struct jeu p1;
    struct jeu p2;

	init_jeu(&p1);
	init_jeu(&p2);
	
	system("clear");
	
	char key;
	int frame_total = 0;
    int frame = 1e3;
	
	while(key != 'q'){

		display_game_multi(&p1, &p2);
        
		// Si Une touche est tapée déplacer le radeau
		if(read(STDIN_FILENO, &key, 1) == 1){
			move_raft(&p1, key, 'a', 'd');
			move_raft(&p2, key, '1', '3');
		}
		
		usleep(frame); // Delais pour que les objets tombent (en microsecondes)
		
		frame_total += frame;

	    int delta_t = 50;	
		
        if (frame_total == delta_t){
			frame_total = 0;
			update_objects(&p1);
			update_objects(&p2);
		}
	
		system("clear");
	}
	
	//key = 'r'; // Pourquoi ??
	//restaurer_terminal();
}
