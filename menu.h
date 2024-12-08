/* ------ MENU.H --------- */

#ifndef MENU_H
#define MENU_H

// LES MENUS, LEURS CHAMPS, LEURS TAILLES

// Principal - champs 
char *mprincipal[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter" };

// Principal - taille
const int taille_menu_principal = 6;

// Pause - champs
char *mpause[4]= {"Continuer", "Sauvegarder", "Réglage", "Quitter"};

// Pause - taille
const int taille_menu_pause = 4;

// Sauvegarde - champs
char *s[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

// Sauvegarde - taille
const int taille_sauvegardes = 3; 


// --- PROTOTYPES DES FONCTIONS ---

// -- Affiche Menu --
void affiche_menu(int menu_position, int taille, char *menu[]);

// -- Déplacer Curseur --
void deplacer_curseur(int *menu_position, char touche, char up, char down, int taille);

#endif
