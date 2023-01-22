/**
 * \file io.c
 * \brief implémentation des fonctions d'affichage et d'interaction
 */

#include "../include/io.h"


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf (COULEUR_GRILLE "|---" );
	printf(COULEUR_GRILLE"|\n"ANSI_COLOR_RESET);
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf (COULEUR_GRILLE"|   "); 
		else if (ligne[i] == -1){ printf (COULEUR_GRILLE"| "); printf(COULEUR_CELLULE_NON_VIABLE"X ");} 
		else {printf (COULEUR_GRILLE"| ");printf( COULEUR_CELLULE"%d ",ligne[i]-1);}
	printf(COULEUR_GRILLE"|\n"ANSI_COLOR_RESET);
	return;
}

void affichage_infos(int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)),grille g){
	printf(COULEUR_TITRE"\nLe Jeu De La Vie\n");
	printf(COULEUR_INSTRUCTION"\nInstruction :\n\nTouche ");
	printf(COULEUR_INSTRUCTION_LETTRE"Entrée");
	printf(COULEUR_INSTRUCTION" : faire évoluer la grille d'un pas.\nTouche ");
	printf(COULEUR_INSTRUCTION_LETTRE"c");
	printf(COULEUR_INSTRUCTION" : %s le voisinage cyclique.\nTouche ",(*cyclique == &compte_voisins_vivants_cyclique) ? "Désactiver" : "Activer");
	printf(COULEUR_INSTRUCTION_LETTRE"v");
	printf(COULEUR_INSTRUCTION" : %s le vieillissement des cellules.\nTouche ",(*vieillissement == &evolue_avec_vieillissement) ? "Désactiver" : "Activer");
	printf(COULEUR_INSTRUCTION_LETTRE"n");
	printf(COULEUR_INSTRUCTION" : Ouvrir une nouvelle grille.\nTouche ");
	printf(COULEUR_INSTRUCTION_LETTRE"o");
	printf(COULEUR_INSTRUCTION" : Calculer l'oscillation.\nTouche  ");
	printf(COULEUR_INSTRUCTION_LETTRE"q");
	printf(COULEUR_INSTRUCTION" : Quitter le programme.\n");
	
	printf(COULEUR_ETAT"\nCyclique : ");
	printf(COULEUR_ETAT_VALEUR"%s", (*cyclique == &compte_voisins_vivants_cyclique) ? "ON" : "OFF");
	printf(COULEUR_ETAT"\tVieillissement : ");
	printf(COULEUR_ETAT_VALEUR"%s", (*vieillissement == &evolue_avec_vieillissement) ? "ON" : "OFF");
	printf(COULEUR_ETAT"\tTemps d'évolution : ");
	printf(COULEUR_ETAT_VALEUR"%d "ANSI_COLOR_RESET,g.temps);
	
	
}


void affiche_grille (grille g, int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille))){
	int i, l=g.nbl, c=g.nbc;
	
	

	
	affichage_infos(cyclique, vieillissement, g);
	printf("\n");
	
	
	
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/*
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}*/
void efface_grille (grille g){
    for(int i=0;i<g.nbl*2 + 25;i++){
        printf("\e[A");
        printf("\e[2K");
    }
}


void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	int (*compte_voisins_vivants) (int, int, grille);
	compte_voisins_vivants = compte_voisins_vivants_cyclique;
	
	void (*evolution_vieillissement) (grille *, grille *, int (*compte_voisins_vivants) (int, int, grille));
	evolution_vieillissement = evolue_sans_vieillissement;

	
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case 'n':
			{ //touche "n" nouvelle grille

				efface_grille(*g);
				char tab[50];
				printf("nom de la grille à ouvrir ? ");
				scanf("%s",tab);
				printf("\e[A");
				printf("\e[2K");
				
				
				libere_grille(g);
				libere_grille(gc);				
				
				init_grille_from_file(tab,g);
				alloue_grille (g->nbl, g->nbc, gc);
				

				
				affiche_grille(*g, compte_voisins_vivants, evolution_vieillissement);
				//printf("\e[B");
				//printf("\e[B");
				//printf("\e[2K");
				//printf("\n\n");
				getchar();
				break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolution_vieillissement(g,gc,compte_voisins_vivants);
				efface_grille(*g);
				affiche_grille(*g,compte_voisins_vivants, evolution_vieillissement);
				break;
			}
			case 'c' :
			{	//touche "c" pour activer/desactiver le comptage cyclique des voisins vivants
				efface_grille(*g);
				if(*compte_voisins_vivants == &compte_voisins_vivants_cyclique)
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
				else
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
				affiche_grille(*g, compte_voisins_vivants, evolution_vieillissement);
				getchar();
				break;
			}
			case 'v' :
			{	//touche "v" pour activer/desactiver le vieillissement des cellules
				efface_grille(*g);
				
				if(*evolution_vieillissement == &evolue_sans_vieillissement)
					evolution_vieillissement = evolue_avec_vieillissement;
				else
					evolution_vieillissement = evolue_sans_vieillissement;
				affiche_grille(*g, compte_voisins_vivants, evolution_vieillissement);

				getchar();
				break;
			}
			case 'o' :
			{	//touche "v" pour activer/desactiver le vieillissement des cellules

				efface_grille(*g);
				affiche_grille(*g, compte_voisins_vivants, evolution_vieillissement);
				printf("Calcul en cours... Merci de patienter.\n");
				
				affichage_oscillation_Terminal(test_oscillant_full(*g, compte_voisins_vivants, evolution_vieillissement),*g, compte_voisins_vivants, evolution_vieillissement);

				getchar();
				break;
			}
			default : 
			{ // touche non traitée
				//printf("\n\e[1A");
				efface_grille(*g);
				affiche_grille(*g, compte_voisins_vivants, evolution_vieillissement);
				getchar();
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}

void affichage_oscillation_Terminal(oscil oscillation,grille g, int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille))){
	
	
	efface_grille(g);
	affiche_grille(g, cyclique, vieillissement);
				
	if(oscillation.periode == 1){
		
		if (oscillation.index_debut > 0){
			printf("La grille est stable dans %d.\n",oscillation.index_debut);		
		} else {
			printf("La grille est stable.\n");
		}
	} else {
		
		printf("La grille oscille sur une période de %d.\n",oscillation.periode);
		if (oscillation.index_debut > 0){
		printf("L'oscillation commence dans %d.\n",oscillation.index_debut);
		
	}
		
		
	}
		
		
		
	
	
	
}
