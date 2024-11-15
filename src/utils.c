#include "../includes/my.h"
// Bouger le fond d'ecran
void backgroundMove(sfRenderWindow* window, sfSprite* backgroundSprite) {
    // Facteur de mouvement
    float moveFactor = 0.1f;
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(backgroundSprite);
    
    sfVector2f backgroundPosition;
    backgroundPosition.x = (mousePosition.x * moveFactor) - (spriteBounds.width * moveFactor / 2);
    backgroundPosition.y = (mousePosition.y * moveFactor) - (spriteBounds.height * moveFactor / 2);

    if (backgroundPosition.x > 0) backgroundPosition.x = 0;
    if (backgroundPosition.y > 0) backgroundPosition.y = 0;
    if (backgroundPosition.x < windowSize.x - spriteBounds.width)
        backgroundPosition.x = windowSize.x - spriteBounds.width;
    if (backgroundPosition.y < windowSize.y - spriteBounds.height)
        backgroundPosition.y = windowSize.y - spriteBounds.height;
    sfSprite_setPosition(backgroundSprite, backgroundPosition);
}







