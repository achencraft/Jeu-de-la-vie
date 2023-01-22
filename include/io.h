/**
 * \file io.h
 * \brief définition de l'affichage et de l'interaction avec l'utilisateur
 *
 */
 

#ifndef __IO_H
#define __IO_H



#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//gestion centralisée des couleurs
#define COULEUR_GRILLE ANSI_COLOR_YELLOW
#define COULEUR_CELLULE ANSI_COLOR_CYAN
#define COULEUR_CELLULE_NON_VIABLE ANSI_COLOR_RED
#define COULEUR_INSTRUCTION ANSI_COLOR_MAGENTA
#define COULEUR_INSTRUCTION_LETTRE ANSI_COLOR_GREEN
#define COULEUR_TITRE ANSI_COLOR_CYAN
#define COULEUR_ETAT ANSI_COLOR_GREEN
#define COULEUR_ETAT_VALEUR ANSI_COLOR_CYAN



// affichage d'un trait horizontal
/**
 * \brief affichage d'un trait horizontal
 * \param [in] c longueur du trait (en nombre de colonnes)
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 * \brief affichage d'une ligne de la grille
 * \param [in] c longueur de la ligne (en nombre de colonnes)
 * \param [in] ligne pointeur vers la ligne de la grille à afficher.
 */
void affiche_ligne (int c, int* ligne);

// affichage des instructions et informations de jeu
/**
 * \brief affichage des instructions et informations de jeu
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 * \param [in] g la grille à afficher
 */
void affichage_infos (int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)),grille);

// affichage d'une grille
/**
 * \brief affichage d'une grille
 * \param [in] g la grille à afficher
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 */
void affiche_grille (grille g, int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)));

// effacement d'une grille
/**
 * \brief effacement d'une grille
 * \param [in] g la grille à effacer
 */
void efface_grille (grille g);

// debute le jeu
/**
 * \brief lance le jeu
 * \param [in] g la grille g
 * \param [in] gc la grille gc
 */
void debut_jeu(grille *g, grille *gc);



// affiche les informations de l'oscillation dans le Terminal
/**
 * \brief affiche les informations de l'oscillation dans le Terminal
 * \param [in] oscillation, une structure de donnée contenant la période d'oscillation et son index de début
 * \param [in] g la grille à afficher
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 */
void affichage_oscillation_Terminal(oscil oscillation,grille g, int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)));


#endif
