#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/my.h"
#include <unistd.h>


void initGrilleWindow(sfRenderWindow* window){

}


void puissance4_function(sfRenderWindow* window,sfEvent event) {
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window) ) {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            /* Fermer la fenêtre en cas de fermeture ou si on appuie sur Escape */
             if (event.type == sfEvtClosed){
                 printf("Fermeture détectée\n");
                sfRenderWindow_close(window);
             }
               
        }
        
        sfRenderWindow_clear(window,sfWhite);
        
        /* Modification de la fenêtre */
        sfRenderWindow_display(window);
    }

    
    

}
