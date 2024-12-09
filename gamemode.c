/* -------- GAMEMODE.C -------- */

#include "gamemode.h"


// Partie Solo : 

void solo(int slot_number){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	       
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p; 
	
	if (slot_number == 0){p = init_jeu();} // Initialiser

	else {p = load(slot_number);}
	
	system("clear");
	
	display_game(p);
	
	char key;

	int frame_total = 0;
	
	while(key != 'q' && p.score > -50){
	
		// Pause
		if(key == 'p'){
			int option =  menu(taille_menu_pause, mpause);
			touche = m_pause->action(option, p);
			
		}
		
		// Si Une touche est tapée deplacer le radeau
		if (read(STDIN_FILENO, &key, 1) == 1){
			p.position = move_raft(key, &p, 'a', 'd');
		}
		
		usleep(frame); // Delais pour que les objets tombent (en microsecondes)
		
		frame_total += frame;
		
		if(drop(frame*50, &frame_total)){
			
			update_objects(&p);
		}
				
		system("clear");
			 
		display_game(&p);
		
		printf("\n Score : %d\n", p.score); //Afficher le score de la partie
		
	}
	
	touche = 'r';// Pourquoi ?
	//restaurer_terminal();
}

void multi(){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p1 = init_jeu();
	struct jeu p2 = init_jeu();
	
	system("clear");
	
	char key;
	int frame_total = 0;
	
	while(key != 'q'){

		display_game_multi(&p1, &p2);
        
		// Si Une touche est tapée déplacer le radeau
		if(read(STDIN_FILENO, &touche, 1) == 1){
			move_raft(&p1, key, 'a', 'd');
			move_raft(&p2, key, '1', '3');
		}
		
		usleep(frame); // Delais pour que les objets tombent (en microsecondes)
		
		frame_total += frame;
		
		if(drop(frame*50, &frame_total)){
			
			update_objects(&p1);
			update_objects(&p2);
		}
		system("clear");
	}
	
	touche = 'r'; // Pourquoi ??
	//restaurer_terminal();
}
