/* ------ MENU.H --------- */

#ifndef MENU_H
#define MENU_H

// --- STRUCTURE MENU ---
struct menu{
    char *options[];// ! erreur potentielle !
    int size;
    int position;
}

// --- PROTOTYPES DES FONCTIONS ---

// -- Affiche Menu --
void display_menu(int menu_position, int size, char *menu[]);

// -- Déplacer Curseur --
void move_menu(int *menu_position, char touche, char up, char down, int taille);

#endif
