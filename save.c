/* ------ SAVE.C ------ */

#include <stdio.h>

#include "material.h"
#include "game.h"

void save(struct jeu *p, int slot_number){
	
	FILE * savefile = NULL;
	
	// Création Fichier Sauvegarde
	
	if(slot_number == 1){savefile = fopen("Sauvegarde1.txt", "w");}
	if(slot_number == 2){savefile = fopen("Sauvegarde2.txt", "w");}
	if(slot_number == 3){savefile = fopen("Sauvegarde3.txt", "w");}
	
	if(savefile == NULL){		
        // Erreur dans l'ouverture du programme
	    printf("Problème à l'ouverture de sauvegarde. Fin de la sauvegarde.\n");
		return;
}
	
    // Saving p
    // Radeau et flotte
	fprintf(savefile, "%d\n", p->position);
    fprintf(savefile, "%d\n", p->index);
    fprintf(savefile, "%d\n", p->index_fleet);
    fprintf(savefile, "%d\n", p->index_map);

    // Joueur
    fprintf(savefile, "%d\n", p->score);
    fprintf(savefile, "%s\n", p->pseudo);
    fprintf(savefile, "%d\n", p->money);
	

	// Sauvegarder les objets 
    for (int i = p->first; i < p->N_objects; i++){
        fprintf(savefile, "%d ", p->Is[i]);
    }

    fprintf(savefile, "\n");

    for (int i = p->first; i < p->N_objects; i++){
        fprintf(savefile, "%d ", p->Js[i]);
    }

    fprintf(savefile, "\n");

    for (int i = p->first; i < p->N_objects; i++){
        fprintf(savefile, "%d ", p->Ks[i]);
    }

    fprintf(savefile, "%d", p->first);
    fprintf(savefile, "%d", p->N_objects);

	fclose(savefile); // Fermermeture du fichier
}


struct jeu load(int slot_number){
	
	FILE * loadfile = NULL;
	
	// Lire les sauvegardes
	
	if(slot_number == 1){loadfile = fopen("Sauvegarde1.txt", "r");}
	if(slot_number == 2){loadfile = fopen("Sauvegarde2.txt", "r");}
	if(slot_number == 3){loadfile = fopen("Sauvegarde3.txt", "r");}
	
	struct jeu p;

	if(loadfile == NULL){
		//printf("Fichier Inexistant\n");
        
        init_jeu(&p);
		return p; // Renvoyer un jeu par defaut
	}
	
    // Radeau et flotte
    fscanf(loadfile, "%d", &p.position);
    fscanf(loadfile, "%d", &p.index);
    fscanf(loadfile, "%d", &p.index_fleet);
    fscanf(loadfile, "%d", &p.index_map);

    // Joueur
    fscanf(loadfile, "%d", &p.score);
    fscanf(loadfile, "%s", p.pseudo);
    fscanf(loadfile, "%d", &p.money);

    // Jeu
    

	// Sauvegarder les objets // Y REVENIR !
    for (int i = p.first; i < p.N_objects; i++){
        fscanf(loadfile, "%d", &p.Is[i]);
    }
    for (int i = p.first; i < p.N_objects; i++){
        fscanf(loadfile, "%d", &p.Js[i]);
    }
    for (int i = p.first; i < p.N_objects; i++){
        fscanf(loadfile, "%d", &p.Ks[i]);
    }
	
    
    fscanf(loadfile, "%d", &p.first);
    fscanf(loadfile, "%d", &p.N_objects);


    fclose(loadfile); // Fermeture du fichier
	
	return p; 
}
