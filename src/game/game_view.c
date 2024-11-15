#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/my.h"
#include <unistd.h>

typedef int t_grille[NB_LIGNES][NB_COLONNES];
#define JOUEUR 1
#define ADVERSAIRE 2


int isClicked = 0;
/**
 * @brief 
 * Déclaration des constantes
 * 
 */
const int SIZEW = 880;
const int SIZEH = 730;
const int ligne = 6;
const int colonnes = 7;


const sfTexture* Yellow; 
const sfTexture* Red;
const sfFont* font;

int initTexture(){
    Yellow = sfTexture_createFromFile("content/yellow.png",NULL);
    if(!Yellow){
        return -1;
    }
    Red =  sfTexture_createFromFile("content/red.png",NULL);
    if(!Red){
        return -1;

    }
    texturePuissance4 = sfTexture_createFromFile("content/Puissance4.jpg",NULL);
    if(!texturePuissance4){
        return -1;
    }
    ordinateur = sfTexture_createFromFile("content/ordinateur.png",NULL);
    if(!ordinateur){
        return -1;
    }
    textureHumain = sfTexture_createFromFile("content/Humain.png",NULL);
    if(!textureHumain){
        return -1;
    }
    return 0;
}

int initFont(){
     font = sfFont_createFromFile("font/Roboto.ttf");
     return 0;
}


int startGame(){
    sfVideoMode mode = {880, 730, 64};
    sfRenderWindow* window;
    if(initFont()==-1){
        return -1;
    }
    if(initTexture()==-1){
        return -1;

    }
    sfFont_setSmooth(font,sfTrue);
    sfText *textMenu = sfText_create();
    sfText *choixOrdinateur = sfText_create();
    sfText *choixHumain = sfText_create();
    sfText_setFont(choixHumain,font);
    sfText_setCharacterSize(choixHumain,20);
    sfText_setFillColor(choixHumain,sfBlack);
    sfText_setString(choixHumain,"Humain");
    sfText_setFont(choixOrdinateur,font);
    sfText_setString(choixOrdinateur,"Ordinateur");
    sfText_setCharacterSize(choixOrdinateur,20);
    sfVector2f positionTexteOrdinateur = {140,320};
    sfText_setPosition(choixOrdinateur,positionTexteOrdinateur);
    sfText_setColor(choixOrdinateur,sfBlack);
    sfText_setFont(textMenu,font);
    sfText_setString(textMenu,"          Bienvenue sur Puissance 4\nveuillez cliquer sur une option de jeu.");
    sfText_setColor(textMenu,sfBlack);
    // positionner le texte
    // Positionner le texte
    sfVector2f coordTexte = {((880)-sfText_getLocalBounds(textMenu).width)/2.0f,20};
    sfText_setPosition(textMenu,coordTexte);
    sfTexture_setSmooth(ordinateur,sfTrue);
    sfTexture_setSmooth(textureHumain,sfTrue);
    sfSprite *sprite =  sfSprite_create();
    sfSprite *spriteHumain = sfSprite_create();
    sfSprite *buttonOrdinateur = sfSprite_create();
    sfVector2f scale = {0.90,0.90};
    sfVector2f scale2 = {0.1,0.1};
    sfVector2f psBouton = {90,350};
     sfSprite_setTexture(spriteHumain,textureHumain,sfTrue);     
    sfSprite_setScale(spriteHumain,scale2);
    sfVector2f psHumain= {(880-(sfSprite_getLocalBounds(spriteHumain).width)*0.1)-90,350};
    sfVector2f positionTexteHmain = {(880-(sfSprite_getLocalBounds(spriteHumain).width)*0.1)-20,320};
    sfText_setPosition(choixHumain,positionTexteHmain);
    sfSprite_setPosition(spriteHumain,psHumain);
    sfSprite_setScale(sprite,scale);
    sfSprite_setTexture(sprite,texturePuissance4,sfTrue);
    sfSprite_setPosition(buttonOrdinateur,psBouton);
    sfSprite_setScale(buttonOrdinateur,scale2);
    sfSprite_setTexture(buttonOrdinateur,ordinateur,sfTrue);
    window = sfRenderWindow_create(mode, "Puissance4",  sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window,30);
    while (sfRenderWindow_isOpen(window)) {
        /* Process events */
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            /* Close window : exit */
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(window);
            }
            is_click(window,event);
                
        }

        backgroundMove(window,sprite);
        // clear l'écran
        sfRenderWindow_clear(window,sfBlack);
        // On dessine les elements de la fenetre
        sfRenderWindow_drawSprite(window,sprite,NULL);
        sfRenderWindow_drawText(window,textMenu,NULL);
        sfRenderWindow_drawText(window,choixOrdinateur,NULL);
        sfRenderWindow_drawSprite(window,buttonOrdinateur,NULL);
        sfRenderWindow_drawSprite(window,spriteHumain,NULL);
        sfRenderWindow_drawText(window,choixHumain,NULL);
        
        /* modification de la fenetre */
        sfRenderWindow_display(window);
    }

    /* On clean l'ecran*/
     sfSprite_destroy(sprite);
     sfSprite_destroy(spriteHumain);
     sfTexture_destroy(textureHumain);
     sfText_destroy(choixOrdinateur);
     sfText_destroy(textMenu);
     sfFont_destroy(font);
     sfRenderWindow_destroy(window);
     return 0;
}


void is_click(sfRenderWindow* window,sfEvent event){
    sfVector2i positionMouse = sfMouse_getPosition(window);
    // Contre ordinateur
    if(positionMouse.x>=102 && positionMouse.x<=277){
        if(positionMouse.y>=377 && positionMouse.y<=525){
            if (event.type==sfEvtMouseButtonPressed) {
                menuOrdreJeu(window,event);

            }
        }

    }
    
    // Contre Humain
    if(positionMouse.x>=622 && positionMouse.x<=751){
        if(positionMouse.y<=376 && positionMouse.y<=516){
            if (event.type==sfEvtMouseButtonPressed) {
                jouerContreHumain(window,event);
            }
        }
    }
}


t_grille grille;


/**
 * @brief 
 * Fonction qui permet de chercher le minimum entre deux nombre
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float min(float a, float b) {
    return (a < b) ? a : b;
}


/**
 * @brief 
 * Demande à l'ordinateur l'ordre de passage
 * 
 * @param window 
 */
void menuOrdreJeu(sfRenderWindow* window,sfEvent event){
    initgrille(grille);
    initTexture();
    sfFont* font = sfFont_createFromFile("font/Roboto.ttf");
    sfText *choixHumain = sfText_create();
    sfText *choixOrdinateur = sfText_create();
    sfText_setFont(choixOrdinateur,font);
    sfText_setString(choixOrdinateur,"L'ordinateur");
    sfText_setCharacterSize(choixOrdinateur,20);
    sfVector2f positionTexteOrdinateur = {140,320};
    sfText_setPosition(choixOrdinateur,positionTexteOrdinateur);
    sfText_setColor(choixOrdinateur,sfBlack);
    sfText_setFont(choixHumain,font);
    sfText_setCharacterSize(choixHumain,20);
    sfText_setFillColor(choixHumain,sfBlack);
    sfText_setString(choixHumain,"Humain");
    sfText* textChoixOrdre = sfText_create();
    sfText_setFont(textChoixOrdre,font);
    sfText_setCharacterSize(textChoixOrdre,26);
    sfText_setString(textChoixOrdre,"Veuillez choisir qui commence en premier");
    sfText_setFillColor(textChoixOrdre,sfBlack);
    sfVector2f coordTexte = {((SIZEW)-sfText_getLocalBounds(textChoixOrdre).width)/2.0f,20};
    sfText_setPosition(textChoixOrdre,coordTexte);
    sfTexture_setSmooth(textureHumain,sfTrue);
    sfTexture_setSmooth(ordinateur,sfTrue);
    sfSprite *buttonOrdinateur = sfSprite_create();
    sfVector2f scale2 = {0.1,0.1};
    sfVector2f psBouton = {90,350};
    sfSprite_setPosition(buttonOrdinateur,psBouton);
    sfSprite_setScale(buttonOrdinateur,scale2);
    sfSprite_setTexture(buttonOrdinateur,ordinateur,sfTrue);
     // Creation de la texture
    sfTexture_setSmooth(texturePuissance4,sfTrue);
    sfVector2f scale = {0.87,0.87};
    sfSprite *spriteHumain = sfSprite_create();
    sfSprite *fondSprite = sfSprite_create();

    sfSprite_setScale(fondSprite,scale);
    sfSprite_setTexture(fondSprite,texturePuissance4,sfTrue);
    
    sfVector2f scaleHumain = {0.1,0.1};
    sfSprite_setScale(spriteHumain,scaleHumain);
    sfSprite_setTexture(spriteHumain,textureHumain,sfTrue);
    sfVector2f psHumain= {(880-(sfSprite_getLocalBounds(spriteHumain).width)*0.1)-90,350};
    sfVector2f positionTexteHmain = {(880-(sfSprite_getLocalBounds(spriteHumain).width)*0.1)-20,320};
    sfText_setPosition(choixHumain,positionTexteHmain);
    sfSprite_setPosition(spriteHumain,psHumain);
    // Boucle de la fenêtre
    sfClock* clock = sfClock_create();
    sfTime delay = sfSeconds(0.1);
    while (sfRenderWindow_isOpen(window) ) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape 
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
             }
             if(sfClock_getElapsedTime(clock).microseconds >= delay.microseconds ){
                isClickOrdre(window,event);
            }
        }
        // Clear l'ecran
        sfRenderWindow_clear(window,sfWhite);
        // On affiche à l'ecran le fond de puissance4
        sfRenderWindow_drawSprite(window,fondSprite,NULL);
        sfRenderWindow_drawText(window,textChoixOrdre,NULL);
        sfRenderWindow_drawText(window,choixOrdinateur,NULL);
        sfRenderWindow_drawSprite(window,buttonOrdinateur,NULL);
        sfRenderWindow_drawSprite(window,spriteHumain,NULL);
        sfRenderWindow_drawText(window,choixHumain,NULL);

        
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    
    sfTexture_destroy(ordinateur);
    sfText_destroy(textChoixOrdre);
    sfText_destroy(choixHumain);
    sfText_destroy(choixOrdinateur);
    sfSprite_destroy(fondSprite);
    sfSprite_destroy(spriteHumain);
}


void isClickOrdre(sfRenderWindow* window,sfEvent event){
    sfVector2i positionMouse = sfMouse_getPosition(window);
    // Ordinateur joue en premier
    if(positionMouse.x>=102 && positionMouse.x<=277){
        if(positionMouse.y>=377 && positionMouse.y<=525){
             if(event.type==sfEvtMouseButtonPressed){
                jouerContreOrdi(window,event,true);
            }
        }
    }
    // Humain joue en premier
    if(positionMouse.x>=622 && positionMouse.x<=751){
        if(positionMouse.y<=376 && positionMouse.y<=516){
            if(event.type==sfEvtMouseButtonPressed){
                jouerContreOrdi(window,event,false);

            }
        }
    }
}

void jouerContreOrdi(sfRenderWindow* window,sfEvent event,bool isFirst){
    int winner = -1;
    int colonne ;
    int joueur;
    sfSprite* coin = sfSprite_create();  

    if(isFirst){
        joueur=ADVERSAIRE;
        sfSprite_setTexture(coin,Red,sfTrue);

    }
    else{
        sfSprite_setTexture(coin,Yellow,sfTrue);
        joueur=JOUEUR;
    }
    sfTexture_setSmooth(texturePuissance4,sfTrue);
    sfVector2f scale = {0.88,0.88};
    sfSprite *fondSprite = sfSprite_create();
    sfSprite_setScale(fondSprite,scale);
    sfSprite_setTexture(fondSprite,texturePuissance4,sfTrue);
    sfVector2f scaleCoin = {1,1};
    
    sfTexture_setSmooth(Red,sfTrue);
    sfTexture_setSmooth(Yellow,sfTrue);
    sfVector2f firstPosition = {130+88*3,5};
    sfSprite_setPosition(coin,firstPosition);
    sfSprite_setScale(coin,scaleCoin);
    



    // Boucle de la fenêtre
    while (sfRenderWindow_isOpen(window) ) {

        while (sfRenderWindow_pollEvent(window, &event)) {
            // Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape 
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
             }
            if(joueur==ADVERSAIRE){
                mooveCoin(window,coin,event,grille,&joueur,&winner,true);
            }
            else if(joueur==JOUEUR){
                mooveCoin(window,coin,event,grille,&joueur,&winner,true);
            }

        }
        if(winner>=0){
            endGame(window,event,winner);
        }
        sfRenderWindow_clear(window,sfBlack);
        // Clear l'ecran
        // On affiche à l'ecran le fond de puissance4
        sfRenderWindow_drawSprite(window,fondSprite,NULL);
        sfRenderWindow_drawSprite(window,coin,NULL);

        showGrille(window,grille);
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    sfTexture_destroy(texturePuissance4);
}


void jouerContreHumain(sfRenderWindow* window,sfEvent event) {
    int winner = -1;
    int colonne ;
    int joueur = ADVERSAIRE;
    sfTexture_setSmooth(texturePuissance4,sfTrue);
    sfVector2f scale = {0.88,0.88};
    sfSprite *fondSprite = sfSprite_create();
    sfSprite_setScale(fondSprite,scale);
    sfSprite_setTexture(fondSprite,texturePuissance4,sfTrue);
    sfVector2f scaleCoin = {1,1};
    sfSprite* coin = sfSprite_create();  
    
    sfTexture_setSmooth(Red,sfTrue);
    sfTexture_setSmooth(Yellow,sfTrue);
    sfVector2f firstPosition = {130+88*3,5};
    sfSprite_setPosition(coin,firstPosition);
    sfSprite_setScale(coin,scaleCoin);
    sfSprite_setTexture(coin,Red,sfTrue);
    



    // Boucle de la fenêtre
    while (sfRenderWindow_isOpen(window) ) {

        while (sfRenderWindow_pollEvent(window, &event)) {
            // Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape 
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
             }
            if(joueur==ADVERSAIRE){
                mooveCoin(window,coin,event,grille,&joueur,&winner,false);
            }
            else if(joueur==JOUEUR){
                mooveCoin(window,coin,event,grille,&joueur,&winner,false);
            }

        }
        if(winner>=0){
            endGame(window,event,winner);
        }
        sfRenderWindow_clear(window,sfBlack);
        // Clear l'ecran
        // On affiche à l'ecran le fond de puissance4
        sfRenderWindow_drawSprite(window,fondSprite,NULL);
        sfRenderWindow_drawSprite(window,coin,NULL);

        showGrille(window,grille);
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    sfTexture_destroy(texturePuissance4);

}


void showGrille(sfRenderWindow* window,t_grille grille){
    sfTexture * textureGrille = sfTexture_createFromFile("content/grille.png",NULL);
    sfSprite *spriteGrille = sfSprite_create();
    sfVector2f scaleGrille = {0.88,0.88};
    sfTexture_setSmooth(textureGrille,sfTrue);
    sfSprite_setScale(spriteGrille,scaleGrille);
    sfSprite_setTexture(spriteGrille,textureGrille,sfTrue);
    sfFloatRect bounds = sfSprite_getGlobalBounds(spriteGrille);
    sfVector2f positionGrille = {(SIZEW-bounds.width)/2.0f,100};
    sfSprite_setPosition(spriteGrille,positionGrille);
    sfRenderWindow_drawSprite(window,spriteGrille,NULL);
    float positionFirstGrillex = 134.50;
    float positionFirstGrilley=114.25;
    for(int i=0;i<NB_LIGNES;i++){
        for(int j=0;j<NB_COLONNES;j++){
            if(grille[i][j]!=0){
                sfSprite* coin = sfSprite_create();
                float positionJoueurCoinx = positionFirstGrillex+(88.350*j);
                float positionJoueurCoiny = positionFirstGrilley+(91*i);
                sfVector2f positionCoin = {positionJoueurCoinx,positionJoueurCoiny};
                sfSprite_setPosition(coin,positionCoin);
                sfSprite_setScale(coin,scaleGrille);  
                if(grille[i][j]==JOUEUR){
                    sfSprite_setTexture(coin,Yellow,sfTrue);
                }
                else if(grille[i][j]==ADVERSAIRE){
                    sfSprite_setTexture(coin,Red,sfTrue);
                }
                sfRenderWindow_drawSprite(window,coin,NULL);
                sfSprite_destroy(coin);

            }
        }
    }

}


void endGame(sfRenderWindow* window,sfEvent event,int winner){
    sfTexture_setSmooth(texturePuissance4,sfTrue);
    sfVector2f scale = {0.88,0.88};
    sfSprite *fondSprite = sfSprite_create();
    sfSprite_setScale(fondSprite,scale);
    sfText* endText =sfText_create();
    sfText_setFont(endText,font);
    sfText_setCharacterSize(endText,28);
    
    
    if(winner==0){
        sfText_setString(endText,"Egalite");
        sfText_setFillColor(endText,sfWhite);
    }
    else if(winner==1){
        sfText_setString(endText,"Le joueur jaune gagne");
        sfText_setFillColor(endText,sfYellow);
    }
    else{
        sfText_setString(endText,"Le joueur rouge gagne");
        sfText_setFillColor(endText,sfRed);
    }
    sfVector2f positionEndText = {(880-sfText_getLocalBounds(endText).width)/2.0f,20};
    sfText_setPosition(endText,positionEndText);
    sfSprite_setTexture(fondSprite,texturePuissance4,sfTrue);
    // Boucle de la fenêtre
    while (sfRenderWindow_isOpen(window) ) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape 
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
             }
        }
        sfRenderWindow_clear(window,sfBlack);
        sfRenderWindow_drawSprite(window,fondSprite,NULL);
        showGrille(window,grille);
        sfRenderWindow_drawText(window,endText,NULL);
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    sfText_destroy(endText);
}
