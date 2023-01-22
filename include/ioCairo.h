/**
 * \file ioCairo.h
 * \brief Focntions d'affichage des grilles avec Cairo
 *
 */


//fichier ioCairo.h

#ifndef __IOCAIRO__
#define __IOCAIRO__



#define SIZEX 1000
#define SIZEY 800

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"






// affichage d'une ligne de la grille CAIRO
/**
 * \brief affichage d'une ligne de la grille avec Cairo
 * \param [in] surface, la surface Cairo
 * \param [in] g, la grille à afficher
 * \param [in] ligne, le pointeur vers la ligne de la grille à afficher
 * \param [in] largeur, la largeur en pixel d'un carré
 * \param [in] position_verticale, le nombre de pixel entre la ligne et le haut de la fenêtre
 */
void affiche_ligne_Cairo (cairo_surface_t *surface,grille g,int* ligne,int largeur,int position_verticale);

// affichage d'une grille
/**
 * \brief affichage d'une grille
 * \param [in] surface, la surface Cairo
 * \param [in] g, la grille à afficher
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 */
void affiche_grille_Cairo (cairo_surface_t *surface,grille g,int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)));

// affichage d'un rectangle
/**
 * \brief affichage d'un rectangle Cairo
 * \param [in] surface, la surface Cairo
 * \param [in] x1, l'abscisse du coin haut gauche
 * \param [in] x2, l'ordonnee du coin haut gauche
 * \param [in] y1, l'abscisse du coin bas droite
 * \param [in] y2, l'ordonnee du coin bas droite
 * \param [in] type, valeur de la cellule de la grille à représenter
 */
void CairoPrintRectangle(cairo_surface_t *surface, double x1, double x2, double y1, double y2, int type);


// efface l'écran
/**
 * \brief efface l'écran
 * \param [in] surface, la surface Cairo
 */
void CairoBackground(cairo_surface_t *surface);

// affichage des infos de jeu
/**
 * \brief affichage des infos de jeu
 * \param [in] surface, la surface Cairo
 * \param [in] g, la grille à afficher
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 */
void afficher_info(cairo_surface_t *surface,grille g,int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)));


// affichage des infos d'oscillation
/**
 * \brief affichage des infos oscillation
 * \param [in] surface, la surface Cairo
 * \param [in] oscillation, une structure comprenant la période d'oscillation et l'index de début d'oscillation
 */
void affichage_oscillation(cairo_surface_t *surface, oscil oscillation);

// affichage calcul en cours
/**
 * \brief affiche le message "calcul en cours... Merci de patienter."
 * \param [in] surface, la surface Cairo
 */
void affichage_calcul_en_cours(cairo_surface_t *surface);

#endif
