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
void display_menu(struct menu *m);

// -- Déplacer Curseur --
void move_menu(struct menu *m, char touche, char up, char down);

#endif
