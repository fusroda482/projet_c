/* ------ AFFICHAGE.H -------- */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

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

void display_game(struct jeu *p);
void display_game_multi(struct jeu *p1, struct jeu *p2);
#endif
