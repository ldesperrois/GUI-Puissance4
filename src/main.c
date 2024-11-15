#include <SFML/Graphics.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/my.h"
#include "utils.c"


int main() {
    int result = startGame();
    if(result==-1){
        perror("Erreur lors de l'execution du jeu");
    }
    return 0;
}
