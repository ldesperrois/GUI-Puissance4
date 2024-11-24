/**
 * @file main.c
 * @author Lucas Desperrois (lucas-desperrois.fr)
 * @brief 
 * @version 0.1
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/my.h"


int main() {
    int result = startGame();
    if(result==-1){
        perror("Erreur lors de l'execution du jeu");
    }
    return 0;
}
