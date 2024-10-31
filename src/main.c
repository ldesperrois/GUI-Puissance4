#include <SFML/Graphics.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/my.h"

void is_click(sfRenderWindow* window,sfEvent event){
    sfVector2i positionMouse = sfMouse_getPosition(window);
    if(positionMouse.x>=58 && positionMouse.x<=223){
        if(positionMouse.y>=369 && positionMouse.y<=525){
            if(event.type==sfEvtMouseButtonPressed){
                puissance4_function(window,event);
            }
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
    sfText_setFont(choixOrdinateur,font);
    sfText_setString(choixOrdinateur,"Ordinateur");
    sfText_setCharacterSize(choixOrdinateur,20);
     sfVector2f scale3 = {85,320};
    sfText_setPosition(choixOrdinateur,scale3);
    sfText_setColor(choixOrdinateur,sfBlack);
    sfText_setFont(textMenu,font);
    sfText_setString(textMenu,"          Bienvenue sur Puissance 4\nveuillez selectionner une option de jeu.");
    sfText_setColor(textMenu,sfBlack);
    // Positionner le texte
    sfVector2f coordTexte = {((880)-sfText_getLocalBounds(textMenu).width)/2.0f,20};
    sfText_setPosition(textMenu,coordTexte);
    sfTexture *texture = sfTexture_createFromFile("content/Puissance4.jpg",NULL);
    sfTexture *ordinateur = sfTexture_createFromFile("content/ordinateur.png",NULL);
    sfTexture_setSmooth(ordinateur,sfTrue);
    sfSprite *sprite =  sfSprite_create();
    sfSprite *buttonOrdinateur = sfSprite_create();
    sfVector2f scale = {0.87,0.87};
    sfVector2f scale2 = {0.1,0.1};

    sfVector2f psBouton = {40,350};
    sfSprite_setScale(sprite,scale);
    sfSprite_setTexture(sprite,texture,sfTrue);

    sfSprite_setPosition(buttonOrdinateur,psBouton);
    
    sfSprite_setScale(buttonOrdinateur,scale2);
    sfSprite_setTexture(buttonOrdinateur,ordinateur,sfTrue);
    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML Window",  sfClose, NULL);
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
        
        /* Clear the screen */
        sfRenderWindow_clear(window,sfBlack);
        
        // On dessine les elements de la fenetre
        sfRenderWindow_drawSprite(window,sprite,NULL);
        sfRenderWindow_drawText(window,textMenu,NULL);
        sfRenderWindow_drawText(window,choixOrdinateur,NULL);
        sfRenderWindow_drawSprite(window,buttonOrdinateur,NULL);
        is_click(window,event);
        /* modification de la fenetre */
        sfRenderWindow_display(window);
    }

    /* On clean l'ecran*/
     sfSprite_destroy(sprite);
     sfTexture_destroy(texture);
     sfText_destroy(textMenu);
     sfFont_destroy(font);
     sfRenderWindow_destroy(window);
    

    return EXIT_SUCCESS;
}
