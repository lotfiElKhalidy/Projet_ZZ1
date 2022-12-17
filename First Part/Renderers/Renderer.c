#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

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

int main(int argc, char **argv) {
    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", window, renderer);
    }

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Fenêtre", 350, 30, 800, 600, SDL_WINDOW_RESIZABLE);

    /* Création du rendu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) {
        end_sdl(0, "Echec de la création de la fenetre", window, renderer);
    }

    if (renderer == NULL) {
        end_sdl(0, "Echec de la création du rendu dans la fenetre", window, renderer);
    }

    SDL_Delay(500);
    
    //_______________________ Cette partie du code crée les rectangles et les déplace sur la fenetre ___________________________________

    // On initialise trois rectangles
    SDL_Rect rectangle[3];
    
    // xabs et yord vont contenir la position actuelle (et future) des trois rectangles 
    int xabs[3]  = {0}, yord[3]  = {0};
    int cpt      = 0; // compteur

    /* On dessine sur le rendu trois rectangles de taille 20px * 20px */
    for (int i=0; i<3; i++) {
        
        // paramètres de position
        rectangle[i].x = xabs[i];
        rectangle[i].y = yord[i];

        // paramètres de taille
        rectangle[i].w = 20;
        rectangle[i].h = 20;
    }

    while (cpt < 55) {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        
        for (int i=0; i<3; i++) {
            rectangle[i].x = xabs[i];
            rectangle[i].y = yord[i] ;
            
            SDL_RenderFillRect(renderer, &rectangle[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(30);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        xabs[0]  += 10;
        yord[0] += 5;
        
        xabs[1] += 10;
        yord[1] += 10;

        xabs[2] += 5;
        yord[2] += 10;

        cpt ++;
    }

    //______________________________________________________________________________________________________________________

    SDL_Delay(500); 

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    
    if (window != NULL)
        SDL_DestroyWindow(window);   

    SDL_Quit();

    return EXIT_SUCCESS;
}
