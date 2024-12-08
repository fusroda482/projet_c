/* ------ SAVE.C ------ */


void save(struct jeu *p, int slot_number){
	
	FILE * sauvegarde = NULL;
	
	// Création Fichier Sauvegarde
	
	if(i == 1){savefile = fopen("Sauvegarde1.txt", "w");}
	if(i == 2){savefile = fopen("Sauvegarde2.txt", "w");}
	if(i == 3){savefile = fopen("Sauvegarde3.txt", "w");}
	
	
	
	if(sauvegarde == NULL){		// Erreur dans l'ouverture du programme
		
		printf("Problème à l'ouverture de sauvegarde. Fin de la sauvegarde.\n");
		return;
}
	
    // Saving p
    // Radeau et flotte
	fprintf(savefile, "%d\n", p->position);
    fprintf(savefile, "%s\n", p->fleet.name);
    fprintf(savefile, "%s\n", p->size); 

    // Joueur
    fprint(savefile, "%d\n", p->score);
    fprint(savefile, "%s\n", p->pseudo);
    fprint(savefile, "%d\n", p->money);
	
    // Jeu
    fprint(savefile, "%s\n", p->map.name);

	// Sauvegarder les objets 
	for(int i = 0; i < HAUTEUR; i++){
		for(int j = 0; j < LARGEUR; j++){
			fprintf(sauvegarde, "%d ", p.objets[i][j]);
		}
		
		fprintf(sauvegarde, "\n");
	}
	
	fprintf(sauvegarde, "%d\n", p.taille); // Sauvegarde taille
	fprintf(sauvegarde, "%d\n", p.score); // Sauvegarde score
	
	fputs(p.pseudo, sauvegarde); // Sauvegarde Pseudo
	fprintf(sauvegarde, "%d\n", p.argent); // Sauvegarde Argent 
	
	fclose(sauvegarde); // Fermermeture du fichier
		 
}


struct jeu charge_partie(int i){
	
	FILE * charge = NULL;
	
	// Lire les sauvegardes
	
	if(i == 1){charge = fopen("Sauvegarde1.txt", "r");}
	if(i == 2){charge = fopen("Sauvegarde2.txt", "r");}
	if(i == 3){charge = fopen("Sauvegarde3.txt", "r");}
	
	
	if(charge == NULL){
		//printf("Fichier Inexistant\n");
		struct jeu defaut = init_jeu(); 
		return defaut; // Renvoyer un jeu par defaut
	}
	
	struct jeu p;
	
	// Pour la position 
	fscanf(charge, "%d", &p.position);
	
	// Pour les objets
	for(int i = 0; i < HAUTEUR; i++){
		for(int j = 0; j < LARGEUR; j++){
			fscanf(charge, "%d", &p.objets[i][j]);
		}
	}
	
	// Pour la taille 
	fscanf(charge, "%d", &p.taille);
	
	// Pour le score
	fscanf(charge, "%d", &p.score);
	
	//Pour le pseudo
	fgets(p.pseudo, 20, charge);
	
	//Pour l'argent
	fscanf(charge, "%d", &p.argent);
	
	
	fclose(charge); // Fermeture du fichier
	
	return p; 
}



