#include <SFML/Graphics.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/my.h"
#include "utils.c"



int isClicked = 0;

/**
 * @brief 
 * Fonction qui lance l'option choisie selon le click de l'utilisateur
 * se base sur la position des images
 * 
 * @param window 
 * @param event 
 */
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
            
        }
    }
}




int main() {
    sfVideoMode mode = {880, 730, 64};
    sfRenderWindow* window;
    sfFont* font = sfFont_createFromFile("font/Roboto.ttf");
    if(!font){
        return EXIT_FAILURE;
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
    sfTexture *texture = sfTexture_createFromFile("content/Puissance4.jpg",NULL);
    sfTexture *ordinateur = sfTexture_createFromFile("content/ordinateur.png",NULL);
    sfTexture *textureHumain = sfTexture_createFromFile("content/Humain.png",NULL);
    if(!textureHumain){
        return EXIT_FAILURE;
    }
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
    sfSprite_setTexture(sprite,texture,sfTrue);
    sfSprite_setPosition(buttonOrdinateur,psBouton);
    sfSprite_setScale(buttonOrdinateur,scale2);
    sfSprite_setTexture(buttonOrdinateur,ordinateur,sfTrue);
    /* Create the main window */
    window = sfRenderWindow_create(mode, "Puissance4",  sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window)) {
        /* Process events */
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
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
        is_click(window,event);
        
        /* modification de la fenetre */
        sfRenderWindow_display(window);
    }

    /* On clean l'ecran*/
     sfSprite_destroy(sprite);
     sfSprite_destroy(spriteHumain);
     sfTexture_destroy(textureHumain);
     sfText_destroy(choixOrdinateur);
     sfTexture_destroy(texture);
     sfText_destroy(textMenu);
     sfFont_destroy(font);
     sfRenderWindow_destroy(window);
    return 0;
}
