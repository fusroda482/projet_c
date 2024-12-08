/* --- OBJET.H --- */

#ifndef OBJET_H
#define OBJET_H

// JEU
// La structure

// Précaution : Map et non map
// pour pouvoir crée une instance map
// plus commode dans la lecture p->map
struct Map{

    char *border;
};


struct object{
    
    void (*action)(struct jeu *p);
    char *skin;
};

// Radeau
struct raft{
    
    int size;// c'est la moitié de la taille en réalité
    char *skin;
};


struct jeu {

    // Radeau et flotte
	int position;
    struct raft fleet[3];
    int raft; //index du radeau en cours d'utilisation

    // Joueur
	int score;
	char pseudo[20];
	int money;

    // Jeu
    struct Map map;

    // Objets
    struct object objects[3];
    int Is[HAUTEUR];
    int Js[HAUTEUR];
    int Ks[HAUTEUR];
    int first = 0;
    int N_objects = 0;
};

// PROTOTYPE
void initialiser_jeu(struct jeu *p);


// PROTOTYPES

int object_generator();
void bigger(struct jeu *p);
void smaller(struct jeu *p);

#endif
