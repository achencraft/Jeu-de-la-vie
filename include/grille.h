/**
 * \file grille.h
 * \brief définition des générateurs de grilles
 *
 */


#ifndef __GRILLE_H
#define __GRILLE_H




#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * \brief structure grille 
 *
 * Représente la grille dans laquelle évolue les cellules.\n
 */
typedef struct {
	 int nbl;//!< Nombre de lignes.
	 int nbc;//!< Nombre de colonnes.
	 int temps;//!< Age de la grille
	 int** cellules;//!< Pointeur vers un tableau de tableaux de cellules.
	 } grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/**
 * \brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * \param [in] l Nombre de lignes.
 * \param [in] c Nombre de colonnes.
 * \param [out] g Pointeur vers la nouvelle grille.
 */
void alloue_grille (int l, int c, grille* g);

// libère une grille
/**
 * \brief libère une grille
 * \param [in] g pointeur vers une grille.
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/**
 * \brief alloue et initalise la grille g à partir d'un fichier
 * \param [in] filename nom du fichier contenant la grille.
 * \param [out] g pointeur vers la nouvelle grille.
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 * \brief rend vivante la cellule (i,j) de la grille g
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g grille à modifier.
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

// rend non-viable la cellule (i,j) de la grille g
/**
 * \brief rend non-viable la cellule (i,j) de la grille g
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g grille à modifier.
 */
static inline void set_nonviable(int i, int j, grille g){g.cellules[i][j] = -1;}

// rend morte la cellule (i,j) de la grille g
/**
 * \brief rend morte la cellule (i,j) de la grille g
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g grille à modifier.
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 * \brief teste si la cellule (i,j) de la grille g est vivante
 * \param [in] i ligne de la cellule.
 * \param [in] j colonne de la cellule.
 * \param [in] g grille à modifier.
 */
static inline int est_vivante(int i, int j, grille g){
	if ((i < 0) || (i >= g.nbl) || (j < 0) || (j >= g.nbc)) {return 0;}
	return g.cellules[i][j] > 0;
	}


// recopie gs dans gd (sans allocation)
/**
 * \brief recopie gs dans gd (sans allocation)
 * \param [in] gs grille à copier.
 * \param [in] gd grille de sortie.
 */
void copie_grille (grille gs, grille gd);

#endif
