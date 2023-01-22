/**
 * \file jeu.h
 * \brief définition du moteur de jeu d'évolution des cellules
 *
 */


#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#include <stdbool.h>


/**
 * \brief structure oscil
 *
 * Contient les informations sur l'oscillation de la grille (sa période et l'index de départ)
 */
typedef struct {
	int periode;//!< la période d'oscillation
	int index_debut;//!< Le nombre de tour avant l'oscillation
} oscil;

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 * \brief gestion des modulos pour les bords de grille
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * 
 * modulo modifié pour traiter correctement les bords i=0 et j=0\n
 * dans le calcul des voisins avec bords cycliques\n
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
 * \brief comptage des voisins vivants cyclique
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g la grille à étudier.
 * \return Retourne le nombre de cellules vivantes voisines à la cellule.
 * 
 * compte le nombre de voisins vivants de la cellule (i,j)\n
 *les bords sont cycliques.\n
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont NON cycliques.
/**
 * \brief comptage des voisins vivants non-cyclique
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g la grille à étudier.
 * \return Retourne le nombre de cellules vivantes voisines à la cellule.
 * 
 * compte le nombre de voisins vivants de la cellule (i,j)\n
 *les bords sont NON cycliques.\n
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps sans vieillissement
/**
 * \brief fait évoluer la grille g d'un pas de temps sans vieillissement des cellules
 * \param [in] g la grille g
 * \param [in] gc la grille gc
 * \param [in] fonction_comptage pointeur vers la fonction comptage des voisins vivants, cyclique ou non.
 */
void evolue_sans_vieillissement (grille *g, grille *gc, int (*fonction_comptage) (int, int, grille));

// fait évoluer la grille g d'un pas de temps avec vieillissement
/**
 * \brief fait évoluer la grille g d'un pas de temps avec vieillissement des cellules
 * \param [in] g la grille g
 * \param [in] gc la grille gc
 * \param [in] fonction_comptage pointeur vers la fonction comptage des voisins vivants, cyclique ou non.
 */
void evolue_avec_vieillissement (grille *g, grille *gc, int (*fonction_comptage) (int, int, grille));


// va calculer l'oscillation d'une grille
/**
 * \brief calcul de l'oscillation
 * \param [in] g, la grille à analyser
 * \param [in] cyclique le pointeur de fonction vers les fonctions compter_voisins_vivants, cycliques ou non.
 * \param [in] vieillissement le pointeur de fonction vers les fonctions d'évolution, vieillissantes ou non.
 * \return Retourne une structure oscil contenant la période d'oscillation et l'index de début d'oscillation.
 */
oscil test_oscillant_full(grille g, int (*cyclique) (int, int, grille),void (*vieillissement) (grille*, grille*, int (*cyclique) (int, int, grille)) );


// comparaison de grilles
/**
 * \brief compare l'égalité de deux grilles
 * \param [in] a la première grille
 * \param [in] b la deuxième grille
 * \return Retourne 1 si les grilles sont égales, 0 sinon
 */
int compare_grille(grille a, grille b);
#endif
