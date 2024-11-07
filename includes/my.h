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

    void jouerContreOrdi(sfRenderWindow* window,sfEvent event,bool isFirst);
    void menuOrdreJeu(sfRenderWindow* window,sfEvent event);
    void isClickOrdre(sfRenderWindow* window,sfEvent event);
    void showGrille(sfRenderWindow* grille);
    void mooveCoin(sfRenderWindow* window,sfSprite* coin,sfEvent event);

#endif