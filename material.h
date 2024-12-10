/* --- MATERIAL.H --- */

#ifndef MATERIAL_H
#define MATERIAL_H

#define LARGEUR 10
#define HAUTEUR 14
// JEU
// La structure
struct jeu{

    // Radeau et flotte
	int position;
    struct raft fleet[3];
    int index; //index du radeau en cours d'utilisation

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
    int first;
    int N_objects;
};



// Précaution : Map et non map
// pour pouvoir crée une instance map
// plus commode dans la lecture p->map
struct Map{

    char *border;
};

struct Map default_map;


struct object{
    
    void (*action)(struct jeu *);
    char *skin;
};

struct object default_objects[3];

// Radeau
struct raft{
    
    int size;// c'est la moitié de la taille en réalité
    char *skin;
};

struct fleet{

    struct raft ships[3];
    char *name;
};

struct fleet default_fleet;


// PROTOTYPES

// Objets
int object_generator();

// Raft
void move_raft(struct jeu *p, char direction, char left, char right);
void score_pp(struct jeu *p);
void bigger(struct jeu *p);
void smaller(struct jeu *p);
#endif
