#ifndef MY_H_
    #define MY_H_
    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Clock.h>
    #include <stdio.h>

    #define sfCf sfTexture_createFromFile
    #define sfWc sfRenderWindow_create

    void puissance4_function(sfRenderWindow* window,sfEvent event);


#endif