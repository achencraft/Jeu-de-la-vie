/**
 * \file mainCairo.c
 * \brief La fichier main Cairo
 * 
 * 
 */



//fichier mainCairo.c



#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
//#include <X11/Xatom.h>  //tentative de mise en fullScreen


#include "../include/grille.h"
#include "../include/jeu.h"
#include "../include/ioCairo.h"


#define SIZEX 1000
#define SIZEY 800


/* //fonction de mise en Fullscreen
 * /**
 * \brief la fonction fullscreen
 * \param [in] dpy 
 * \param [in] win
 
static void fullscreen(Display* dpy, Window win)
{
  Atom atoms[2] = { XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False), None };
  XChangeProperty(dpy, win, XInternAtom(dpy, "_NET_WM_STATE", False),
                  XA_ATOM, 32, PropModeReplace, (unsigned char*) atoms, 1);
}
*/



/**
 * \brief la fonction main
 * \param [in] argc le nombre d'argument (automatique)
 * \param [in] argv la liste des arguments.
 */
int main (int argc, char ** argv) {
	
	
	
	
	
	grille g, gc;
	int (*cyclique) (int, int, grille);
	cyclique = compte_voisins_vivants_cyclique;
	void (*vieillir) (grille *, grille *, int (*cyclique) (int, int, grille));
	vieillir = evolue_sans_vieillissement;
	
	
	
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	

	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));
	//fullscreen (dpy, win);

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	
	
		// create cairo surface
	cairo_surface_t *cs; 

	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);


	int (*compte_voisins_vivants) (int, int, grille);
	compte_voisins_vivants = compte_voisins_vivants_cyclique;
	
	void (*evolution_vieillissement) (grille *, grille *, int (*compte_voisins_vivants) (int, int, grille));
	evolution_vieillissement = evolue_sans_vieillissement;

	int boucle = 1;
	
	//printf("%d %d",cairo_xlib_surface_get_height (cs),cairo_xlib_surface_get_width (cs));
	

	// run the event loop
	while(boucle==1) {
		//boucle = ecouteur_evenements(cs,g,gc,dpy,e,compte_voisins_vivants,evolution_vieillissement);
		
		
		XNextEvent(dpy, &e);

		switch (e.type)
		{
			
			case KeyPress:{	
				
				
				switch(e.xkey.keycode)
				{
					case 55	: //touche v
						if(*evolution_vieillissement == &evolue_sans_vieillissement)
							evolution_vieillissement = evolue_avec_vieillissement;
						else
							evolution_vieillissement = evolue_sans_vieillissement;
							
							CairoBackground(cs);
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
						break;
					case 54: //touche c
						if(*compte_voisins_vivants == &compte_voisins_vivants_cyclique)
							compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
						else
							compte_voisins_vivants = compte_voisins_vivants_cyclique;
							
							CairoBackground(cs);
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
						break;
					case 57: //touche n
						CairoBackground(cs);
						


						char tab[50];
						printf("nom de la grille à ouvrir ? ");
						scanf("%s",tab);
						printf("\e[A");
						printf("\e[2K");
						
						
						libere_grille(&g);
						libere_grille(&gc);				
						
						init_grille_from_file(tab,&g);
						alloue_grille (g.nbl, g.nbc, &gc);
						

						
						affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);

						getchar();
						break;
						
					case 36: //touche entrée (permet d'évoluer sans spam click la souris)
					{
							evolution_vieillissement(&g,&gc,compte_voisins_vivants);
							
							CairoBackground(cs);
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
							break;
					 }		
					case 32: //touche o
							{
							CairoBackground(cs);	
							affichage_calcul_en_cours(cs);
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
							
							affichage_oscillation(cs,test_oscillant_full(g,compte_voisins_vivants,evolution_vieillissement));
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
							break;
						}
				}
				break;	
			}
			case ButtonPress:{
				switch(e.xbutton.button)
					{
						case 1:   //left click
							evolution_vieillissement(&g,&gc,compte_voisins_vivants);
							
							CairoBackground(cs);
							affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
							break;
						case 3:  //right click
							boucle = 0;
							break;
						}
					break;
					}
			default :
				CairoBackground(cs);
				affiche_grille_Cairo(cs,g,compte_voisins_vivants, evolution_vieillissement);
				break;
		}
	}
		
		//if(e.type==Expose && e.xexpose.count<1) {


	
	
	libere_grille(&g);
	libere_grille(&gc);
		
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}
