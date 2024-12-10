/* ------- AFFICHAGE.C -------- */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 
#include <string.h>

#include "material.h"
#include "affichage.h"

#define PMOD(a,b) ( ( (a) + (b) ) % b )

#include <stdio.h>

/* --- MENU --- */
// MENUS TEXTES
// Principal
char *main_menu_options[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter"};
char *pause_menu_options[3] = {"Continuer", "Sauvegarder", "Quitter"};
char *save_menu_options[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

static struct menu *m_main = NULL;
static struct menu *m_pause = NULL;
static struct menu *m_save = NULL;

struct menu *create_menu(int size, char **options) {
    struct menu *m = malloc(sizeof(struct menu) + size * sizeof(char *));
    if (m == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    m->size = size;
    m->position = 0;

    for (int i = 0; i < size; i++) {
        m->options[i] = strdup(options[i]); // Copier les chaînes dynamiquement
        if (m->options[i] == NULL) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
    }
    return m;
}

void my_free_menu(struct menu *m){
    if (m != NULL) {
        for (int i = 0; i < m->size; i++) {
            free(m->options[i]); // Libérer chaque chaîne
        }
        free(m); // Libérer la structure
    }
}

void move_menu(struct menu *m, char key, char up, char down){

    if (key == up){m->position = PMOD(m->position-1, m->size);}

    
    if (key == down){m->position = (m->position + 1) % m->size;}
}


// Fonction pour initialiser tous les menus
void initialize_menus() {
    m_main = create_menu(6, main_menu_options);
    m_pause = create_menu(3, pause_menu_options);
    m_save = create_menu(3, save_menu_options);
}

// Fonctions pour accéder aux menus
struct menu *get_main_menu() {
    return m_main;
}

struct menu *get_pause_menu() {
    return m_pause;
}

struct menu *get_save_menu() {
    return m_save;
}

// Display
void display_menu(struct menu *m){ 
		
	for (int i = 0; i < m->size; i++){
		
		if (i == m->position){
			printf("\033[4m%s\033[24m\n\n", m->options[i]);		
		}
		else{
			printf("%s\n\n", m->options[i]);
		}
	}
}

/* --- GAME --- */

void display_game(struct jeu *p){

    // -- OBJETS --
    struct object *objects = get_objects();

    // Informations pour les objets
    // on commence par le plus haut sur la
    // map donc le dernier de la file
    
    //printf("hauteur = %d", HAUTEUR);
    
    int index;

    //if (p->first == -1){index=0;}
    
    index = (p->first + p->N_objects - 1) % HAUTEUR;
    
    //printf("index avant le for = %d", index);
    
    for (int i = -1; i < HAUTEUR+2; i++){

        // Mur gauche
        printf("%s", maps[p->index_map].border);
        for (int j = -1; j < LARGEUR+1; j++){
        
            if (i == -1 || i == HAUTEUR+1){

                // Plafond et plancher
                printf("%s", maps[p->index_map].border);
            }

            // Radeau
            else if (i == HAUTEUR && (j >= p->position - fleet[p->index_fleet][p->index].size) && (j <= p->position + fleet[p->index_fleet][p->index].size)){
                
                printf("-");
            } 

            // Objets
            else if (p->first != -1 && p->Is[index] == i && p->Js[index] == j){
                
                printf("%s", objects[p->Ks[index]].skin);

                index = PMOD(index-1, HAUTEUR);

                //printf("First: %d, N_objects: %d, Initial index: %d\n", p->first, p->N_objects, index);
                //printf("Index : %d\n", index);

            }

            else{printf(" ");}

        }
        printf("%s\n", maps[p->index_map].border);

    }   
}

// Partie Multijouer :
void display_game_multi(struct jeu *p1, struct jeu *p2){
	
    display_game(p1);
	printf("\n Score : %d\n", p1->score);
	printf("\n\n\n");

	display_game(p2);
	printf("\n Score : %d\n", p2->score);
}


