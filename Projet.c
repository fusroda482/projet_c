// Groupe G6 B
// FOUINE Geoffrey
// SEGHIR Wassim 

#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <stdbool.h> 
#include <time.h> 
#include "gestion_clavier.c"
#include "objet.c"
#include "menu.c"



#define LARGEUR 10
#define HAUTEUR 14

#define frame 5e3

struct jeu {
	int position;
	int objets[HAUTEUR][LARGEUR];
	int score;
	int taille;
	//Nouveaux :
	char * pseudo ;
	int argent;
	
};


struct jeu init_jeu() {

	struct jeu p;

	p.position = LARGEUR / 2;
	p.score = 0;
	p.taille = 2;

	for(int i=0; i < HAUTEUR; i++)
		for(int j=0; j < LARGEUR; j++)
			p.objets[i][j] = 0;
			
	p.pseudo = "Inconnu.e";
	p.argent = 0;
	
	return p;
}


void affiche_jeu(struct jeu p) {
	
	//system("clear");	
	
	for(int i=-1; i< HAUTEUR+2; i++) {
	
		printf("* "); // '*' sur à gauche de chaque ligne
		
		for (int j=0; j < LARGEUR; j++){

			if (i == -1 || i == HAUTEUR+1) { 	// '*' sur toutes la ligne du haut
				printf("* ");			// et celle du bas
			}
			
			// Le radeau
			else if (i == HAUTEUR && j >= p.position-p.taille && j <= p.position+p.taille) {
				printf("- ");
			}
			
			// Les objets
			else if (i < HAUTEUR && p.objets[i][j] != 0){
				
				affiche_objets( p.objets[i][j]);
			}
			
			else {
				printf("  ");
			}
			
		} //fin boucle for
		
		printf("*\n"); // '*' à chaque fin de ligne
		
	}// fin boucle for

}


int deplacer(char direction, struct jeu p, char droite , char gauche ){

	if (direction == droite && (p.position - p.taille) > 0){
		p.position--;
	}

	if (direction == gauche && (p.position + p.taille) < LARGEUR - 1){
		p.position++;
	}

	return p.position;
}


void mise_a_jour_objets(int objets[HAUTEUR][LARGEUR]){
	
	
	// 1. Disparition
	for (int j = 0; j < LARGEUR; j++){
		
		objets[HAUTEUR - 1][j] = 0;
	}
	
	// 2. Déplacement
	for (int i = HAUTEUR - 2; i >= 0; i--){
	
		for (int j = 0; j < LARGEUR; j++){
		
			if (objets[i][j] != 0){
				
				int temp = objets[i][j];
				objets[i][j] = 0;
				objets[i+1][j] = temp;
			}
		}
	}
	
	// 3. Apparition
	
	int objet= prob_apparition();
	
	
	objets[0][rand() % LARGEUR] = objet;

}


struct jeu verifier_colision(struct jeu p){
	
	for (int j = 0; j < LARGEUR; j++){
		
		if (j >= p.position-p.taille && j <= p.position+p.taille && p.objets[HAUTEUR - 1][j] != 0){	// Si objet touche radeau 
			
			switch (p.objets[HAUTEUR - 1][j]){
				
				case 1 :
					p.score++;
					break;
					
				case 2 : 
					Augmente_taille(& p.taille, & p.position, LARGEUR, 2);
					break;
				
				case -1 :
					Baisse_taille(& p.taille, & p.position, LARGEUR, 2);
					break;
					
			}//fin switch
			
			
		}
		
		if( (j < p.position-p.taille || j > p.position+p.taille)  && p.objets[HAUTEUR - 1][j] == 1){	// Si objet normale touche pas
			p.score --;
		}
	}

	return p;
}


void sauve_partie(struct jeu p, int i){
	
	FILE * sauvegarde = NULL;
	
	// Creation Fichier Sauvegarde
	
	if(i == 1){sauvegarde = fopen("Sauvegarde1.txt", "w");}
	if(i == 2){sauvegarde = fopen("Sauvegarde2.txt", "w");}
	if(i == 3){sauvegarde = fopen("Sauvegarde3.txt", "w");}
	
	
	
	if(sauvegarde == NULL){		// Erreur dans l'ouverture du programme
		
		printf("Probleme a l'ouverture de sauvegarde. Fin de la sauvegarde\n");
		return;
	}
	
	fprintf(sauvegarde, "%d\n", p.position); // sauvegarder la position
	
	// Sauvegarder les objets 
	for(int i = 0; i < HAUTEUR; i ++){
		for(int j = 0; j < LARGEUR; j++){
			fprintf(sauvegarde, "%d ", p.objets[i][j]);
		}
		
		fprintf(sauvegarde, "\n");
	}
	
	fprintf(sauvegarde, "%d\n", p.taille); // Sauvegarde taille
	fprintf(sauvegarde, "%d\n", p.score); // Sauvegarde score
	
	fprintf(sauvegarde, "%s\n", p.pseudo); //Sauvegarde Pseudo
	fprintf(sauvegarde, "%d\n", p.argent);
	
	fclose(sauvegarde); // Fermermeture du fichier
		 
}


struct jeu charge_partie(int i){
	
	FILE * charge = NULL;
	
	// Lire les sauvegardes
	
	if(i == 1){charge = fopen("Sauvegarde1.txt", "r");}
	if(i == 2){charge = fopen("Sauvegarde2.txt", "r");}
	if(i == 3){charge = fopen("Sauvegarde3.txt", "r");}
	
	
	if(charge == NULL){
		printf("Fichier Inexistant\n");
		struct jeu defaut = init_jeu(); 
		return defaut; // Renvoyer un jeu par defaut
	}
	
	struct jeu p;
	
	// Pour la position 
	fscanf(charge, "%d", &p.position);
	
	// Pour les objets
	for(int i = 0; i < HAUTEUR; i++){
		for(int j = 0; j < LARGEUR; j++){
			fscanf(charge, "%d", &p.objets[i][j]);
		}
	}
	
	// Pour la taille 
	fscanf(charge, "%d", &p.taille);
	
	// Pour le score
	fscanf(charge, "%d", &p.score);
	
	//Pour le pseudo
	fscanf(charge, "%20[^\n]", p.pseudo);
	
	//Pour l'argent
	fscanf(charge, "%d", &p.argent);
	
	
	fclose(charge); // Fermeture du fichier
	
	return p; 
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
	
	config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	       
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p; 
	
	if(charge == 0) { p = init_jeu();} // Initialiser

	else { p = charge_partie(charge);}
	
	system("clear");
	
	affiche_jeu(p);
	
	char touche;
	int frame_total = 0;
	
	
	while(touche != 'q' && p.score > -50){
	
		
		// Si Une touche est tapé deplacer le radeau
		if(read(STDIN_FILENO, &touche, 1) == 1){
			p.position = deplacer(touche, p, 'a', 'd');
		}
		
		usleep(frame); // Delais pour que les objets tembent (en microsecondes)
		
		frame_total += frame;
		
		if(Faire_Tomber(frame*50, &frame_total)){
			
			p = verifier_colision(p);
			mise_a_jour_objets(p.objets);
		}
				
		system("clear");
			 
		affiche_jeu(p);
		
		printf("\n Score : %d\n", p.score); //Afficher le score de la partie
	}
	
	
	printf("\nVoulez vous sauvegarder y/n\n");
				
	while(true){
		
		if(read(STDIN_FILENO, &touche, 1) == 1 &&touche == 'y'){
			restaurer_terminal(); // Restaurer le terminale à son état initial
			
			char * nom_sauvegarde[3] = {(charge_partie(1)).pseudo,
			(charge_partie(2)).pseudo, (charge_partie(3)).pseudo};
					
			int partie = menu(3, nom_sauvegarde);
						
			sauve_partie(p, partie);
			
			break;
			}
			
		else if(touche == 'n'){break;} 
		
	}
	
	restaurer_terminal(); // Restaurer le terminale à son état initial
	
	
	int position = menu(taille_menu_principale, mprincipale);
	menu_principale(position);
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
	
	config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p1 = init_jeu();
	struct jeu p2 = init_jeu();
	
	system("clear");
	
	affiche_jeu_multi(p1, p2);
	
	char touche;
	int frame_total = 0;
	
	
	while(touche != 'q'){
	
		// Si Une touche est tapé deplacer le radeau
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
	
	restaurer_terminal();
	
	int position = menu(taille_menu_principale, mprincipale);
	menu_principale(position);
}

// Partie Menu : 
int menu(int taille, char * m[]){
	
	config_terminal(); // Mode non canonique
	
	char touche;
	int menu_position = 0;
	
	while(touche != '\n'){
	
		affiche_menu(menu_position, taille, m);
		
		if(read(STDIN_FILENO, &touche, 1) == 1){ 
			deplacer_curseur(&menu_position, touche, 'a', 'd', taille);
		}
		
		usleep(frame);
		
		system("clear");
	}
	
	restaurer_terminal();
	
	return menu_position;
}


void menu_principale(int position){
	
	switch(position){
		case 0 : // Pour jouer seul (le jeu classique)
			solo(0);
			break;
		
		case 1 : // Pour jouer à deux
			multi();
			break;
			
		case 2 : // Pour charger une partie solo (pas possible pour le multi)
			char * nom_sauvegarde[3] = {(charge_partie(1)).pseudo,
			(charge_partie(2)).pseudo, (charge_partie(3)).pseudo};
			
			int partie = menu(3, nom_sauvegarde);
			
			solo(partie);
			break; 
							
			
			
			
		
	}//fin switch
		
}


// Programme principal
int main(void) {
	
	menu_principale(menu(taille_menu_principale, mprincipale));
	
	restaurer_terminal();
	
	return 1;
}
