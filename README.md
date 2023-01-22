README Lucas LETT  


hello world
#Le Jeu De La Vie  



mes numéros de versionnage sont les suivantes :  

v1.X = niveau 1 du projet  
v2.X = niveau 2 du projet   
v3.X = niveau 3 du projet   
v4.X = niveau 4 du projet   
v5.X = niveau 5 du projet   


###Auteur  
    Lucas LETT  
    
    
    
    

##Pré-requis

L'exécution du programme nécessite :

    le logiciel libC
    le logiciel gcc
    le logiciel make
    le logiciel doxygen
    le logiciel graphviz
    la librairie cairo.h
	la librairie cairo-xlib.h
	la librairie X11/Xlib.h
    
    
    
    
    

##Compilation et lancement

Récupérez l'ensemble du programme et mettez le dans un répertoire vide.  
Avec le Terminal, entrez la commande make si vous souhaitez avoir le jeu en version graphique.  
Dans le cas où vous préferez la version terminal, entrez la commande make MODE=TEXTE  

Executez votre programme avec la commande  
./bin/main ./grilles/<nom_de_la_grille.txt>






##Commandes en jeu  

Version Terminal  
Touche Entrée : faire évoluer la grille d'un pas.  
Touche c : Activer/Désactiver le voisinage cyclique.  
Touche v : Activer/Désactiver le vieillissement des cellules.  
Touche n : Ouvrir une nouvelle grille.  
Touche o : Calcul de l'oscillation de la grille.  
Touche q : Quitter le programme.  

Version Graphique  
Touche Entrée/Clic gauche : faire évoluer la grille d'un pas.  
Touche c : Activer/Désactiver le voisinage cyclique.  
Touche v : Activer/Désactiver le vieillissement des cellules.   
Touche n : Ouvrir une nouvelle grille.  
Touche o : Calcul de l'oscillation de la grille.  
Clic droit : Quitter le programme.  



##Generer la documentation  
Utilisez la commande make doc pour générer la documentation.  
Ouvrez la en double-cliquant sur index.html dans le dossier ./html qui a été généré.   
