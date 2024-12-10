/*#include <stdio.h>

// Définition de la structure test
struct test {
    int valeur;
    char caractere;
};

// Définition de la structure object
struct object {
    void (*action)(struct test);
};

// Fonction pour afficher les propriétés de l'instance
void fonction(struct test instance) {
    printf("dans la fonction\n");
    printf("Valeur : %d, Caractere : %c\n", instance.valeur, instance.caractere);
}

int main() {
    // Création d'une instance de test
    struct test instance = {0, 'a'};

    // Création d'un objet avec la fonction
    struct object coucou = {fonction};

    // Appel de la fonction via l'objet
    coucou.action(instance);


    int tableau[2] = {1,2};
    int somme(){
        int resultat = tableau[0] + tableau[1];
        return resultat;
    }

    int result = somme();
    printf("résultat : %d\n", result);
    return 0;
}
*/
#include <stdlib.h>
#include <string.h>

// MENUS TEXTES
char *main_menu_options[6] = {"Solo", "Multijoueur", "Charger", "Skin", "Réglages", "Quitter"};
char *pause_menu_options[4] = {"Continuer", "Sauvegarder", "Réglage", "Quitter"};
char *save_menu_options[3] = {"Sauvegarde 1", "Sauvegarde 2", "Sauvegarde 3"};

// MENUS STRUCTURES
struct menu {
    int size;
    int position;
    char *options[]; // Flexible Array Member
};

int main() {
    // Allocate memory for the main menu
    struct menu *m_main = malloc(sizeof(struct menu) + 6 * sizeof(char *));
    m_main->size = 6;
    m_main->position = 0;
    memcpy(m_main->options, main_menu_options, 6 * sizeof(char *));

    // Allocate memory for the pause menu
    struct menu *m_pause = malloc(sizeof(struct menu) + 4 * sizeof(char *));
    m_pause->size = 4;
    m_pause->position = 0;
    memcpy(m_pause->options, pause_menu_options, 4 * sizeof(char *));

    // Allocate memory for the save menu
    struct menu *m_save = malloc(sizeof(struct menu) + 3 * sizeof(char *));
    m_save->size = 3;
    m_save->position = 0;
    memcpy(m_save->options, save_menu_options, 3 * sizeof(char *));

    // Free allocated memory when done
    free(m_main);
    free(m_pause);
    free(m_save);

    return 0;
}

