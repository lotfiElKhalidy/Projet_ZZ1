#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Qtable.h"



void allouerQ(Action_t  * Q[LIGNE][COLONNE]) {
    for (int i=0; i<LIGNE; i++) {
        
        for (int j=0; j<COLONNE; j++) {
            
            Q[i][j] = (Action_t *) malloc(sizeof(Action_t));

            if (!Q[i][j]) {
                printf("Erreur d'allocation");
            }
        }
    }
}

void initQ(Action_t * Q[LIGNE][COLONNE]) {
   for (int i=0; i<LIGNE; i++) {
        for (int j=0; j<COLONNE; j++) {

            // Cas général : Où on a 
            if (i > 0 && i < LIGNE-1 && j > 0 && j < COLONNE-1) {
                Q[i][j]->direction[0]   = 0;
                Q[i][j]->direction[1]   = 0;
                Q[i][j]->direction[2]   = 0;
                Q[i][j]->direction[3]   = 0;
            }
            
            // Cas des bords de la fenetre : où il y a 2 actions possibles
            else if (i == 0 && j == 0) {
                int kPossibleValues[2] = {1, 2};
                
                for(int k = 0; k < 2; k++) {
                    Q[i][j]->direction[kPossibleValues[k]]  = 0;
                }
                Q[i][j]->direction[0] = -1;
                Q[i][j]->direction[3] = -1;
            }

            else if (i == 0 && j == COLONNE-1) {
                int kPossibleValues[2] = {1, 3};

                for(int k = 0; k < 2; k++) {
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[0] = -1;
                Q[i][j]->direction[2] = -1;
            }

            else if (i == LIGNE-1 && j == 0) {
                int kPossibleValues[2] = {0, 2};

                for(int k = 0; k < 2; k++) {
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[1] = -1;
                Q[i][j]->direction[3] = -1;
            }

            else if (i == LIGNE-1 && j == COLONNE-1) {
                int kPossibleValues[2] = {0, 3};

                for(int k = 0; k < 2; k++) {
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[1] = -1;
                Q[i][j]->direction[2] = -1;
            }

            // Cas où les actions possibles sont 3
            else if (j == COLONNE-1) {
                int kPossibleValues[3] = {0, 1, 3};

                for(int k = 0; k < 3 ;k++){
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[2] = -1;
            }

            else if (i == LIGNE-1) {
                int kPossibleValues[3] = {0, 2, 3};

                for(int k = 0; k < 3; k++) {
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[1] = -1;
            }

            else if (j == 0) {
                int kPossibleValues[3] = {0, 1, 2};
                for(int k = 0; k < 3; k++){
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[3] = -1;
            }

            else if (i == 0) {
                int kPossibleValues[3] = {1, 2, 3};

                for(int k = 0; k < 3; k++) {
                    Q[i][j]->direction[kPossibleValues[k]] = 0;
                }
                Q[i][j]->direction[0] = -1;
            }
        }
    }
}

void afficherQ(Action_t * Q[LIGNE][COLONNE]) {
    for (int i=0; i<LIGNE; i++) {
        
        for (int j=0; j<COLONNE; j++) {
            
            printf("Up : %f\n", Q[i][j]->direction[0]);
            printf("Down : %f\n", Q[i][j]->direction[1]);
            printf("Right : %f\n", Q[i][j]->direction[2]);
            printf("Left : %f\n", Q[i][j]->direction[3]);
            printf("****************************************\n");
        }
    }
}