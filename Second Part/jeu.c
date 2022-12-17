#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"

int welcome = 1;

void jeu(SDL_Window  ** window, SDL_Renderer ** renderer, SDL_Texture ** carUp, SDL_Texture ** carDown,
                                SDL_Texture ** carLeft, SDL_Texture ** carRight, SDL_Texture ** cash, 
                                SDL_Texture ** bomb, SDL_Texture ** flag, SDL_Texture ** background, TTF_Font *font) {  

    SDL_bool       program_on = SDL_TRUE;                  // Booléen pour dire que le programme doit continuer
    SDL_Event      event;                                  // Evènement à traiter
    
    int          tailleCaseW = 700/LIGNE;
    int          tailleCaseH = 560/COLONNE;
    int sens = 0;

    float         epsilon    = 0.9, gamma = 0.5;   // Run : 90% exploration et 10% exploitation
    //printf(" < epsilon Initial = %f\n >", epsilon);

    float         Q_s_a, Q_value, Max, rn, S;

    float Un = 0.0;


    Action_t * Q[LIGNE][COLONNE];                   // Q(s,a) : Q_table

    // Etat initial de la voiture
    Etat_t etatInitial = {100, 500};

    // Etat final du jeu
    Etat_t etatFinal   = {700, 20};

    // Etat courant
    Etat_t etatCourant;

    // Action réalisée
    //Action_t action;
    int action;

    int indiceAction, indiceMeilleureAction, recompenseCumulee = 0;

    int grille[LIGNE][COLONNE];
    int mondeActuel[LIGNE][COLONNE];

    // Création du monde
    initialiser(grille);
    genererGrille(grille);
    //printf(" < epsilon après générerGrille = %f\n >", epsilon);

    // Sauvegarde du monde
    sauvegarderGrille(grille, mondeActuel);

    afficherGrille(grille);
    
    // Initialisation de la table des qualités
    allouerQ(Q);
    initQ(Q);
    
    // Création de la table des récompenses
    int ** recompense = (int **) malloc(LIGNE*sizeof(int *));

    if(!recompense) {
        printf("ERROR : ECHEC DE L'ALLOCATION");
        exit(0);
    } 

    for (int i = 0; i<LIGNE; i++) {

        recompense[i] = (int *) malloc(COLONNE*sizeof(int));

        if (!recompense[i]) {
            printf("ERROR : ECHEC DE L'ALLOCATION");
            exit(0);
        }
    }
    
    // On remplit la table des récompenses à partir de la grille
    defineRewardFromGrid(grille, &recompense);

    // Run : 90 % d'exploration et 10 % d'exploitation 
    for (int pas=0;  pas<NB_MAX_ETAT_PAR_EPOQUE; pas++) {

        //printf("/******** époque n°%d\n **************/", pas+1);
        
        Un = (float) 1/(pas+850);

        etatCourant = etatInitial;
        int i = (etatCourant.y - 20)/80;
        int j = (etatCourant.x - 100)/100;

        while (!estTerminal(&etatCourant)) {

            indiceAction = choixActionParEpsGreedy(&etatCourant, Q, epsilon);

            if (Q[i][j]->direction[indiceAction] != -1.0) { 

                Q_s_a = Q[i][j]->direction[indiceAction];
            
                etatSuivant(&i, &j, indiceAction);                          // On met à jour l'état courant
                deplacerVoiture (&etatCourant, indiceAction);

                S = gamma * Max;
                Q_value = Q_s_a + epsilon * (rn + S - Q_s_a);

                updateGrille(grille, indiceAction, recompense, &recompenseCumulee);
            }
        }

        // On récupère notre grille pour l'époque d'après
        copieGrille(mondeActuel, grille);

        epsilon -= Un; 
    }

   
    // On dessine notre grille initiale de taille 7 * 7
    afficherGrille(mondeActuel);

    while (program_on) {    

        SDL_RenderClear(*renderer);
        afficherBackground(*background, *window, *renderer);
        dessinerGrilleInitiale(tailleCaseW,tailleCaseH, *renderer);

        if (welcome) {
            affficherTexteBienvenue(window, renderer, font);

            if (SDL_PollEvent(&event)) {

                switch (event.type) {                         
                    case SDL_QUIT:                                
                        program_on = SDL_FALSE;                    
                        break;
                    
                    case SDL_KEYDOWN:                                                        
                        if (event.key.keysym.sym == SDLK_s) {
                            welcome = 0;
                        }else if (event.key.keysym.sym == SDLK_q){
                            program_on = SDL_FALSE;
                            printf("Vous avez quitté le jeu, A bientot.\n");
                            end_sdl_success(*window, *renderer);
                            exit(0);
                        } 
                }
            }   
        }
        else {
            drawWorldFromGrid(grille, *cash, *bomb, *flag, *carUp, *carLeft, *carDown, *carRight, *window , *renderer, sens);
            if (SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                    // terminé le programme Défiler l'élément en tête de file dans 'event'

                switch (event.type) {                         // En fonction de la valeur du type de cet évènement
                    case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                        program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                        break;
                    
                    case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                            // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                                                            // l'event, plusieurs champs deviennent pertinents   
                        switch (event.key.keysym.sym) {             // la touche appuyée est ..

                            case SDLK_UP:
                                deplacerVoiture (&etatInitial, 0);
                                updateGrille(grille,0, recompense, &recompenseCumulee);
                                sens = 0;
                                printf("0");
                                break;
                            
                            case SDLK_DOWN:
                                deplacerVoiture (&etatInitial,1);
                                updateGrille(grille,1, recompense, &recompenseCumulee);
                                sens = 1;
                                printf("1");
                                break;


                            case SDLK_RIGHT:
                                deplacerVoiture (&etatInitial,2);
                                updateGrille(grille, 2, recompense, &recompenseCumulee);
                                sens = 2;
                                printf("2");
                                break;
                            
                            case SDLK_LEFT:
                                deplacerVoiture (&etatInitial, 3);
                                updateGrille(grille,3, recompense, &recompenseCumulee);
                                sens = 3;
                                printf("3");                       
                                break;


                            case SDLK_q:
                                program_on = SDL_FALSE;
                                printf("Vous avez quitté le jeu, A bientot.\n");
                                end_sdl_success(*window, *renderer);
                                exit(0);
                                break;
                            
                            default:                           // Une touche appuyée qu'on ne traite pas
                                break;
                        }

                    default:
                        break;
                }
        
            }
        }

        SDL_RenderPresent(*renderer);
      
        SDL_Delay(1);
    }
    
}

