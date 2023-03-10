/**
 * \file grille.c
 * \brief implémentation des fonctions concernant les grilles
 */

#include "../include/grille.h"

void alloue_grille (int l, int c, grille* g){
	
	int i,j;

	g->nbl = l;
	g->nbc = c;
	g->temps = 0;
	
	//printf("l = %d\n",l);
	//printf("c = %d\n",c);
	
	g->cellules = (int **) malloc (l * sizeof(int*));
	for (i = 0; i<l; i++){
		g->cellules[i] = (int *) malloc (c * sizeof(int));
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			g->cellules[i][j] = 0;
		}
	}
	
	}


void libere_grille (grille * g){
	
	int i,j;
	
	for(i = 0; i<g->nbl; i++){
			free(g->cellules[i]);
			g->cellules[i] = NULL;
		}
	free(g->cellules);
	g->cellules=NULL;
	

}


void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,nonviable=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fscanf(pfile, "%d", & nonviable);
	for (n=0; n< nonviable; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_nonviable(i,j,*g);
	}
	
	
	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
