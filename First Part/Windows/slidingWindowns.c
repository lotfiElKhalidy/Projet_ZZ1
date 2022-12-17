#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void end_sdl(char ok, char const* msg, SDL_Window * window, SDL_Renderer * renderer) {
    char msg_formated[255];                                                         
    int l;                                                                          

    if (!ok) {
        strncpy(msg_formated, msg, 250);                                              
        l = strlen(msg_formated);                                                     
        strcpy(msg_formated + l, " : %s\n");                                          

        SDL_Log(msg_formated, SDL_GetError());                                        
    }
    
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL)   {
        SDL_DestroyWindow(window);
        window= NULL;
    }

    SDL_Quit();                                                                     

    if (!ok) {               
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}

int main(int argc, char ** argv) {
    
    // Le double pointeur va nous aider à créer plusieurs fenetres 
    SDL_Window    ** tabWindow   = NULL;
    
    tabWindow = (SDL_Window **) malloc(20*sizeof(SDL_Window*));

    if (tabWindow == NULL) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    // Paramètres de position de la fonction de création d'une fenetre
    int              abcisse  = 0;
    int              ordonnee = 0;
    
    // Paramètres de position de la fonction de création d'une fenetre
    int              largeur  = 80;
    int              hauteur  = 60;

    // Pointeurs qui vont nous servir comme retour de la fonction SDL_GetWindowPosition
    int            * x, * y;

    // Allocation des pointeurs nécessaires
    x = (int *) malloc(sizeof(int));
    y = (int *) malloc(sizeof(int));
    
    if (x == NULL || y == NULL) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    // Initialisation graphique 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", NULL, NULL);
    }
       
    // Création des fenetres
    for (int i=0; i<20; i++) {
        tabWindow[i] = SDL_CreateWindow("SDL2 Programme 0.1", abcisse, ordonnee, largeur, hauteur, SDL_WINDOW_RESIZABLE);

        abcisse += 20;
        ordonnee += 20;

        if (tabWindow[i] == NULL) {
            end_sdl(0, "Echec de la création de la fenetre", tabWindow[i], NULL);
        }

        SDL_Delay(100);
    }    

    SDL_Delay(5);

    // On détruit les fenetres dans le sens inverse de leur creation
    for (int i=19; i>0; i--) {
        SDL_DestroyWindow(tabWindow[i]);
    }
    
   SDL_GetWindowPosition(tabWindow[0], x, y);

    // Descente de la dernière fenetre crée
    while (*y < 625) {
        largeur += 2.5;
        hauteur += 2.5;
        
        abcisse += 5;
        ordonnee += 5;

        SDL_SetWindowSize(tabWindow[0], largeur, hauteur);  
        SDL_SetWindowPosition(tabWindow[0], abcisse, ordonnee);
        SDL_GetWindowPosition(tabWindow[0] , x, y);
        SDL_Delay(1);
    }

    // Montée des fenetres
    while (*y > 0) {
        largeur += 1.25;
        hauteur += 1.25;
        
        abcisse += 5; 
        ordonnee -= 5;

        SDL_SetWindowSize(tabWindow[0], largeur, hauteur);  
        SDL_SetWindowPosition(tabWindow[0], abcisse, ordonnee);
        SDL_GetWindowPosition(tabWindow[0] , x, y);
        SDL_Delay(1);
        
    }

    // Déplacement horizontal des fenetres
    while (*x > 0) {
        largeur -= 0.55;
        hauteur -= 0.55;

        abcisse -= 5;
        
        SDL_SetWindowSize(tabWindow[0], largeur, hauteur);  
        SDL_SetWindowPosition(tabWindow[0], abcisse, ordonnee);
        SDL_GetWindowPosition(tabWindow[0] , x, y);
        SDL_Delay(1);
    }

    if (tabWindow[0] != NULL)
        SDL_DestroyWindow(tabWindow[0]);

    free(tabWindow);

    SDL_Quit();

    return 0;
}