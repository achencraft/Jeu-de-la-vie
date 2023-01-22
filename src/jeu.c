/**
 * \file jeu.c
 * \brief implémentation des fonctions de jeu.
 */

#include "../include/jeu.h"
#include "../include/grille.h"

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	
	return v; 
}


int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0;
	v+= est_vivante(i-1,j-1,g);
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i-1,j+1,g);
	v+= est_vivante(i,j-1,g);
	v+= est_vivante(i,j+1,g);
	v+= est_vivante(i+1,j-1,g);
	v+= est_vivante(i+1,j,g);
	v+= est_vivante(i+1,j+1,g);
	
	return v;
}



void evolue_sans_vieillissement (grille *g, grille *gc, int (*fonction_comptage) (int, int, grille)){
	g->temps++;
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = fonction_comptage (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 && g->cellules[i][j] != -1) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

void evolue_avec_vieillissement (grille *g, grille *gc, int (*fonction_comptage) (int, int, grille)){
	g->temps++;
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (g->cellules[i][j] > 8) set_morte(i,j,*g);
			else {
			
			v = fonction_comptage (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				g->cellules[i][j]++;
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 && g->cellules[i][j] != -1)	set_vivante(i,j,*g);
				
			}
		}
		}
	}
	return;
}

oscil test_oscillant_full(grille g,int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)) ){
	
	
	grille b,c,e,f;
	alloue_grille (g.nbl, g.nbc, &b);	
	alloue_grille (g.nbl, g.nbc, &e);
	alloue_grille (b.nbl, b.nbc, &c);	
	alloue_grille (e.nbl, e.nbc, &f);
	copie_grille (g,b); 	
	copie_grille (g,e); 


	oscil sortie;
	
	int compteur1 = 0;
	int compteur2;
	int trouve = 0;
	int identique;
	
	while(compteur1 < 500 && trouve == 0){  //calcul de l'index du début de cycle
		//printf("compteur 1 %d\n",compteur1);
		compteur2 = 0;
		while(compteur2 < 500 && trouve == 0){  //calcul de la période
			//printf("compteur 2 %d\n",compteur2);
			vieillissement(&e,&f,cyclique);
			identique=compare_grille(b,e);
			
			if (identique == 1) {
				sortie.periode = compteur2+1;
				sortie.index_debut = compteur1;
				trouve = 1;
			}
			
			
		compteur2++;
		}
		vieillissement(&b,&c,cyclique);
		copie_grille (b,e);
		compteur1++;
	}
	
	
	libere_grille(&b);
	libere_grille(&c);
	libere_grille(&e);
	libere_grille(&f);
	


	return sortie;
}


int compare_grille(grille g1, grille g2){
	int identique = 1,i,j;
	(g1.nbl != g2.nbl) ? identique = 0 : 1;
	(g1.nbc != g2.nbc) ? identique = 0 : 1 ;
	for(i=0;i<g1.nbl;i++){
		for(j=0;j<g1.nbc;j++){
			(g1.cellules[i][j] != g2.cellules[i][j]) ? identique = 0 : 1;
		}
	}
	return identique;
}
