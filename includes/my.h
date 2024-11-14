#ifndef MY_H_
    #define MY_H_
    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Clock.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <limits.h>
    #include <time.h>
    #include <ctype.h> 
 

// Constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define INCONNU ' '


extern bool keyLeftPressed;
extern bool keyRigthPressed;
extern bool isPresseReturn;

typedef int t_grille[NB_LIGNES][NB_COLONNES];

const int VIDE;


    // Fonctions
    void initgrille(t_grille grille);
    bool grillePleine(t_grille grille);
    int estVainqueurOrdi(t_grille grille, int ligne, int colonne);
    bool estVainqueur(t_grille grille, int ligne, int colonne);
    int endGames(t_grille grille);
    int trouverLigne(t_grille t, int colonne);
    int evaluateSegment(t_grille grille, int ligne, int colonne, int delta_ligne, int delta_colonne, int joueur);
    int scorePosition(t_grille grille, int joueur);
    void placerPion(int ligne, int colonne, t_grille grille, int Pion);
    int minmax(t_grille t, int profondeur, int alpha, int beta, bool Estmax);
    int coup_ordi(t_grille t);
    void afficheGrille(t_grille grille);
    void jouerContreOrdi(sfRenderWindow* window,sfEvent event,bool isFirst);
    void menuOrdreJeu(sfRenderWindow* window,sfEvent event);
    void isClickOrdre(sfRenderWindow* window,sfEvent event);
    void showGrille(sfRenderWindow* window,t_grille grillex,sfTexture* red,sfTexture* yellow);
    void mooveCoin(sfRenderWindow* window,sfSprite* coin,sfEvent event,t_grille grille,int* joueur,sfTexture* red,sfTexture* yellox);
#endif