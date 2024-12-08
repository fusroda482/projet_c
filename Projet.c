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


#define LARGEUR 10
#define HAUTEUR 14

#define frame 5e4

void deplacer(char direction, struct jeu *p, char right, char left){

	if (direction == right && (p->position - p->taille) > 0){
		p->position--;
	}

	if (direction == left && (p->position + p->taille) < LARGEUR - 1){
		p->position++;
	}
}

bool Faire_Tomber(int diff, int * frame_tot){ // Faire tomber à chaque "diff" frame

	if(*(frame_tot) == diff){
		* frame_tot = 0; // Renitialiser la variable
		return true;
	}
	
	return false;
}


// Partie Solo : 

void solo(int charge){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	       
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p; 
	
	if(charge == 0) { p = init_jeu();} // Initialiser

	else { p = charge_partie(charge);}
	
	system("clear");
	
	affiche_jeu(p);
	
	char touche;
	int frame_total = 0;
	
	
	while(touche != 'q' && p.score > -50){
	
		
		if(touche == 'p'){
			int option =  menu(taille_menu_pause, mpause);
			touche = menu_pause(option, p);
			
		}
		
		// Si Une touche est tapée deplacer le radeau
		if(read(STDIN_FILENO, &touche, 1) == 1){
			p.position = deplacer(touche, p, 'a', 'd');
		}
		
		usleep(frame); // Delais pour que les objets tombent (en microsecondes)
		
		frame_total += frame;
		
		if(Faire_Tomber(frame*50, &frame_total)){
			
			p = verifier_colision(p);
			mise_a_jour_objets(p.objets);
		}
				
		system("clear");
			 
		affiche_jeu(p);
		
		printf("\n Score : %d\n", p.score); //Afficher le score de la partie
		
		
	}
	
	
	touche = 'r';
	//restaurer_terminal();
}

// Partie Multijouer :

void affiche_jeu_multi(struct jeu p1, struct jeu p2){
	
	affiche_jeu(p1);
	printf("\n Score : %d\n", p1.score);
	printf("\n\n\n");
	affiche_jeu(p2);
	printf("\n Score : %d\n", p2.score);
}

void multi(){
	
	//config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p1 = init_jeu();
	struct jeu p2 = init_jeu();
	
	system("clear");
	
	affiche_jeu_multi(p1, p2);
	
	char touche;
	int frame_total = 0;
	
	
	while(touche != 'q'){
	
		// Si Une touche est tapée déplacer le radeau
		if(read(STDIN_FILENO, &touche, 1) == 1){
			p1.position = deplacer(touche, p1, 'a', 'd');
			p2.position = deplacer(touche, p2, '1', '3');
		}
		
		usleep(frame); // Delais pour que les objets tambent (en microsecondes)
		
		frame_total += frame;
		
		if(Faire_Tomber(frame*50, &frame_total)){
			
			p1 = verifier_colision(p1);
			p2 = verifier_colision(p2);
			
			
			mise_a_jour_objets(p1.objets);
			mise_a_jour_objets(p2.objets);
		}
		
		system("clear");
		affiche_jeu_multi(p1, p2);
		
		
	}
	
	touche = 'r';
	//restaurer_terminal();
}

// Partie Menu : 
int menu(int taille, char * m[]){
	
	 
	char touche;
	int menu_position = 0;
	

	while(touche != '\n'){
	
		affiche_menu(menu_position, taille, m);
		
		if(read(STDIN_FILENO, &touche, 1) == 1){ 
			deplacer_curseur(&menu_position, touche, 'a', 'd', taille);
		}
		
		usleep(frame*10);
		
		system("clear");
	}
	

	touche = 't';
	return menu_position;
}


void menu_principal(int position){
	
	switch(position){
		case 0 : // Pour jouer seul (le jeu classique)
			solo(0);			
			return;
		
		case 1 : // Pour jouer à deux
			multi();
			break;
			
			
		case 2 : // Pour charger une partie solo (pas possible pour le multi)
		
			int  charge = menu(taille_s, s);
			solo(charge + 1);
			break;
			
		case 5 : 
			break;
												
	}//fin switch
		
}

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

// Programme principal
int main(void){

	config_terminal(); // Mode non canonique
	

	int position = menu(taille_menu_principal, mprincipal);
	
	while(position != 5){
		
		menu_principal(position);
		position = menu(taille_menu_principal, mprincipal);
		
	}
	
	restaurer_terminal();
	
	return 1;
}
		
