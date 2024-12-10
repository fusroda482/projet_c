// En tête structure de jeu
// dont les fichiers
// - 
// -
// dépendent.
#ifndef JEU_H
#define JEU_H

// JEU
// La structure
struct jeu{
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
#endif
