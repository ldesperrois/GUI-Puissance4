#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/my.h"
#include <unistd.h>



/**
 * @brief 
 * Déclaration des constantes
 * 
 */
const int SIZEW = 880;
const int SIZEH = 730;
const int ligne = 6;
const int colonnes = 7;
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
 * Fonction qui dessine les cercles
 * 
 * @param window 
 * @return sfRectangleShape* 
 */
void initGrilleWindow(sfRenderWindow* window){
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

}
/**
 * @brief 
 * Demande à l'ordinateur l'ordre de passage
 * 
 * @param window 
 */
void menuOrdreJeu(sfRenderWindow* window,sfEvent event){

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
    sfTexture *ordinateur = sfTexture_createFromFile("content/ordinateur.png",NULL);
    sfTexture *textureHumain = sfTexture_createFromFile("content/Humain.png",NULL);
    sfTexture_setSmooth(textureHumain,sfTrue);
    sfTexture_setSmooth(ordinateur,sfTrue);
    sfSprite *buttonOrdinateur = sfSprite_create();
    sfVector2f scale2 = {0.1,0.1};
    sfVector2f psBouton = {90,350};
    sfSprite_setPosition(buttonOrdinateur,psBouton);
    sfSprite_setScale(buttonOrdinateur,scale2);
    sfSprite_setTexture(buttonOrdinateur,ordinateur,sfTrue);
     // Creation de la texture
    sfTexture * texturePuissance4 = sfTexture_createFromFile("content/Puissance4.jpg",NULL);
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
    sfTime delay = sfSeconds(1);
    while (sfRenderWindow_isOpen(window) ) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape 
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
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
        if(sfClock_getElapsedTime(clock).microseconds >= delay.microseconds && !sfMouse_isButtonPressed(sfMouseLeft)){
            isClickOrdre(window,event);
        }
        
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    
    sfTexture_destroy(ordinateur);
    sfText_destroy(textChoixOrdre);
    sfText_destroy(choixHumain);
    sfText_destroy(choixOrdinateur);
    sfSprite_destroy(fondSprite);
    sfSprite_destroy(spriteHumain);
    sfTexture_destroy(texturePuissance4);



    

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
                
            }
        }
    }
}


void jouerContreOrdi(sfRenderWindow* window,sfEvent event,bool isFirst) {
    sfTexture * texturePuissance4 = sfTexture_createFromFile("content/Puissance4.jpg",NULL);
    sfVector2f scale = {0.87,0.87};
    sfSprite *fondSprite = sfSprite_create();
    sfSprite_setScale(fondSprite,scale);
    sfSprite_setTexture(fondSprite,texturePuissance4,sfTrue);
    sfTexture* Jaune = sfTexture_createFromFile("content/yellow.png",NULL);
    sfVector2f scaleCoin = {1,1};
    sfSprite* coin = sfSprite_create();
    sfTexture* Red = sfTexture_createFromFile("content/red.png",NULL);
    sfTexture_setSmooth(Red,sfTrue);
    sfTexture_setSmooth(Jaune,sfTrue);
    sfVector2f firstPosition = {130,10};
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
        }
        // Clear l'ecran
        // On affiche à l'ecran le fond de puissance4
        sfRenderWindow_drawSprite(window,fondSprite,NULL);
        sfRenderWindow_drawSprite(window,coin,NULL);
        
        initGrilleWindow(window);
        mooveCoin(window,coin,event);
        
        // Modification de la fenêtre 
        sfRenderWindow_display(window);
    }
    
    
    sfSprite_destroy(fondSprite);
    sfTexture_destroy(texturePuissance4);

}


void showGrille(sfRenderWindow* window){

}
