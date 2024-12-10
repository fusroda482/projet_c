/* --- MATERIAL.H --- */

#ifndef MATERIAL_H
#define MATERIAL_H

#define LARGEUR 10
#define HAUTEUR 14
// JEU
// La structure

struct Map{

    char *border;
};

extern struct Map maps[1];
// Radeau
struct raft{
    
    int size;// c'est la moitié de la taille en réalité
    char *skin;
};

extern struct raft fleet[1][3];

//struct Map objects;


struct jeu{

    // Radeau et flotte
	int position;
    //struct raft fleet[3];
    int index; //index du radeau en cours d'utilisation
    int index_fleet;

    // Joueur
	int score;
	char pseudo[20];
	int money;

    // Jeu
    //struct Map map;
    int index_map;
    // Objets
    //struct object objects[3];
    int Is[HAUTEUR];
    int Js[HAUTEUR];
    int Ks[HAUTEUR];
    int first;
    int N_objects;
};


// Précaution : Map et non map
// pour pouvoir crée une instance map
// plus commode dans la lecture p->map
struct object{
    
    void (*action)(struct jeu *);
    char *skin;
};

struct object *get_objects();

//struct object default_objects[3];


// PROTOTYPES

// Objets
int object_generator();

// Raft
void move_raft(struct jeu *p, char key, char left, char right);
void score_pp(struct jeu *p);
void bigger(struct jeu *p);
void smaller(struct jeu *p);
#endif
