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



#define LARGEUR 10
#define HAUTEUR 14

#define frame 5e3

struct jeu {
	int position;
	int objets[HAUTEUR][LARGEUR];
	int score;
	int taille;
};


struct jeu init_jeu() {

	struct jeu p;

	p.position = LARGEUR / 2;
	p.score = 0;
	p.taille = 2;

	for(int i=0; i < HAUTEUR; i++)
		for(int j=0; j < LARGEUR; j++)
			p.objets[i][j] = 0;
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


int deplacer(char direction, struct jeu p, char droite, char gauche){

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


void sauve_partie(struct jeu p){
	
	FILE * sauvegarde = NULL;
	sauvegarde = fopen("Sauvegarde.txt", "w"); // Creation (ou remplacement) Fichier Sauvegarde
	
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
	
	fclose(sauvegarde); // Fermermeture du fichier
		 
}


struct jeu charge_partie(void){
	
	FILE * charge = NULL;
	charge = fopen("Sauvegarde.txt", "r"); // Lire la sauvegarde
	
	if(charge == NULL){
		printf("Erreur de le lecture de la sauvegarde\n");
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
	
	fclose(charge); // Fermeture du fichier
	
	return p; 
}


bool Faire_Tomber(int diff, int * frame_tot){ // Faire tomber à chaque "diff" frame

	if(*(frame_tot) == diff){
		* frame_tot = 0; // renitialiser la variable
		return true;
	}
	
	return false;
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
		
		usleep(frame); // Delais pour que les objets tembent (en microsecondes)
		
		frame_total += frame;
		
		if(Faire_Tomber(frame*100, &frame_total)){
			
			p1 = verifier_colision(p1);
			p2 = verifier_colision(p2);
			
			
			mise_a_jour_objets(p1.objets);
			mise_a_jour_objets(p2.objets);
		}
		
		system("clear");
		affiche_jeu_multi(p1, p2);
		
		
	}
	
	restaurer_terminal(); // Restaurer le terminal a son état normal
}

// Programme principal
int main(void) {

	multi();
	
	/*
	config_terminal(); // Rend le terminal non canonique et n'affiche pas les char saisie
	
	srand(time(NULL)); // Pour l'aléatoire
	
	struct jeu p = init_jeu(); // Initialiser
	affiche_jeu(p);
	
	
	char touche;
	int frame_total = 0;
	
	
	while(touche != 'q' /&& p.score > -50){
	
		// Si Une touche est tapé deplacer le radeau
		if(read(STDIN_FILENO, &touche, 1) == 1){
			p.position = deplacer(touche, p);
		}
		
		usleep(frame); // Delais pour que les objets tembent (en microsecondes)
		
		frame_total += frame;
		
		if(Faire_Tomber(frame*50, &frame_total)){
			
			p = verifier_colision(p);
			mise_a_jour_objets(p.objets);
		}
					 
		affiche_jeu(p);
		
		printf("\n Score : %d\n", p.score); //Afficher le score de la partie
	}
	
	sauve_partie(p); // Sauvegarder la partie
	
	restaurer_terminal(); // Restaurer le terminal a son état normal
	
	printf("\n Score Final %d\n", p.score); // Afficher score  
	
	*/
	
	return 1;
}
