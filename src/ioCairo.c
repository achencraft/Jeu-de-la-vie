/**
 * \file ioCairo.c
 * \brief affichage Cairo
 */

#include "../include/ioCairo.h"



void affiche_ligne_Cairo (cairo_surface_t *surface,grille g,int* ligne,int largeur_case,int position_verticale){
	int i;
	int espace = largeur_case > 50 ? 25 : largeur_case/2;

	int x1_depart = ((SIZEX-(g.nbc*largeur_case + espace*(g.nbc-1)))/2)-1;
	int x2_depart = ((SIZEY-(largeur_case*g.nbl + espace*(g.nbl-1)))/2)-1+position_verticale;
	int x1=x1_depart, x2=x2_depart;
	
	
	for (i=0; i<g.nbc; ++i){
	
	CairoPrintRectangle(surface, x1, x2, largeur_case, largeur_case,ligne[i]);
	
	x1=x1+largeur_case+espace;
	
	}	
	return;
}

void affiche_grille_Cairo (cairo_surface_t *surface,grille g,int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille))){
	int i, l=g.nbl, c=g.nbc;
	
	
	afficher_info(surface,g,cyclique,vieillissement);

	
	int largeur_case,ligne = 1;
	int largeur_carre = (SIZEX-300)/c;
	int hauteur_carre = (SIZEY-311)/l;
	if(largeur_carre <= hauteur_carre) largeur_case = largeur_carre;
	else largeur_case = hauteur_carre;
	
	int position_verticale = 30;
	
	int espace = largeur_case > 50 ? 25 : largeur_case/2;
	
	
	
	for (i=0; i<l; ++i) {
		affiche_ligne_Cairo(surface,g,g.cellules[i],largeur_case,position_verticale);
		ligne++;
		position_verticale = position_verticale + largeur_case + espace;
	}	
	return;
	
	
}


void CairoBackground(cairo_surface_t *surface){
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);    //noir
	cairo_paint(cr);
	
	cairo_destroy(cr); // destroy cairo mask
}


void CairoPrintLine (cairo_surface_t *surface, double x1, double x2, double y1, double y2, int largeur){
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
	
	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_move_to (cr, x1, x2);
	cairo_line_to(cr, y1,y2);
	cairo_set_line_width (cr, largeur);
	cairo_stroke (cr);
	
	cairo_destroy(cr); // destroy cairo mask
}

void CairoPrintRectangle(cairo_surface_t *surface, double x1, double x2, double y1, double y2, int type){
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
	
	cairo_rectangle(cr,x1,x2,y1,y2);
	
	switch(type){
		case -1 : cairo_set_source_rgb (cr, 0.0, 0.1, 0.2);  //cellule age 0    bleu foncé
			break;
		case 0 : cairo_set_source_rgb (cr, 0.0, 0.2, 0.6);  //cellule morte    bleu
			break;
		case 1 : cairo_set_source_rgb (cr, 0.6, 0.9, 0.3);  //cellule age 0    vert slime
			break;
		case 2 : cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);  //cellule age 1    vert normal
			break;
		case 3 : cairo_set_source_rgb (cr, 0.5, 0.55, 0.2);  //cellule age 2    vert kaki
			break;
		case 4 : cairo_set_source_rgb (cr, 0.8, 0.82, 0.0);  //cellule age 3    jaune/vert
			break;
		case 5 : cairo_set_source_rgb (cr, 1.0, 1.0, 0.0);  //cellule age 4    jaune
			break;
		case 6 : cairo_set_source_rgb (cr, 0.9, 0.5, 0.08);  //cellule age 5    orange
			break;
		case 7 : cairo_set_source_rgb (cr, 1.0, 0.3, 0.0);  //cellule age 6    rouge clair
			break;
		case 8 : cairo_set_source_rgb (cr, 1, 0.0, 0.0);  //cellule age 7    rouge
			break;
		case 9 : cairo_set_source_rgb (cr, 0.8, 0.0, 0.0);  //cellule age 8    rouge foncé
			break;

			
	}
	
	
	cairo_fill(cr);	
	
	cairo_destroy(cr); // destroy cairo mask
}


void afficher_info(cairo_surface_t *surface,grille g,int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille))){
	
	
	cairo_t *cr;
	cr=cairo_create(surface);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 

	  cairo_select_font_face(cr, "Purisa",
		  CAIRO_FONT_SLANT_NORMAL,
		  CAIRO_FONT_WEIGHT_BOLD);

  cairo_set_font_size(cr, 13);


	//la zone de texte fait au minimum 550px de large
	int debut_texte = (SIZEX-550)/2;
	
	//vieillir
	cairo_move_to(cr, debut_texte + 0, 20);
	char vieillir[100] = "Vieillissement = ";
	cairo_show_text(cr, vieillir);
	
	cairo_move_to(cr, debut_texte + 120, 20);
	if(*vieillissement == &evolue_sans_vieillissement)
		cairo_show_text(cr, "OFF");
	else 
		cairo_show_text(cr, "ON");
	
	//cyclique
	cairo_move_to(cr, debut_texte + 200, 20);
	char cycle[100] = "Cyclique = ";
	cairo_show_text(cr, cycle);
	
	cairo_move_to(cr, debut_texte + 280, 20);
	if(*cyclique == &compte_voisins_vivants_cyclique)
		cairo_show_text(cr, "ON");
	else 
		cairo_show_text(cr, "OFF");
		
	//nbr_de_pas
	char str[12];
	sprintf(str, "%d", g.temps);
	
	cairo_move_to(cr, debut_texte + 350, 20);
	char temps[100] = "Temps d'évolution = ";
	cairo_show_text(cr, temps);
	cairo_move_to(cr, debut_texte + 510, 20);
	cairo_show_text(cr, str);
	
	
	
	

	cairo_destroy(cr); // destroy cairo mask
}

void affichage_oscillation(cairo_surface_t *surface, oscil oscillation){
		CairoBackground(surface);	

	cairo_t *cr;
	cr=cairo_create(surface);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
	cairo_select_font_face(cr, "Purisa",
		  CAIRO_FONT_SLANT_NORMAL,
		  CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 13);

	char periode[12];
	sprintf(periode,"%d",oscillation.periode);
		
	char index[12];
	sprintf(index,"%d",oscillation.index_debut);
	
	if(oscillation.periode == 1){
		


		char stable[100] = "La grille est stable ";
		char stable_index[100] = "La grille est stable dans ";

		if (oscillation.index_debut > 0){
		//la zone de texte fait au minimum 200px de large
		int debut_texte = (SIZEX-200)/2;

		cairo_move_to(cr, debut_texte, 40);
		cairo_show_text(cr, stable_index);
		cairo_move_to(cr, debut_texte + 190, 40);
		cairo_show_text(cr, index);

		} else {
			int debut_texte = (SIZEX-170)/2;
			cairo_move_to(cr, debut_texte, 40);
			cairo_show_text(cr, stable);
		}
		
	} else {
	
		//la zone de texte fait au minimum 270px de large
		int debut_texte = (SIZEX-270)/2;

		char cycle_periode1[100] = "La grille oscille sur une période de ";
		char cycle_index1[100] = "L'oscillation commence dans ";



		cairo_move_to(cr, debut_texte, 40);
		cairo_show_text(cr, cycle_periode1);
		cairo_move_to(cr, debut_texte + 260, 40);
		cairo_show_text(cr, periode);

		if (oscillation.index_debut > 0){
		
		cairo_move_to(cr, debut_texte + 20, 60);
		cairo_show_text(cr, cycle_index1);
		cairo_move_to(cr, debut_texte + 240, 60);
		cairo_show_text(cr, index);
		}
	
	
	}
	cairo_destroy(cr); // destroy cairo mask
}

void affichage_calcul_en_cours(cairo_surface_t *surface){
		cairo_t *cr;
	cr=cairo_create(surface);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
	cairo_select_font_face(cr, "Purisa",
		  CAIRO_FONT_SLANT_NORMAL,
		  CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 13);
    
    
    int debut_texte = (SIZEX-550)/2+130;
    
    char msg[100] = "Calcul en cours...   Merci de patienter.";
    cairo_move_to(cr, debut_texte, 40);
	cairo_show_text(cr, msg);
}
