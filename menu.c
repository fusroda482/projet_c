/ Groupe G6 B
// FOUINE Geoffrey
// SEGHIR Wassim 

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 
#include <string.h>

#include "menu.h"
// MENUS TEXTES
// Principal
char *main_menu_options[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter"};

// Pause
char *pause_menu_options[4] = {"Continuer", "Sauvegarder", "Réglage", "Quitter"};

// Sauvegarde
char *save_menu_options[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

// MENUS STRUCTURES
struct menu m_main = {
    main_menu_options,
    6,
    0
};

struct menu m_pause = {
    pause_menu_options;
    4,
    0
};

struct menu m_save = {
    save_menu_options,
    3,
    0
};

// MENUS ACTIONS

