#include <stdio.h>

#include "objet.h"

// Maps
struct Map default_map{'*'}; 


/* --- OBJETS --- */
// -- Actions --
// 1. Augmente score
void score_pp(struct jeu *p){
    
    p->score++;
}

// 2. Augmente taille
void bigger(struct jeu *p){

    p->raft = (p->raft + 1) % 3; // 3 tailles disponibles

    // Gestion collision en cas d'agrandissement
    // 1. se cogne contre le mur de droite
	if (p->position + p->fleet[p->raft].size > LARGEUR){p->position--;}
    // 2. se cogne contre le mur de gauche	
	if (p->position - p->fleet[p->raft].size < 0){p->position++;}; 
}

// 3. Diminue taille
void smaller(struct jeu *p){

    p->raft = PMOD(p->raft - 1, 3);	
} 

// -- default --
struct object default_object_1 = {
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

struct object default_objects[3] = {
    default_object_1,
    default_object_2,
    default_object_3
};


// Se resservir des struct default ???
// pour ne pas avoir à redéfinir les fonctions
// mais directement les skins



// Fleet
// --default --
struct raft default_raft_S{
    1,
    "___"
};

struct raft default_raft_M{
    2,
    "_____"
};

struct raft default_raft_L{
    3,
    "_______"
};
// -- marine française --
// -- pirate --

struct fleet default_fleet = {
    {default_raft_S, default_raft_M, default_raft_L},
    "default"
};
