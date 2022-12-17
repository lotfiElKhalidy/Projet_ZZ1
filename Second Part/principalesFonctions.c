#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "principalesFonctions.h"

// Calcul du nombre d'éléments d'un tableau d'entiers
int len(float * tab) {
    int cpt = 0;

    while (!tab) {
        cpt++;
    }

    return cpt;
}

// A partir d'un état, on définit les actions qu'on peut faire
// retour : La table des indices des actions possibles
float * enumAction(Etat_t * etat, Action_t * Q[LIGNE][COLONNE]) {
    float   actions[4];
    float * actionsPossibles;

    int cpt = 0;

    int j = (etat->x - 100)/100;         // indice de ligne
    int i = (etat->y - 20)/80;              // indice de colonne

    actionsPossibles = (float *) malloc(4*sizeof(float));

    if (!actionsPossibles) {
        printf("Erreur d'allocation\n");
    }

    for (int k = 0; k < 4; k++) {
        actions[k] = Q[i][j]->direction[k];
    }

    while (cpt < 4) {
        if (actions[cpt] != -1.0) {
            actionsPossibles[cpt] = cpt + 1.0;
            cpt++;
        }
    }
    return actionsPossibles;
}

int ActionAvecMeilleureQualite(Action_t * Q[LIGNE][COLONNE], int i, int j) {
    int max = Q[i][j]->direction[0];   
    int indice = 0;

    if (Q[i][j]->direction[1] > max) {
        max    = Q[i][j]->direction[1];   
        indice = 1;
    }
    else if (Q[i][j]->direction[2] > max) {
        max    = Q[i][j]->direction[2];   
        indice = 2;
    }
    else if (Q[i][j]->direction[3] > max) {
        max    = Q[i][j]->direction[3];   
        indice = 3;
    }

    return indice; 
} 

// Choix d'une action : epsilon-greedy
// Pb :  L'action que m'affiche epsilon-greedy me donne une action qui peut ne pas etre possible
int choixActionParEpsGreedy(Etat_t * etat, Action_t * Q[LIGNE][COLONNE], float epsilon) {
    float random = rand()/(RAND_MAX+1.0);

    if (random < epsilon) {
        //printf("C'est l'exploration qui a été choisie\n");
        return rand()%4;                    // Indice de l'état généré selon une loi uniforme
    }
    else {
        int i = (etat->x - 100)/100;
        int j = (etat->y - 20)/80;
        //printf("C'est l'exploitation qui a été choisie\n");
        return ActionAvecMeilleureQualite(Q, i, j);
    } 
} 

void etatSuivant(int * x, int * y, int indiceAction) {

    if (*x>0 && indiceAction == 0) {
        *x -= 1;
    }
    else if (*x<(LIGNE-1) && indiceAction == 1) {
        *x += 1;
    }
    else if (*y<(COLONNE-1) && indiceAction == 2) {
        *y += 1;
    }
    else if (*y>0 && indiceAction == 3) {
        *y -= 1;
    }
}

// Choix d'une action : Preference learning Base === Stratégie / Politique
// Retour : Indice de l'action qui aura lieu dà partir de l'état courant
int choixActionPLB(Etat_t * etat, Action_t * Q[LIGNE][COLONNE], float T, float alpha) {

    float   * actionPossible;                                         // la liste des actions possibles depuis l'état s
    float   * E_a;                                                    // tableau des énergies pour chaque action

    int cumul   = 0;                                                  // la probabilité d'une action

    float Z     = 0;                                               //la somme des énergies des éléments de L
    
    int N, q, indice;

    int x       = etat->x, y = etat->y;

    int ligne   = (y - 20)/80;
    int colonne = (x - 100)/100;
    
    int indiceAction;

    actionPossible = (float *) malloc(4*sizeof(float));
    E_a = (float *) malloc(4*sizeof(float));

    if (!actionPossible || !E_a){
        printf("Erreur : Echec de l'allocation !");
        exit(0);
    }

    actionPossible = enumAction(etat, Q);                       // On énumère les actions possibles à partir d'un état
    N = len(actionPossible);                                    // On calcule le nombre d'éléments de actionPossible



    for (int i = 0; i < N; i++) {
        indice = (int) actionPossible[i];
        q = Q[ligne][colonne]->direction[indice];
        E_a[i] = exp(q/T);                                                              // E(a)
        Z += E_a[i];                                                             // Somme des E(a)
    }
    
    indiceAction = actionPossible[N-1];

    for (int i = 0; i < N; i++) {
        cumul += E_a[i] / Z;

        if (alpha <= cumul) {
            indiceAction = actionPossible[i];
            break; 
        }
    }

    return indiceAction;
}

void deplacerVoiture (Etat_t * etat, int choice) {

        switch(choice) {

            case 0:
                if (etat->y > 20) {
                    etat->y -= 80;
                }
                break;
            
            case 1 :
                if (etat->y < 500) {
                    etat->y += 80;
                }
                break;
            
            case 2 :
                if (etat->x < 800) {
                    etat->x += 100;
                }
                break;
            
            case 3 :
                if (etat->x > 100) {
                    etat->x -= 100;
                }
                break;
            
            default:
                break;
        }  
} 

int estTerminal(Etat_t * etat) {

    int i = (etat->y - 20) / 80;
    int j = (etat->x - 100) / 100;

    if (i == 0 && j == 6) {
        return 1;
    } 
    return 0;
}
