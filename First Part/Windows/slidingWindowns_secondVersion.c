#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc,char **argv) {
    int abscisse = 0, ordonnee = 0, largeur = 60, hauteur = 40, it = 0, counter = 30;    
    
    SDL_Window *  window    = NULL;
    SDL_Window ** tabWindow = NULL;
    
    tabWindow = malloc(sizeof(window)*200);

    if (!tabWindow) {
        printf("Erreur : Allocation dynamique échouée");
    }

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    
    /* Création des fenetres */
    while (it < 50) {
        tabWindow[it] = SDL_CreateWindow("Fenêtre", abscisse, ordonnee, largeur, hauteur, SDL_WINDOW_RESIZABLE);
        
        if (tabWindow[it] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());                 // échec de la création de la fenêtre
            SDL_Quit();                              // On referme la SDL       
            exit(EXIT_FAILURE);                             
        }
        
        SDL_Delay(50);      // Pause exprimée  en ms
        
        ++it;

        abscisse += 5;
        largeur  += 5;
        hauteur  += 5;
    }

    while (it < 100) {
        tabWindow[it] = SDL_CreateWindow("Fenêtre", abscisse, ordonnee, largeur, hauteur, SDL_WINDOW_RESIZABLE);
        
        if (tabWindow[it] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());                 // échec de la création de la fenêtre
            SDL_Quit();                              // On referme la SDL       
            exit(EXIT_FAILURE);                             
        }
        
        SDL_Delay(50);      // Pause exprimée  en ms
        
        ++it;
        
        ordonnee += 5;
        largeur  -= 5;
        hauteur  -= 5;
    }
    
    while (counter > 0) {
        abscisse += 20;
        ordonnee += 20;
        
        SDL_SetWindowPosition(tabWindow[99],abscisse,ordonnee);
        SDL_Delay(50);
        
        counter -= 1;
    }
  
}
