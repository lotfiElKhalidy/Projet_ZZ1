#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "grille.h"

void initialiser(int grille[LIGNE][COLONNE]) {
    for (int i=0; i<LIGNE; i++) {
        for (int j=0; j<COLONNE; j++) {
            grille[i][j] = 0;
        }   
    }
}

void afficherGrille(int grille[LIGNE][COLONNE]) {
    for(int i=0; i<LIGNE; i++) {
        for (int j=0; j<COLONNE; j++) {
            printf("%d", grille[i][j]);
        }
        printf("\n");
    }
    //printf("------------------------------\n");
}

void genererGrille(int grille[LIGNE][COLONNE]) {
    grille[0][6]=3;
    grille[6][0]=4;
    
    int k=0;

    while(k < NOMBRE_OBSTACLE/2) {
        int i=rand()%7;             //entre 0 et 6
        int j=rand()%7;             //entre 0 et 6
        if (grille[i][j]==0) {
            grille[i][j]=1;
            k++;
        }
    }
    while(k < NOMBRE_OBSTACLE) {
        int i=rand()%7;             //entre 0 et 6
        int j=rand()%7;             //entre 0 et 6
        
        if (grille[i][j]==0) {
            grille[i][j]=2;
            k++;
        }
    }

}

void drawWorldFromGrid(int grille[LIGNE][COLONNE], SDL_Texture * cash, SDL_Texture * bomb, SDL_Texture * flag,
                        SDL_Texture * carUp,SDL_Texture * carLeft, SDL_Texture * carDown,SDL_Texture * carRight, SDL_Window * window , 
                        SDL_Renderer * renderer, int action) {
    
    int abscisse;
    int ordonnee;

    for(int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {

            abscisse = 100 + j * 100;
            ordonnee = 20  + i * 80;

            switch(grille[i][j]) {
                case 1:
                    afficherCash(cash, window, renderer, abscisse, ordonnee);
                    break;

                case 2:
                    afficherBomb(bomb, window, renderer, abscisse, ordonnee);
                    break;

                case 3:
                    afficherFlag(flag, window, renderer, abscisse, ordonnee);
                    break;

                case 4:
                    switch(action){
                        case 0:
                            afficherVoitureUpDown(carUp, window, renderer, abscisse, ordonnee);
                            break;
                        case 1:
                            afficherVoitureUpDown(carDown, window, renderer, abscisse, ordonnee);
                            break;
                        case 2:
                            afficherVoitureRightLeft(carRight, window, renderer, abscisse, ordonnee);
                            break;
                        case 3:
                            afficherVoitureRightLeft(carLeft, window, renderer, abscisse, ordonnee);
                            break;

                    }
                
                    break;
                
                default:
                    break;
            }
        }
    }
     

}

void sauvegarderGrille(int grille[LIGNE][COLONNE], int grille1[LIGNE][COLONNE]) {

    for(int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {

            grille1[i][j] = grille[i][j];
        }
    }
}

void copieGrille(int source[LIGNE][COLONNE], int destination[LIGNE][COLONNE]) {

    for(int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {

            destination[i][j] = source[i][j];
        }
    }
}

void updateGrille(int grille[LIGNE][COLONNE], int action, int ** recompense, int * recompenseCumulee) {
    int x = 0;
    int y = 0;

    // Recherche la position courante
    for (int i = 0; i < LIGNE; i++) {

        for (int j = 0; j < COLONNE; j++) {

            if (grille[i][j] == 4) {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (action) {

        case 0:                 //Up
            if (x > 0) {
                grille[x][y] = 0;
                grille[x-1][y] = 4;
                *recompenseCumulee += recompense[x - 1][y];
                recompense[x - 1][y] = 0;
            }
            break;

        case 1:                 //Down
            if (x < LIGNE-1) {
                grille[x][y] = 0;
                grille[x + 1][y] = 4;
                *recompenseCumulee += recompense[x + 1][y];
                recompense[x + 1][y] = 0;
            }
            break;

        case 2 :                   //Right
            if (y < COLONNE-1) {
                grille[x][y] = 0;
                grille[x][y+1] = 4;
                *recompenseCumulee += recompense[x][y+1];
                recompense[x][y+1] = 0;
            }
            break;

        case 3:                 //Left
            if (y>0) {
                grille[x][y] = 0;
                grille[x][y-1] = 4;
                *recompenseCumulee += recompense[x][y-1];
                recompense[x][y-1] = 0;
            }
            break;

        default:
            break;
    }
}

void defineRewardFromGrid (int grille[LIGNE][COLONNE], int *** recompense) {

    for (int i = 0; i<LIGNE; i++) {

        for(int j = 0; j<COLONNE; j++) {

            switch (grille[i][j]) {

                case 1 :
                    (*recompense)[i][j] =  1;
                    break;

                case 2 :
                    (*recompense)[i][j] = -1;
                    break;

                case 3 :
                    (*recompense)[i][j] =  2;
                    break;

                default :
                    (*recompense)[i][j] =  0;
                    break;   
            } 
        } 
    }
}

void afficherRecompense (int ** recompense) {

    for (int i = 0; i<LIGNE; i++) {

        printf("|");

        for(int j = 0; j<COLONNE; j++) {

            printf("  %d  ", recompense[i][j]);
        }

        printf("|\n");
    }
}

void libererRecompense(int ** recompense) {
    for (int i = 0; i < LIGNE; i++) {
        free(recompense[i]);
    } 
    free(recompense);
}
