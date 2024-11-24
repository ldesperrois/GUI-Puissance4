#ifndef MY_H_
    #define MY_H_
    #include "SFML/Graphics.h"
    #include <stdlib.h>
    #include "SFML/Window.h"
    #include "SFML/System.h"
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <limits.h>
    #include <time.h>
    #include <ctype.h> 
 

    // Constantes de jeu
    #define NB_LIGNES 6
    #define NB_COLONNES 7
    #define PION_A 'X'
    #define PION_B 'O'
    #define INCONNU ' '
    const int VIDE;

    extern bool keyLeftPressed;
    extern bool keyRigthPressed;
    extern bool isPresseReturn;

    typedef int t_grille[NB_LIGNES][NB_COLONNES];

    


    // Textures
    const sfTexture* Yellow; 
    const sfTexture* Red;
    const sfTexture* texturePuissance4;
    const sfTexture *ordinateur;
    const sfTexture *textureHumain;

    const sfFont* font;

    // Fonctions
    int initTexture();
    int startGame();
    int initFont();
    sfVector2f centerXWindow(int sizeWindow,int sizeElement,float y);
    void is_click(sfRenderWindow* window,sfEvent event);
    void endGame(sfRenderWindow* window,sfEvent event,int winner);
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
    void jouerContreHumain(sfRenderWindow* window,sfEvent event);
    void jouerContreOrdi(sfRenderWindow* window,sfEvent event,bool isFirst);
    void menuOrdreJeu(sfRenderWindow* window,sfEvent event);
    void isClickOrdre(sfRenderWindow* window,sfEvent event);
    void showGrille(sfRenderWindow* window,t_grille grille);
    void backgroundMove(sfRenderWindow* window, sfSprite* backgroundSprite);
    void mooveCoin(sfRenderWindow* window,sfSprite* coin,sfEvent event,t_grille grille,int* joueur,int* winner,bool robot);
    void freeGrille(t_grille grille);
#endif