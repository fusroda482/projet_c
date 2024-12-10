/* ------ AFFICHAGE.H -------- */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

// --- STRUCTURE MENU ---
struct menu{
    int size;
    int position;
    char *options[];// Flexible Array Member
};

// --- PROTOTYPES DES FONCTIONS ---

// -- Create Menu --
struct menu *create_menu(int size, char **options);
void my_free_menu(struct menu *m);

void initialize_menus();
struct menu *get_main_menu();
struct menu *get_pause_menu();
struct menu *get_save_menu();

// -- Affiche Menu --
void display_menu(struct menu *m);

// -- Déplacer Curseur --
void move_menu(struct menu *m, char key, char up, char down);

void display_game(struct jeu *p);
void display_game_multi(struct jeu *p1, struct jeu *p2);
#endif
