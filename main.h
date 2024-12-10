/* ----- MAIN.H ------ */

#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>// ??

bool drop(int delta_t, int *frame_tot);
void menu_principal_switch(struct menu *m);
char menu_pause_switch(struct menu *m, struct jeu *p);
void interactive_menu(struct menu *m);
int main();
#endif
