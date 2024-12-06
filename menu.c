#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "gestion_clavier.c"

// MENU

void affiche_menu(char *menu[]){
	
	for (int i=0; i<6; i++){
		printf("test : %s", menu[i]);
	}
}

int main(){

	char *menu[] = {"1.Jouer\n",
		"2.Charger\n",
		"3.Skin\n",
		"4.Map\n",
		"5.Réglages\n",
		"6.Quitter\n"};


	//config_terminal(); // non canonique
	
	//char touche;

	//while (touche != '\r'){
		
		// Affichage du MENU
		//
	affiche_menu(menu);
	int reponse;
	scanf("%d", &reponse);
	printf("%d\n", reponse);

	if (reponse == 1){
		// C'est parti !

	}

	if (reponse == 2){
		// Charger

	}

	if (reponse == 3){
		// Skin
	
	}

	if (reponse == 4){
		// Map

	}

	if (reponse == 5){
		// Réglage

	}

	if (reponse == 6){
		// Quitter
	}







	//}


	//printf("\033[4mCe texte est souligné.\033[0m");
	//printf("%s", "\U0001f4b2");
       	return(0);

}
