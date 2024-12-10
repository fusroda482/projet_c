/* ----- MATERIAL.C ----- */
#include <stdio.h>

#include "material.h"
#include "game.h"

#define PMOD(a,b) ( ( (a) + (b) ) % b )

// Maps
const struct Map default_map = {"*"}; 

struct Map maps[1] = {default_map};


/* --- OBJETS --- */
// -- Actions --
//
// DIMINUE SCORE !!

// 1. Augmente score
void score_pp(struct jeu *p){
    
    p->score++;
}

// 2. Augmente taille
void bigger(struct jeu *p){

    p->index = (p->index + 1) % 3; // 3 tailles disponibles

    // Gestion collision en cas d'agrandissement
    // 1. se cogne contre le mur de droite
	if (p->position + fleet[p->index_fleet][p->index].size > LARGEUR){p->position--;}
    // 2. se cogne contre le mur de gauche	
	if (p->position - fleet[p->index_fleet][p->index].size < 0){p->position++;} 
}

// 3. Diminue taille
void smaller(struct jeu *p){

    p->index = PMOD(p->index - 1, 3);	
} 

// -- default --
/*struct object default_object_1 = {
    score_pp,
    "1"
}; 

struct object default_object_2 = {
    bigger,
    "2"    
};

struct object default_object_3 = {
    smaller,
    "3"
};
*/
static struct object objects[3] = {
    {score_pp, "1"},
    {bigger, "2"},
    {smaller, "3"}
};
    
struct object *get_objects(){
    return objects;
}

// Se resservir des struct default ???
// pour ne pas avoir à redéfinir les fonctions
// mais directement les skins


// --- FLEET ---


// -- SKINS --
// --default --
const struct raft default_raft_S = {
    1,
    "___"
};

const struct raft default_raft_M = {
    2,
    "_____"
};

const struct raft default_raft_L = {
    3,
    "_______"
};
// -- marine française --
// -- pirate --


struct raft fleet[1][3] = {
    {default_raft_S, default_raft_M, default_raft_L},
};

// -- ACTIONS --
void move_raft(struct jeu *p, char direction, char left, char right){
    
    if (direction == right && (p->position + fleet[p->index_fleet][p->index].size) > 0){p->position++;}

    if (direction == left && (p->position - fleet[p->index_fleet][p->index].size) > 0){p->position++;}
}
