/**
 * \file main.c
 * \brief La fichier main
 * 
 * 
 */



/**
 * \mainpage UE Technique de Développement
 * \author Lucas LETT
 * 
 * \section prérequis Pré-requis
 * L'exécution du programme nécessite :
 * - le logiciel libC
 * - le logiciel gcc
 * - le logiciel make
 * - le logiciel doxygen
 * - le logiciel graphviz
 * - la librairie cairo.h
 * - la librairie cairo-xlib.h
 * - la librairie X11/Xlib.h
 * 
 * 
 * 
 * \section compil Compilation et lancement
 * Récupérez l'ensemble du programme et mettez le dans un répertoire vide.\n
 * 
 * Avec le Terminal, entrez la commande **make** si vous souhaitez avoir le jeu en version graphique.\n
 * Dans le cas où vous préferez la version terminal, entrez la commande **make MODE=TEXTE**
 * 
 * Executez votre programme avec la commande 
 * \code{.sh}
 * ./bin/main ./grilles/<nom_de_la_grille.txt>
 * \endcode
 * 
 * 
 * 
 * 
 * \section cmd Commandes en jeu
 * 
 * 
 * **Version Terminal**\n
 * Touche Entrée : faire évoluer la grille d'un pas.\n
 * Touche c : Activer/Désactiver le voisinage cyclique.\n
 * Touche v : Activer/Désactiver le vieillissement des cellules.\n
 * Touche n : Ouvrir une nouvelle grille.\n
 * Touche o : Calcul de l'oscillation de la grille.\n
 * Touche q : Quitter le programme.
 * 
 * **Version Graphique**\n
 * Touche Entrée/Clic gauche : faire évoluer la grille d'un pas.\n
 * Touche c : Activer/Désactiver le voisinage cyclique.\n
 * Touche v : Activer/Désactiver le vieillissement des cellules.\n
 * Touche n : Ouvrir une nouvelle grille.\n
 * Touche o : Calcul de l'oscillation de la grille.\n
 * Clic droit : Quitter le programme.
 * 
 * \section doc Générer la documentation
 * 
 * Utilisez la commande **make doc** pour générer la documentation.\n
 * Ouvrez la en double-cliquant sur index.html dans le dossier ./html qui a été généré.
 * 
 * */
#include <stdio.h>



#include "../include/grille.h"
#include "../include/io.h"
#include "../include/jeu.h"





/**
 * \brief la fonction main
 * \param [in] argc le nombre d'argument (automatique)
 * \param [in] argv la liste des arguments.
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}
	

	
	
	system("clear");
	grille g, gc;
	int (*cyclique) (int, int, grille);
	cyclique = compte_voisins_vivants_cyclique;
	void (*vieillir) (grille *, grille *, int (*cyclique) (int, int, grille));
	vieillir = evolue_sans_vieillissement;
	
	
	
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g,cyclique, vieillir);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);

}
