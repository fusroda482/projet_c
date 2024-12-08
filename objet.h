/* --- OBJET.H --- */

#ifndef OBJET_H
#define OBJET_H

// JEU
// La structure
struct jeu {
	int position;
	int objets[HAUTEUR][LARGEUR];
	int score;
    int taille;
	struct theme_prototype theme;
    struct skin_prototype skin;
    //Nouveaux :
	char pseudo[20];
	int argent;
	
};
// PROTOTYPE
void initialiser_jeu(struct jeu *p);


// PROTOTYPES

int object_generator();
void bigger(struct jeu *p);
void smaller(struct jeu *p);

#endif
