/* ------ MENU.H --------- */

#ifndef MENU_H
#define MENU_H

// LES MENUS, LEURS CHAMPS, LEURS TAILLES

struct menu{
    char *options[];
    int size;
}

// Principal
struct menu principal;
struct menu pause;
struct menu save;
struct menu skin;
struct menu settings;

// Principal - champs 
char *main_menu_options[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter" };

// Principal - taille
const int main_menu_size = 6;

// Pause - champs
char *pause_menu_options[4] = {"Continuer", "Sauvegarder", "Réglage", "Quitter"};

// Pause - taille
const int pause_menu_size = 4;

// Sauvegarde - champs
char *s[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

// Sauvegarde - taille
const int taille_sauvegardes = 3; 


// --- PROTOTYPES DES FONCTIONS ---

// -- Affiche Menu --
void display_menu(int menu_position, int size, char *menu[]);

// -- Déplacer Curseur --
void move_menu(int *menu_position, char touche, char up, char down, int taille);

#endif
